import sqlite3 from 'sqlite3';
import { User, Game, Tournament, ChatMessage, UserGameSettings } from '../types/interfaces.js';
import { v4 as uuidv4 } from 'uuid';

export class DatabaseService {
  private db: sqlite3.Database;

  constructor() {
    this.db = new sqlite3.Database('/app/data/transcendence.db', (err) => {
      if (err) {
        console.error('Error opening database:', err);
      } else {
        this.initializeTables();
      }
    });
  }

  private async initializeTables(): Promise<void> {
    const tables = [
      `CREATE TABLE IF NOT EXISTS users (
        id TEXT PRIMARY KEY,
        username TEXT UNIQUE NOT NULL,
        email TEXT UNIQUE NOT NULL,
        password TEXT NOT NULL,
        status INTEGER DEFAULT 0,
        friends TEXT DEFAULT '{}',
        gamesPlayed INTEGER DEFAULT 0,
        gamesWon INTEGER DEFAULT 0,
        gamesLost INTEGER DEFAULT 0,
        winRate REAL DEFAULT 0
      )`,

      `CREATE TABLE IF NOT EXISTS games (
        id TEXT PRIMARY KEY,
        player1Id TEXT NOT NULL,
        player2Id TEXT,
        mode TEXT NOT NULL,
        settings TEXT DEFAULT '{}',
        score TEXT DEFAULT '{"player1": 0, "player2": 0}',
        winner TEXT,
        winnerId TEXT,
        status TEXT DEFAULT 'waiting',
        createdAt TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
        finishedAt TEXT,
        FOREIGN KEY (player1Id) REFERENCES users (id),
        FOREIGN KEY (player2Id) REFERENCES users (id)
      )`,

      `CREATE TABLE IF NOT EXISTS tournaments (
        id TEXT PRIMARY KEY,
        name TEXT NOT NULL,
        creatorId TEXT NOT NULL,
        players TEXT DEFAULT '[]',
        maxPlayers INTEGER DEFAULT 8,
        status TEXT DEFAULT 'waiting',
        winnerId TEXT,
        matches TEXT DEFAULT '[]',
        settings TEXT DEFAULT '{}',
        FOREIGN KEY (creatorId) REFERENCES users (id)
      )`,

      `CREATE TABLE IF NOT EXISTS chat_messages (
        id TEXT PRIMARY KEY,
        senderId TEXT NOT NULL,
        content TEXT NOT NULL,
        channelId TEXT DEFAULT 'global',
        timestamp TEXT NOT NULL,
        type TEXT DEFAULT 'normal',
        isGlobal INTEGER DEFAULT 1,
        FOREIGN KEY (senderId) REFERENCES users (id)
      )`,

      `CREATE TABLE IF NOT EXISTS user_settings (
        id TEXT PRIMARY KEY,
        userId TEXT UNIQUE NOT NULL,
        settings TEXT DEFAULT '{}',
        FOREIGN KEY (userId) REFERENCES users (id)
      )`
    ];

    for (const table of tables) {
      await this.runQuery(table);
    }
  }

  try {
    await this.runQuery(`ALTER TABLE games ADD COLUMN createdAt TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP`);
  } catch (err) {
    // Colonne existe déjà
  }
  
  try {
    await this.runQuery(`ALTER TABLE games ADD COLUMN finishedAt TEXT`);
  } catch (err) {
    // Colonne existe déjà
  }



  private runQuery(sql: string, params: any[] = []): Promise<any> {
    return new Promise((resolve, reject) => {
      this.db.run(sql, params, function (err) {
        if (err) reject(err);
        else resolve({ lastID: this.lastID, changes: this.changes });
      });
    });
  }

  private getQuery(sql: string, params: any[] = []): Promise<any> {
    return new Promise((resolve, reject) => {
      this.db.get(sql, params, (err, row) => {
        if (err) reject(err);
        else resolve(row);
      });
    });
  }

  private allQuery(sql: string, params: any[] = []): Promise<any[]> {
    return new Promise((resolve, reject) => {
      this.db.all(sql, params, (err, rows) => {
        if (err) reject(err);
        else resolve(rows);
      });
    });
  }



