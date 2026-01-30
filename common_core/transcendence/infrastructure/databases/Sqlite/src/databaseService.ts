// src/databaseService.ts
import sqlite3 from 'sqlite3';
import path from 'path';
import fs from 'fs';
import { randomUUID } from 'crypto';
import { sqlCounter } from './metrics';

export class DatabaseService {
  private db: sqlite3.Database;

  constructor() {
    const dbDir = '/app/data';
    if (!fs.existsSync(dbDir)) {
      fs.mkdirSync(dbDir, { recursive: true });
    }

    const dbPath = path.join(dbDir, 'transcendence.db');

    this.db = new sqlite3.Database(dbPath, (err) => {
      if (err) {
        console.error('Error opening database:', err);
      } else {
        console.log('SQLite DB opened at', dbPath);
        this.initializeTables();
      }
    });
  }

  private initializeTables() {
  this.db.serialize(() => {
    // 1. tables de base
    this.db.run(
      `CREATE TABLE IF NOT EXISTS users (
        id TEXT PRIMARY KEY,
        github_id TEXT UNIQUE,
        username TEXT UNIQUE NOT NULL,
        email TEXT UNIQUE NOT NULL,
        password TEXT NOT NULL,
        avatar_url TEXT,
        status INTEGER DEFAULT 0,
        games_played INTEGER DEFAULT 0,
        games_won INTEGER DEFAULT 0,
        games_lost INTEGER DEFAULT 0,
        language TEXT DEFAULT 'fr',
        created_at TEXT DEFAULT CURRENT_TIMESTAMP
      );`,
      (err) => {
        if (err) console.error('Error creating users:', err);
      }
    );

    this.db.run(
      `CREATE TABLE IF NOT EXISTS games (
        id TEXT PRIMARY KEY,
        player1_id TEXT NOT NULL,
        player2_id TEXT,
        mode TEXT NOT NULL,
        settings TEXT DEFAULT '{}',
        score TEXT DEFAULT '{"player1": 0, "player2": 0}',
        winner TEXT,
        winner_id TEXT,
        status TEXT DEFAULT 'waiting',
        created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
        finished_at TEXT,
        FOREIGN KEY (player1_id) REFERENCES users (id),
        FOREIGN KEY (player2_id) REFERENCES users (id)
      );`,
      (err) => {
        if (err) console.error('Error creating games:', err);
      }
    );

    this.db.run(
      `CREATE TABLE IF NOT EXISTS tournaments (
        id TEXT PRIMARY KEY,
        name TEXT NOT NULL,
        creator_id TEXT NOT NULL,
        players TEXT DEFAULT '[]',
        max_players INTEGER DEFAULT 8,
        status TEXT DEFAULT 'waiting',
        winner_id TEXT,
        matches TEXT DEFAULT '[]',
        settings TEXT DEFAULT '{}',
        FOREIGN KEY (creator_id) REFERENCES users (id)
      );`,
      (err) => {
        if (err) console.error('Error creating tournaments:', err);
      }
    );

    this.db.run(
      `CREATE TABLE IF NOT EXISTS chat_messages (
        id TEXT PRIMARY KEY,
        sender_id TEXT NOT NULL,
        content TEXT NOT NULL,
        channel_id TEXT DEFAULT 'global',
        timestamp TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
        type TEXT DEFAULT 'normal',
        is_global INTEGER DEFAULT 1,
        FOREIGN KEY (sender_id) REFERENCES users (id)
      );`,
      (err) => {
        if (err) console.error('Error creating chat_messages:', err);
      }
    );

    this.db.run(
      `CREATE TABLE IF NOT EXISTS user_settings (
        id TEXT PRIMARY KEY,
        user_id TEXT UNIQUE NOT NULL,
        settings TEXT DEFAULT '{}',
        FOREIGN KEY (user_id) REFERENCES users (id)
      );`,
      (err) => {
        if (err) console.error('Error creating user_settings:', err);
      }
    );

    // 💡 nouvelle table pour les amis
    this.db.run(
      `CREATE TABLE IF NOT EXISTS user_friends (
        id TEXT PRIMARY KEY,
        user_id TEXT NOT NULL,
        friend_id TEXT NOT NULL,
        status TEXT DEFAULT 'accepted',
        created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY (user_id) REFERENCES users (id),
        FOREIGN KEY (friend_id) REFERENCES users (id),
        UNIQUE (user_id, friend_id)
      );`,
      (err) => {
        if (err) console.error('Error creating user_friends:', err);
      }
    );

    // 2. petit test
    this.db.all('SELECT * FROM users', (err, rows) => {
      if (err) {
        console.error('DB init failed', err);
      } else {
        console.log(`DB init ok, users count: ${rows.length}`);
      }
    });
  });
}


