import type { User, AuthResponse } from '../types';
import { ApiService } from './ApiService';
import { StorageService } from './StorageService';
import { NotificationService } from './NotificationService';
import { PresenceService } from './PresenceService';

export class AuthService {
	private static instance: AuthService;
	private api: ApiService;
	private storage: StorageService;
	private notification: NotificationService;
	private currentUser: User | null = null;
	private authChangeCallbacks: Array<(user: User | null) => void> = [];

	private constructor() {
		this.api = ApiService.getInstance();
		this.storage = StorageService.getInstance();;
		this.loadUserFromStorage();
		this.notification = NotificationService.getInstance()
	}

	static getInstance(): AuthService {
		if (!AuthService.instance) {
			AuthService.instance = new AuthService();
		}
		return AuthService.instance;
	}

	onAuthChange(callback: (user: User | null) => void): () => void {
		this.authChangeCallbacks.push(callback);
		return () => {
			this.authChangeCallbacks = this.authChangeCallbacks.filter((cb) => cb !== callback);
		};
	}

	private notifyAuthChange(): void {
		this.authChangeCallbacks.forEach((callback) => callback(this.currentUser));
	}

	private loadUserFromStorage(): void {
		const savedUser = this.storage.get<User>('pongUser');
		const authToken = this.storage.get<string>('authToken');

		if (savedUser && authToken) {
			this.currentUser = savedUser;
			this.notifyAuthChange();
		}
	}

	async login(username: string, password: string): Promise<boolean> {
		try {
			const response: AuthResponse = await this.api.post('/auth/login', {
				username,
				password,
			});

			if (!response.success || !response.data) {
				this.notification.show(response.message || 'Login failed', 'error');
				return false;
			}

			this.currentUser = response.data.user;
			this.storage.set('pongUser', response.data.user);
			this.storage.set('authToken', response.data.token);
			this.notifyAuthChange();
			return true;
		} catch (error) {
			console.error('Login error:', error);
			this.notification.show('Network or server error during login', 'error');
			return false;
		}
	}

	async register(username: string, password: string, email: string): Promise<boolean> {
		try {
			const response: AuthResponse = await this.api.post('/auth/register', {
				username,
				password,
				email,
			});

			if (!response.success || !response.data) {
				this.notification.show(response.message || 'Registration failed', 'error');
				return false;
			}

			this.currentUser = response.data.user;
			this.storage.set('pongUser', response.data.user);
			this.storage.set('authToken', response.data.token);
			this.notification.show('Registered successfully!', 'success');
			this.notifyAuthChange();
			return true;
		} catch (error) {
			console.error('Registration error:', error);
			this.notification.show('Network or server error during registration', 'error');
			return false;
		}
	}

	async logout(): void {
		await PresenceService.offline();
		this.currentUser = null;
		this.storage.remove('pongUser');
		this.storage.remove('authToken');
		this.notifyAuthChange();
	}

	isAuthenticated(): boolean {
		return this.currentUser !== null;
	}

	getCurrentUser(): User | null {
		return this.currentUser;
	}


	async refreshCurrentUser(): Promise<void> {
		const token = this.storage.get<string>('authToken');
		if (!token) return;

		const me = await this.api.get<{ user: any }>('/auth/me');
		if (me.success && me.data?.user) {
			const u = me.data.user;


			let avatar = u.avatar_url ?? null;
			if (avatar && typeof avatar === 'string' && avatar.startsWith('/')) {
				avatar = this.api.getBaseUrl() + avatar;
			}


			const games_won = Number(u.games_won ?? 0);
			const games_lost = Number(u.games_lost ?? 0);


			let games_played = Number(u.games_played ?? (games_won + games_lost));


			let win_rate = Number(u.win_rate ?? 0);
			if (win_rate <= 1 && (games_won + games_lost > 0 || u.win_rate <= 1)) {
				win_rate = win_rate * 100;
			}

			if (!u.win_rate && games_played > 0) {
				win_rate = (games_won / games_played) * 100;
			}

			this.currentUser = {
				id: String(u.id),
				username: String(u.username),
				email: u.email ?? undefined,
				avatar_url: avatar,
				games_played,
				games_won,
				games_lost,
				win_rate: Number.isFinite(win_rate) ? win_rate : 0,
				language: u.language,
			};


			this.storage.set('pongUser', this.currentUser);


			this.notifyAuthChange(this.currentUser);
		}
	}



	async updateProfile(payload: { username?: string; email?: string }): Promise<boolean> {
		const res = await this.api.put<{ user: User }>('/auth/me', payload);
		if (res.success && res.data?.user) {
			const apiUser = res.data.user as any;


			const existingAvatar = this.currentUser?.avatar_url;


			if (apiUser.avatar_url && apiUser.avatar_url.startsWith('/')) {
				apiUser.avatar_url = this.api.getBaseUrl() + apiUser.avatar_url;
			}


			if (!apiUser.avatar_url && existingAvatar) {
				apiUser.avatar_url = existingAvatar;
			}

			this.currentUser = apiUser;
			this.storage.set('pongUser', apiUser);
			this.notifyAuthChange();
			return true;
		}
		return false;
	}


	async changePassword(payload: { currentPassword: string; newPassword: string }): Promise<boolean> {

		const res = await this.api.put<{ success: boolean; message?: string }>('/auth/password', payload);
		if (res.success) {
			this.notification.show('Password changed', 'success');
			return true;
		} else {
			this.notification.show(res.message || 'Could not change password', 'error');
			return false;
		}
	}

	async uploadAvatar(file: File): Promise<string | null> {
		const formData = new FormData();
		formData.append('avatar', file);

		const res = await this.api.postForm<{ success: boolean; data?: { avatarUrl: string } }>(
			'/auth/avatar',
			formData
		);

		if (res.success && res.data?.avatarUrl) {

			let fullUrl = res.data.avatarUrl;
			if (fullUrl.startsWith('/')) {
				fullUrl = this.api.getBaseUrl() + fullUrl;
			}

			if (this.currentUser) {
				this.currentUser = { ...this.currentUser, avatar_url: fullUrl };
				this.storage.set('pongUser', this.currentUser);
				this.notifyAuthChange();
			}

			return fullUrl;
		}

		return null;
	}

	async handleOAuthCallback(token: string): Promise<boolean> {
		try {

			this.storage.set('authToken', token);


			await this.refreshCurrentUser();

			if (!this.currentUser) {

				this.notification.show('OAuth login failed', 'error');
				this.storage.remove('authToken');
				return false;
			}

			this.notification.show('Logged in with GitHub', 'success');
			return true;
		} catch (err) {
			console.error('OAuth callback error:', err);
			this.notification.show('Error during OAuth login', 'error');
			this.storage.remove('authToken');
			return false;
		}
	}
}