  async createUser(userData: { username: string; email: string; password: string }): Promise<User> {
    const id = uuidv4();

    await this.runQuery(`
      INSERT INTO users (id, username, email, password)
      VALUES (?, ?, ?, ?)
    `, [id, userData.username, userData.email, userData.password]);

    return this.getUserById(id) as Promise<User>;
  }

  async getUserById(id: string): Promise<User | null> {
    const row = await this.getQuery('SELECT * FROM users WHERE id = ?', [id]);
    return row ? this.rowToUser(row) : null;
  }

  async getUserByUsername(username: string): Promise<User | null> {
    const row = await this.getQuery('SELECT * FROM users WHERE username = ?', [username]);
    return row ? this.rowToUser(row) : null;
  }

  async getUserByEmail(email: string): Promise<User | null> {
    const row = await this.getQuery('SELECT * FROM users WHERE email = ?', [email]);
    return row ? this.rowToUser(row) : null;
  }

  async getAllUsers(): Promise<User[]> {
    const rows = await this.allQuery('SELECT * FROM users ORDER BY username');
    return rows.map(row => this.rowToUser(row));
  }

  async updateUserStats(userId: string, gameResult: 'win' | 'loss'): Promise<void> {
    const user = await this.getUserById(userId);
    if (!user) return;

    const newGamesPlayed = user.gamesPlayed + 1;
    const newWins = gameResult === 'win' ? user.gamesWon + 1 : user.gamesWon;
    const newLosses = gameResult === 'loss' ? user.gamesLost + 1 : user.gamesLost;
    const newWinRate = (newWins / newGamesPlayed) * 100;

    await this.runQuery(`
      UPDATE users SET 
        gamesPlayed = ?, 
        gamesWon = ?, 
        gamesLost = ?, 
        winRate = ?
      WHERE id = ?
    `, [newGamesPlayed, newWins, newLosses, newWinRate, userId]);
  }

  private rowToUser(row: any): User {
    return {
      id: row.id,
      username: row.username,
      email: row.email,
      password: row.password,
      isOnline: Boolean(row.status),
      friends: row.friends || '{}',
      stats: {
        userId: row.id,
        gamesPlayed: row.gamesPlayed || 0,
        gamesWon: row.gamesWon || 0,
        gamesLost: row.gamesLost || 0,
        winRate: row.winRate || 0,
      }
    };
  }



  async addFriend(userId: string, friendId: string): Promise<boolean> {
    try {
      const user = await this.getUserById(userId);
      if (!user) return false;

      const friendsData = JSON.parse(user.friends || '{}');
      friendsData[friendId] = {
        status: 'accepted',
      };

      await this.runQuery(
        'UPDATE users SET friends = ? WHERE id = ?',
        [JSON.stringify(friendsData), userId]
      );

      return true;
    } catch (err) {
      console.error('Error adding friend:', err);
      return false;
    }
  }

  async getFriends(userId: string): Promise<User[]> {
    try {
      const user = await this.getUserById(userId);
      if (!user) return [];

      const friendsData = JSON.parse(user.friends || '{}');
      const friends = [];

      for (const friendId of Object.keys(friendsData)) {
        const friend = await this.getUserById(friendId);
        if (friend) friends.push(friend);
      }

      return friends;
    } catch (err) {
      return [];
    }
  }

  async removeFriend(userId: string, friendId: string): Promise<boolean> {
    try {
      const user = await this.getUserById(userId);
      if (!user) return false;

      const friendsData = JSON.parse(user.friends || '{}');

      delete friendsData[friendId];

      await this.runQuery(
        'UPDATE users SET friends = ? WHERE id = ?',
        [JSON.stringify(friendsData), userId]
      );

      const friend = await this.getUserById(friendId);
      if (friend) {
        const friendFriendsData = JSON.parse(friend.friends || '{}');
        delete friendFriendsData[userId];

        await this.runQuery(
          'UPDATE users SET friends = ? WHERE id = ?',
          [JSON.stringify(friendFriendsData), friendId]
        );
      }

      return true;
    } catch (err) {
      console.error('Error removing friend:', err);
      return false;
    }
  }



  async createGame(gameData: {
    player1Id: string;
    player2Id?: string;
    mode: string;
    settings?: any
  }): Promise<Game> {
    const id = uuidv4();
    const createdAt = new Date().toISOString();

    await this.runQuery(`
      INSERT INTO games (id, player1Id, player2Id, mode, settings, createdAt)
      VALUES (?, ?, ?, ?, ?, ?)
    `, [
      id,
      gameData.player1Id,
      gameData.player2Id || null,
      gameData.mode,
      JSON.stringify(gameData.settings || {}),
      createdAt,
    ]);

    return this.getGameById(id) as Promise<Game>;
  }

