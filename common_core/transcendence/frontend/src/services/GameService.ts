import type { User, AuthResponse, GameResult } from '../types';
import { ApiService } from './ApiService';
import { StorageService } from './StorageService';
import { NotificationService } from './NotificationService';
import { PresenceService } from './PresenceService';

export class GameService {
	private static instance: GameService;
	private api: ApiService;
	private storage: StorageService;
	private notification: NotificationService;
	private currentUser: User | null = null;

	private constructor() {
		this.api = ApiService.getInstance();
		this.storage = StorageService.getInstance();;

		this.notification = NotificationService.getInstance()
	}

	static getInstance(): GameService {
		if (!GameService.instance) {
			GameService.instance = new GameService();
		}
		return GameService.instance;
	}

	async saveGame(gameResult: GameResult): Promise<void> {
		const token = this.storage.get<string>('authToken');
		if (!token) return;
		await this.api.post("/game/save", gameResult);
	}

	async getMyGames(): Promise<any[]> {
		const token = this.storage.get<string>('authToken');
		const user = this.storage.get<User>('pongUser');

		if (!token || !user) {
			return [];
		}

		try {
			const res = await this.api.get<{ success: boolean; data?: any[]; message?: string }>(
				`/game/profile/${user.id}`
			);

			if (!res.success || !res.data) {
				this.notification.show(res.message || 'Failed to load games history', 'error');
				return [];
			}

			return res.data;
		} catch (err) {
			console.error('getMyGames error', err);
			this.notification.show('Network error while loading games history', 'error');
			return [];
		}
	}
}