  getAllUsers(): Promise<any[]> {
    sqlCounter.inc(); // compter la requête
    return new Promise((resolve, reject) => {
      this.db.all('SELECT * FROM users', [], (err, rows) => {
        if (err) reject(err);
        else resolve(rows);
      });
    });
  }
  // src/databaseService.ts (à la suite)

getUserByUsername(username: string): Promise<any | null> {
  return new Promise((resolve, reject) => {
    this.db.get(
      'SELECT * FROM users WHERE username = ?',
      [username],
      (err, row) => {
        if (err) reject(err);
        else resolve(row || null);
      }
    );
  });
}

getUserByEmail(email: string): Promise<any | null> {
  return new Promise((resolve, reject) => {
    this.db.get(
      'SELECT * FROM users WHERE email = ?',
      [email],
      (err, row) => {
        if (err) reject(err);
        else resolve(row || null);
      }
    );
  });
}

createUser(user: {
  id: string;
  username: string;
  email: string;
  password: string;
}): Promise<void> {
  return new Promise((resolve, reject) => {
    this.db.run(
      `INSERT INTO users (id, username, email, password)
       VALUES (?, ?, ?, ?)`,
      [user.id, user.username, user.email, user.password],
      (err) => {
        if (err) reject(err);
        else resolve();
      }
    );
  });
}

async updateUserAvatar(id: string, avatarUrl: string): Promise<void> {
  return new Promise((resolve, reject) => {
    this.db.run(
      'UPDATE users SET avatar_url = ? WHERE id = ?',
      [avatarUrl, id],
      (err) => {
        if (err) reject(err);
        else resolve();
      }
    );
  });
}

addFriend(userId: string, friendId: string): Promise<void> {
  return new Promise((resolve, reject) => {
    const id = randomUUID();
    this.db.run(
      `INSERT OR IGNORE INTO user_friends (id, user_id, friend_id, status)
       VALUES (?, ?, ?, 'accepted')`,
      [id, userId, friendId],
      (err) => {
        if (err) reject(err);
        else resolve();
      }
    );
  });
}

// récupérer tous les amis d’un user (dans les deux sens)
getFriends(userId: string): Promise<any[]> {
  return new Promise((resolve, reject) => {
      this.db.all(
        `
        -- les amis que j'ai ajoutés et qui sont acceptés
        SELECT u.* FROM user_friends uf
        JOIN users u ON u.id = uf.friend_id
        WHERE uf.user_id = ? AND uf.status = 'accepted'
        UNION
        -- les gens qui m'ont ajouté et que j'ai acceptés
        SELECT u2.* FROM user_friends uf2
        JOIN users u2 ON u2.id = uf2.user_id
        WHERE uf2.friend_id = ? AND uf2.status = 'accepted'
        `,
        [userId, userId],
        (err: Error | null, rows: any[]) => {
          if (err) reject(err);
          else resolve(rows);
        }
      );
    });
  }

  getFriendRequests(userId: string): Promise<any[]> {
    return new Promise((resolve, reject) => {
      this.db.all(
        `
        SELECT uf.user_id AS requester_id, u.username, u.email, u.avatar_url
        FROM user_friends uf
        JOIN users u ON u.id = uf.user_id
        WHERE uf.friend_id = ? AND uf.status = 'pending'
        `,
        [userId],
        (err: Error | null, rows: any[]) => {
          if (err) reject(err);
          else resolve(rows);
        }
      );
    });
  }

  createFriendRequest(userId: string, friendId: string, id: string): Promise<void> {
    return new Promise((resolve, reject) => {
      this.db.run(
        `INSERT OR IGNORE INTO user_friends (id, user_id, friend_id, status)
         VALUES (?, ?, ?, 'pending')`,
        [id, userId, friendId],
        (err: Error | null) => {
          if (err) reject(err);
          else resolve();
        }
      );
    });
  }

  acceptFriendRequest(requesterId: string, me: string): Promise<void> {
    return new Promise((resolve, reject) => {
      this.db.run(
        `UPDATE user_friends
         SET status = 'accepted'
         WHERE user_id = ? AND friend_id = ?`,
        [requesterId, me],
        (err: Error | null) => {
          if (err) reject(err);
          else {
            // on peut créer la ligne inverse pour symétrie
            const backId = 'uf-' + Date.now().toString();
            this.db.run(
              `INSERT OR IGNORE INTO user_friends (id, user_id, friend_id, status)
               VALUES (?, ?, ?, 'accepted')`,
              [backId, me, requesterId],
              (err2: Error | null) => {
                if (err2) reject(err2);
                else resolve();
              }
            );
          }
        }
      );
    });
  }

  deleteFriendLink(userId: string, friendId: string): Promise<void> {
    return new Promise((resolve, reject) => {
      this.db.run(
        `DELETE FROM user_friends
         WHERE (user_id = ? AND friend_id = ?)
            OR (user_id = ? AND friend_id = ?)`,
        [userId, friendId, friendId, userId],
        (err: Error | null) => {
          if (err) reject(err);
          else resolve();
        }
      );
    });
  }

removeFriend(userId: string, friendId: string): Promise<void> {
  return new Promise((resolve, reject) => {
    this.db.run(
      `
      DELETE FROM user_friends
      WHERE (user_id = ? AND friend_id = ?)
         OR (user_id = ? AND friend_id = ?)
      `,
      [userId, friendId, friendId, userId],
      (err) => {
        if (err) reject(err);
        else resolve();
      }
    );
  });
}

}

export const dbService = new DatabaseService();