  async getGameById(id: string): Promise<Game | null> {
    const row = await this.getQuery('SELECT * FROM games WHERE id = ?', [id]);
    return row ? this.rowToGame(row) : null;
  }

  async updateGameStatus(gameId: string, status: string, winnerId?: string): Promise<void> {
    const updates = ['status = ?'];
    const values = [status];

    if (winnerId) {
      updates.push('winnerId = ?');
      values.push(winnerId);
    }

    if (status === 'finished' || status === 'completed') {
      updates.push('finishedAt = ?');
      values.push(new Date().toISOString());
    }

    await this.runQuery(
      `UPDATE games SET ${updates.join(', ')} WHERE id = ?`,
      [...values, gameId]
    );
  }

  async getActiveGames(): Promise<Game[]> {
    const rows = await this.allQuery(
      'SELECT * FROM games WHERE status IN (?, ?) ORDER BY id DESC',
      ['waiting', 'in-progress']
    );
    return rows.map(row => this.rowToGame(row));
  }

  private rowToGame(row: any): Game {
    return {
      id: row.id,
      player1Id: row.player1Id,
      player2Id: row.player2Id,
      mode: row.mode,
      settings: JSON.parse(row.settings || '{}'),
      score: JSON.parse(row.score || '{"player1": 0, "player2": 0}'),
      winner: row.winner,
      winnerId: row.winnerId,
      status: row.status || 'waiting',
      tournamentId: row.tournamentId,
      gameEvents: [],
      createdAt: row.createdAt ? new Date(row.createdAt) : new Date(),
      finishedAt: row.finishedAt ? new Date(row.finishedAt) : undefined,
    };
  }

  async getGameHistory(userId: string, limit: number = 20): Promise<Game[]> {
  const rows = await this.allQuery(`
    SELECT * FROM games 
    WHERE (player1Id = ? OR player2Id = ?) 
    AND status = 'finished'
    ORDER BY finishedAt DESC 
    LIMIT ?
  `, [userId, userId, limit]);
  
  return rows.map(row => this.rowToGame(row));
  }

  async getChatMessageById(id: string): Promise<ChatMessage | null> {
    const row = await this.getQuery('SELECT * FROM chat_messages WHERE id = ?', [id]);
    return row ? this.rowToChatMessage(row) : null;
  }

  async getRecentChatMessages(limit: number = 50): Promise<ChatMessage[]> {
    const rows = await this.allQuery(
      'SELECT * FROM chat_messages ORDER BY timestamp DESC LIMIT ?',
      [limit]
    );
    return rows.map(row => this.rowToChatMessage(row)).reverse();
  }

  private createPrivateChannelId(user1Id: string, user2Id: string): string {
    return [user1Id, user2Id].sort().join('-private');
  }

  async areFriends(userId: string, friendId: string): Promise<boolean> {
    try {
      const user = await this.getUserById(userId);
      if (!user) return false;

      const friendsData = JSON.parse(user.friends || '{}');
      return friendsData[friendId] && friendsData[friendId].status === 'accepted';
    } catch (err) {
      return false;
    }
  }

  async sendPrivateMessage(senderId: string, receiverId: string, content: string): Promise<ChatMessage | null> {
    try {
      const befriends = await this.areFriends(senderId, receiverId);
      if (!befriends) {
        return null;
      }

      const channelId = this.createPrivateChannelId(senderId, receiverId);

      const id = uuidv4();
      const timestamp = new Date().toISOString();

      await this.runQuery(`
      INSERT INTO chat_messages (id, senderId, content, channelId, timestamp, type, isGlobal)
      VALUES (?, ?, ?, ?, ?, ?, ?)
    `, [id, senderId, content, channelId, timestamp, 'private', 0]);

      return this.getChatMessageById(id);
    } catch (err) {
      console.error('Error sending private message:', err);
      return null;
    }
  }

