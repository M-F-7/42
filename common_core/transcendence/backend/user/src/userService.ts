
import { dbService } from './databaseService';
import crypto from 'crypto';

export class UserService {
	async getMyFriends(userId: string) {
		const friends = await dbService.getFriendsForUser(userId);
		return friends.map((f: any) => ({
			id: f.id,
			username: f.username,
			email: f.email,
			avatar_url: f.avatar_url ?? null,
		}));
	}

	async getMyFriendRequests(userId: string) {
		const reqs = await dbService.getFriendRequests(userId);
		return reqs.map((r: any) => ({
			id: r.requester_id,
			username: r.username,
			email: r.email,
			avatar_url: r.avatar_url ?? null,
		}));
	}

	async sendFriendRequest(userId: string, friendId: string) {
		if (userId === friendId) throw new Error('Cannot add yourself');

		const target = await dbService.getUserById(friendId);
		if (!target) throw new Error('User not found');

		const id =
			'uf-' + (crypto.randomUUID ? crypto.randomUUID() : Date.now().toString());
		await dbService.createFriendRequest(userId, friendId, id);
	}

	async acceptFriend(userId: string, requesterId: string) {

		await dbService.acceptFriendRequest(requesterId, userId);
	}

	async declineFriend(userId: string, requesterId: string) {
		await dbService.deleteFriendLink(requesterId, userId);
	}

	async removeFriend(userId: string, friendId: string) {
		await dbService.deleteFriendLink(userId, friendId);
	}
}
