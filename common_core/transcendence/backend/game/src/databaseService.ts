
import sqlite3 from 'sqlite3';
import path from 'path';
import fs from 'fs';


type PublicUser = {
	id: string;
	username: string;
	email?: string;
	avatar_url?: string | null;
	games_played: number;
	games_won: number;
	games_lost: number;
	win_rate: number;
};

export class DatabaseService {
	private db: sqlite3.Database;

	constructor() {
		const dbDir = '/app/data';
		if (!fs.existsSync(dbDir)) {
			fs.mkdirSync(dbDir, { recursive: true });
		}
		const dbPath = path.join(dbDir, 'transcendence.db');

		this.db = new sqlite3.Database(dbPath, (err: Error | null) => {
			if (err) {
				console.error('Error opening database (user service):', err);
			} else {
				console.log('User service: SQLite DB opened at', dbPath);
				this.initializeTables();
			}
		});
	}

	private initializeTables() {
		this.db.serialize(() => {

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
        win_rate REAL DEFAULT 0,
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


			this.db.all('SELECT * FROM users', (err, rows) => {
				if (err) {
					console.error('DB init failed', err);
				} else {
					console.log(`DB init ok, users count: ${rows.length}`);
				}
			});
		});
	}

	getUserById(id: string): Promise<any | null> {
		return new Promise((resolve, reject) => {
			this.db.get(
				'SELECT * FROM users WHERE id = ?',
				[id],
				(err: Error | null, row: any) => {
					if (err) reject(err);
					else resolve(row || null);
				}
			);
		});
	}


	getFriendsForUser(userId: string): Promise<any[]> {
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
					if (err) {
						reject(err);
					} else {

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


	setUserStatus(userId: string, status: number): Promise<void> {
		return new Promise((resolve, reject) => {
			this.db.run(
				`UPDATE users SET status = ? WHERE id = ?`,
				[status, userId],
				(err) => (err ? reject(err) : resolve())
			);
		});
	}


	getFriendsWithStatus(userId: string): Promise<Array<{
		id: string;
		username: string;
		email: string;
		avatar_url: string | null;
		status: number | null;
	}>> {
		return new Promise((resolve, reject) => {
			const sql = `
        -- Amis que j'ai ajoutés et acceptés
        SELECT u.id, u.username, u.email, u.avatar_url, u.status
        FROM user_friends uf
        JOIN users u ON u.id = uf.friend_id
        WHERE uf.user_id = ? AND uf.status = 'accepted'
        UNION
        -- Gens qui m'ont ajouté et que j'ai acceptés
        SELECT u2.id, u2.username, u2.email, u2.avatar_url, u2.status
        FROM user_friends uf2
        JOIN users u2 ON u2.id = uf2.user_id
        WHERE uf2.friend_id = ? AND uf2.status = 'accepted'
      `;
			this.db.all(sql, [userId, userId], (err: Error | null, rows: any[]) => {
				if (err) return reject(err);
				resolve(
					rows.map((r: any) => ({
						id: String(r.id),
						username: String(r.username),
						email: String(r.email),
						avatar_url: r.avatar_url ?? null,
						status: r.status ?? 0,
					}))
				);
			});
		});
	}


	getPublicUserById(userId: string): Promise<PublicUser | null> {
		return new Promise<PublicUser | null>((resolve, reject) => {
			this.db.get(
				`SELECT id, username, email, avatar_url,
                COALESCE(games_played, (games_won + games_lost)) AS games_played,
                COALESCE(games_won, 0)  AS games_won,
                COALESCE(games_lost, 0) AS games_lost,
                COALESCE(win_rate, 0)   AS win_rate
         FROM users
         WHERE id = ?`,
				[userId],
				(err: Error | null, row: any) => {
					if (err) return reject(err);
					resolve(row ? (row as PublicUser) : null);
				}
			);
		});
	}

	userLose(userId: string): Promise<boolean | null> {
		return new Promise<boolean | null>((resolve, reject) => {
			this.db.run(
				`UPDATE users
          SET games_lost = games_lost + 1,
              games_played = games_played + 1
          WHERE id = ?;`,
				[userId],
				(err: Error | null, row: any) => {
					if (err) return reject(err);
					resolve(true);
				}
			);
		});
	}

	userWon(userId: string): Promise<boolean | null> {
		return new Promise<boolean | null>((resolve, reject) => {
			this.db.run(
				`UPDATE users SET games_won = games_won + 1, games_played = games_played + 1 WHERE id = ?;`,
				[userId],
				(err: Error | null, row: any) => {
					if (err) return reject(err);
					resolve(true);
				}
			);
		});
	}


	createGame(gameData: any): Promise<any> {
		return new Promise(async (resolve, reject) => {
			let id = 'game-' + Date.now().toString();
			const player1win = gameData.score.player1 > gameData.score.player2;
			const update_stat_res = await (player1win ? this.userWon(gameData.player1id) : this.userLose(gameData.player1id));
			if (!update_stat_res)
				reject(Error("Updating player stat error!"));
			this.db.run(
				`INSERT INTO games (id, player1_id, mode, settings, score)
          VALUES (?, ?, ?, ?, ?)`,
				[id, gameData.player1id, gameData.mode, JSON.stringify(gameData.settings || {}), JSON.stringify(gameData.score)],
				(err: Error | null) => {
					if (err) reject(err);
					else resolve(gameData);
				}
			);
		});
	}

	getGamesByPlayerId(playerId: string): Promise<any[]> {
		return new Promise((resolve, reject) => {
			this.db.all(
				`SELECT * FROM games
          WHERE player1_id = ? OR player2_id = ?`,
				[playerId, playerId],
				(err: Error | null, rows: any[]) => {
					if (err) reject(err);
					else resolve(rows);
				}
			);
		});
	}
}

export const dbService = new DatabaseService();