  async getPrivateMessages(user1Id: string, user2Id: string, limit: number = 50): Promise<ChatMessage[]> {
    try {
      const befriends = await this.areFriends(user1Id, user2Id);
      if (!befriends) {
        return [];
      }

      const channelId = this.createPrivateChannelId(user1Id, user2Id);

      const rows = await this.allQuery(`
      SELECT * FROM chat_messages 
      WHERE channelId = ? AND type = 'private'
      ORDER BY timestamp DESC 
      LIMIT ?
    `, [channelId, limit]);

      return rows.map(row => this.rowToChatMessage(row)).reverse();
    } catch (err) {
      console.error('Error getting private messages:', err);
      return [];
    }
  }

  async createChatMessage(messageData: {
    senderId: string;
    content: string;
    channelId?: string;
    type?: 'normal' | 'private' | 'system';
    isGlobal?: boolean;
  }): Promise<ChatMessage> {
    const id = uuidv4();
    const timestamp = new Date().toISOString();

    await this.runQuery(`
    INSERT INTO chat_messages (id, senderId, content, channelId, timestamp, type, isGlobal)
    VALUES (?, ?, ?, ?, ?, ?, ?)
  `, [
      id,
      messageData.senderId,
      messageData.content,
      messageData.channelId || 'global',
      timestamp,
      messageData.type || 'normal',
      messageData.isGlobal !== false ? 1 : 0
    ]);

    return this.getChatMessageById(id) as Promise<ChatMessage>;
  }

  private rowToChatMessage(row: any): ChatMessage {
    return {
      id: row.id,
      senderId: row.senderId,
      content: row.content,
      channelId: row.channelId,
      timestamp: new Date(row.timestamp),
      type: row.type || 'normal',
      isGlobal: Boolean(row.isGlobal)
    };
  }



  async createTournament(tournamentData: {
    name: string;
    creatorId: string;
    maxPlayers?: number;
    settings?: any;
  }): Promise<Tournament> {
    const id = uuidv4();
    const players = [tournamentData.creatorId];

    await this.runQuery(`
      INSERT INTO tournaments (id, name, creatorId, players, maxPlayers, settings)
      VALUES (?, ?, ?, ?, ?, ?)
    `, [
      id,
      tournamentData.name,
      tournamentData.creatorId,
      JSON.stringify(players),
      tournamentData.maxPlayers || 8,
      JSON.stringify(tournamentData.settings || {}),
    ]);

    return this.getTournamentById(id) as Promise<Tournament>;
  }

  async getTournamentById(id: string): Promise<Tournament | null> {
    const row = await this.getQuery('SELECT * FROM tournaments WHERE id = ?', [id]);
    return row ? this.rowToTournament(row) : null;
  }

  async getActiveTournaments(): Promise<Tournament[]> {
    const rows = await this.allQuery(
      'SELECT * FROM tournaments WHERE status IN (?, ?) ORDER BY id DESC',
      ['waiting', 'in-progress']
    );
    return rows.map(row => this.rowToTournament(row));
  }

  private rowToTournament(row: any): Tournament {
    return {
      id: row.id,
      name: row.name,
      creatorId: row.creatorId,
      players: JSON.parse(row.players || '[]'),
      maxPlayers: row.maxPlayers || 8,
      status: row.status || 'waiting',
      winnerId: row.winnerId,
      matches: JSON.parse(row.matches || '[]'),
      settings: JSON.parse(row.settings || '{}'),
    };
  }
  async getUserSettings(userId: string): Promise<UserGameSettings | null> {
    const row = await this.getQuery('SELECT * FROM user_settings WHERE userId = ?', [userId]);
    return row ? this.rowToUserSettings(row) : null;
  }

  async createUserSettings(userId: string, settings: any): Promise<UserGameSettings> {
    const id = uuidv4();

    await this.runQuery(`
      INSERT INTO user_settings (id, userId, settings)
      VALUES (?, ?, ?)
    `, [id, userId, JSON.stringify(settings)]);

    return this.getUserSettings(userId) as Promise<UserGameSettings>;
  }

  private rowToUserSettings(row: any): UserGameSettings {
    return {
      id: row.id,
      userId: row.userId,
      settings: JSON.parse(row.settings || '{}'),
    };
  }


  async close(): Promise<void> {
    return new Promise((resolve, reject) => {
      this.db.close((err) => {
        if (err) reject(err);
        else resolve();
      });
    });
  }
}

export const dbService = new DatabaseService();