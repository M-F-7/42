
import { ApiService } from './ApiService';

export type Friend = {
	id: string;
	username: string;
	email?: string;
	status: number;
	avatar_url?: string | null;
	games_played: number;
	games_won: number;
	games_lost: number;
	win_rate: number;
};

export type FriendRequest = {
	id: string;
	username: string;
	email?: string;
	avatar_url?: string | null;
};

export class FriendService {
	private static instance: FriendService;
	private api: ApiService;

	private constructor() {
		this.api = ApiService.getInstance();
	}

	static getInstance(): FriendService {
		if (!FriendService.instance) {
			FriendService.instance = new FriendService();
		}
		return FriendService.instance;
	}

	private toAbsolute(url?: string | null): string | null {
		if (!url) return null;
		if (url.startsWith('http://') || url.startsWith('https://')) return url;
		return this.api.getBaseUrl() + url;
	}

	async getFriends(): Promise<Friend[]> {
		const res = await this.api.get<Friend[]>('/user/friends');
		if (res.success && res.data) {
			return (res.data as any[]).map((f: any) => ({
				id: f.id,
				username: f.username,
				email: f.email,
				status: Number(f.status ?? 0),
				avatar_url: this.toAbsolute(f.avatar_url ?? null),
			}));
		}
		return [];
	}

	async addFriendById(friendId: string): Promise<boolean> {
		const res = await this.api.post<{}>(`/user/friends/${friendId}`);
		return !!res.success;
	}

	async removeFriend(friendId: string): Promise<boolean> {
		const res = await this.api.delete<{}>(`/user/friends/${friendId}`);
		return !!res.success;
	}

	async getFriendRequests(): Promise<FriendRequest[]> {
		const res = await this.api.get<any[]>('/user/friend-requests');
		if (res.success && Array.isArray(res.data)) {
			return res.data.map((r: any) => ({
				id: r.id ?? r.requester_id,
				username: r.username,
				email: r.email,
				avatar_url: this.toAbsolute(r.avatar_url ?? null),
			}));
		}
		return [];
	}

	async acceptFriend(requesterId: string): Promise<boolean> {
		const res = await this.api.post(`/user/friends/${requesterId}/accept`);
		return !!res.success;
	}

	async declineFriend(requesterId: string): Promise<boolean> {
		const res = await this.api.post(`/user/friends/${requesterId}/decline`);
		return !!res.success;
	}

	async getFriendProfile(friendId: string): Promise<FriendProfile | null> {
		const res = await this.api.get<{ user: any }>(`/user/profile/${friendId}`);
		if (!res.success || !res.data?.user) return null;
		const u = res.data.user;


		let avatar = u.avatar_url ?? null;
		if (avatar && typeof avatar === 'string' && avatar.startsWith('/')) {
			avatar = this.api.getBaseUrl() + avatar;
		}

		const won = Number(u.games_won ?? 0);
		const lost = Number(u.games_lost ?? 0);
		const played = Number(u.games_played ?? (won + lost));

		let wr = Number(u.win_rate ?? 0);
		if (wr <= 1 && (won + lost > 0 || u.win_rate <= 1)) wr = wr * 100;
		if (u.win_rate == null && played > 0) wr = (won / played) * 100;

		return {
			id: String(u.id),
			username: String(u.username),
			avatar_url: avatar,
			games_played: played,
			games_won: won,
			games_lost: lost,
			win_rate: Number.isFinite(wr) ? wr : 0,
		};
	}
}
