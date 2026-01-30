
import bcrypt from 'bcryptjs';
import { dbService } from './databaseService';
import crypto from 'crypto';
import jwt from 'jsonwebtoken';

const JWT_SECRET = process.env.JWT_SECRET || 'dev-secret';
const JWT_EXPIRES_IN = process.env.JWT_EXPIRES_IN || '1h';

export class AuthService {
	async register(username: string, password: string, email: string) {
		if (!username || !password || !email) {
			return { success: false, message: 'Missing fields' };
		}

		const existingByUsername = await dbService.getUserByUsername(username);
		if (existingByUsername) {
			return { success: false, message: 'Username already taken' };
		}

		const existingByEmail = await dbService.getUserByEmail(email);
		if (existingByEmail) {
			return { success: false, message: 'Email already taken' };
		}

		const hashed = await bcrypt.hash(password, 10);
		const id =
			'user-' + (crypto.randomUUID ? crypto.randomUUID() : Date.now().toString());

		await dbService.createUser({
			id,
			username,
			email,
			password: hashed,
		});

		const user = { id, username, email };


		const token = jwt.sign(
			{
				sub: user.id,
				username: user.username,
				email: user.email,
			},
			JWT_SECRET as any,
			{
				expiresIn: JWT_EXPIRES_IN,
			} as any
		);

		return {
			success: true,
			data: {
				user,
				token,
			},
		};
	}

	async login(username: string, password: string) {
		if (!username || !password) {
			return { success: false, message: 'Missing credentials' };
		}

		const userRow = await dbService.getUserByUsername(username);
		if (!userRow) {
			return { success: false, message: 'User not found' };
		}

		const passwordMatch = await bcrypt.compare(password, userRow.password);
		if (!passwordMatch) {
			return { success: false, message: 'Invalid password' };
		}

		const user = {
			id: userRow.id,
			username: userRow.username,
			email: userRow.email,
			language: userRow.language
		};

		const token = jwt.sign(
			{
				sub: user.id,
				username: user.username,
				email: user.email,
			},
			JWT_SECRET as any,
			{
				expiresIn: JWT_EXPIRES_IN,
			} as any
		);

		return {
			success: true,
			data: {
				user,
				token,
			},
		};
	}

	async changePassword(userId: string, currentPassword: string, newPassword: string): Promise<boolean> {
		const user = await dbService.getUserById(userId);
		if (!user) return false;

		const match = await bcrypt.compare(currentPassword, user.password);
		if (!match) return false;

		const hashed = await bcrypt.hash(newPassword, 10);

		await dbService.updateUserPassword(userId, hashed);

		return true;
	}
}
