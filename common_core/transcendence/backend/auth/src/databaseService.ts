
import sqlite3 from 'sqlite3';
import path from 'path';
import fs from 'fs';

export interface DbUser {
	id: string;
	username: string;
	email: string | null;
	password: string | null;
	status?: number;
	friends?: string;
	games_played?: number;
	games_won?: number;
	games_lost?: number;
	win_rate?: number;
	created_at?: string;
	avatar_url?: string | null;
	github_id?: string | null;
}


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
				console.error('Error opening database:', err);
			} else {
				console.log('SQLite DB opened at', dbPath);
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

	getUserByUsername(username: string): Promise<any | null> {
		return new Promise((resolve, reject) => {
			this.db.get(
				'SELECT * FROM users WHERE username = ?',
				[username],
				(err: Error | null, row: any) => {
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
				(err: Error | null, row: any) => {
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
				(err: Error | null) => {
					if (err) reject(err);
					else resolve();
				}
			);
		});
	}


	updateUser(id: string, data: { username?: string; email?: string }): Promise<void> {
		return new Promise((resolve, reject) => {
			const { username, email } = data;


			this.db.run(
				'UPDATE users SET username = ?, email = ? WHERE id = ?',
				[username, email, id],
				(err: Error | null) => {
					if (err) reject(err);
					else resolve();
				}
			);
		});
	}

	async updateUserPassword(id: string, password: string): Promise<void> {
		return new Promise((resolve, reject) => {
			this.db.run(
				'UPDATE users SET password = ? WHERE id = ?',
				[password, id],
				(err: Error | null) => {
					if (err) return reject(err);
					resolve();
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

	findUserByGithubIdOrEmail(githubId: string, email?: string | null): Promise<DbUser | null> {
		return new Promise((resolve, reject) => {
			let sql = 'SELECT * FROM users WHERE github_id = ?';
			const params: any[] = [githubId];

			if (email) {
				sql += ' OR email = ?';
				params.push(email);
			}

			this.db.get(sql, params, (err: Error | null, row: any) => {
				if (err) return reject(err);
				resolve((row as DbUser) || null);
			});
		});
	}

	createUserFromGithub(data: {
		githubId: string;
		username: string;
		email?: string | null;
		avatar_url?: string | null;
	}): Promise<DbUser> {
		return new Promise((resolve, reject) => {
			const id = 'user-' + Date.now().toString();

			const dummyPassword = 'github-oauth-' + data.githubId;

			this.db.run(
				`INSERT INTO users (id, username, email, password, avatar_url, github_id)
         VALUES (?, ?, ?, ?, ?, ?)`,
				[id, data.username, data.email ?? null, dummyPassword, data.avatar_url ?? null, data.githubId],
				(err: Error | null) => {
					if (err) return reject(err);

					this.db.get(
						'SELECT * FROM users WHERE id = ?',
						[id],
						(err2: Error | null, row: any) => {
							if (err2) return reject(err2);
							resolve(row as DbUser);
						}
					);
				}
			);
		});
	}



}

export const dbService = new DatabaseService();
