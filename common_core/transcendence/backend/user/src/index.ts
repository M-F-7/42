import Fastify from 'fastify';
import cors from '@fastify/cors';
import jwtPlugin from '@fastify/jwt';
import xss from 'xss';
import { UserService } from './userService';
import { dbService } from './databaseService';

async function start() {
	const app = Fastify({ logger: true });
	const PORT = Number(process.env.USER_PORT || 4006);
	const HOST = '0.0.0.0';

	await app.register(cors, {
		origin: true,
		credentials: true,
	});

	await app.register(jwtPlugin, {
		secret: process.env.JWT_SECRET || 'super-secret-dev',
	});

	const userService = new UserService();

	app.get('/user/health', async () => ({ status: 'ok', service: 'user' }));

	app.addHook("preHandler", async (request) => {
		function sanitizeValue(value: any): any {
			if (typeof value === "string") return xss(value);
			if (Array.isArray(value)) return value.map(sanitizeValue);
			if (value && typeof value === "object") {
				const out: any = {};
				for (const k in value) out[k] = sanitizeValue(value[k]);
				return out;
			}
			return value;
		}

		if (request.body) request.body = sanitizeValue(request.body);
		if (request.params) request.params = sanitizeValue(request.params);
		if (request.query) request.query = sanitizeValue(request.query);
	});


	app.addHook('onRequest', async (request, reply) => {
		const auth = request.headers.authorization;
		if (request.url === '/user/health') return;
		if (!auth || !auth.startsWith('Bearer ')) {
			return reply.code(401).send({ success: false, message: 'Missing token' });
		}
		const token = auth.slice('Bearer '.length);
		try {
			const payload = await (app as any).jwt.verify(token);
			(request as any).user = payload;
		} catch (err) {
			request.log.warn(err);
			return reply.code(401).send({ success: false, message: 'Invalid token' });
		}
	});

	const getUserId = (req: any) => (req.user?.sub as string);



	app.get('/user/profile/:id', async (request, reply) => {
		try {
			const { id } = request.params as { id: string };
			const u = await dbService.getPublicUserById(id);
			if (!u) return reply.code(404).send({ success: false, message: 'User not found' });

			return { success: true, data: { user: u } };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to load profile' });
		}
	});







	app.get('/user/friends', async (request, reply) => {
		const userId = getUserId(request as any);
		try {
			const friends = await dbService.getFriendsWithStatus(userId);
			return { success: true, data: friends };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Could not load friends' });
		}
	});


	app.get('/user/friend-requests', async (request, reply) => {
		const userId = getUserId(request as any);
		const reqs = await userService.getMyFriendRequests(userId);
		return { success: true, data: reqs };
	});


	app.post('/user/friends/:friendId', async (request, reply) => {
		const userId = getUserId(request as any);
		const friendId = (request.params as { friendId: string }).friendId;
		try {
			await userService.sendFriendRequest(userId, friendId);
			return { success: true };
		} catch (err: any) {
			return reply.code(400).send({ success: false, message: err.message });
		}
	});


	app.post('/user/friends/:requesterId/accept', async (request, reply) => {
		const me = getUserId(request as any);
		const requesterId = (request.params as { requesterId: string }).requesterId;
		await userService.acceptFriend(me, requesterId);
		return { success: true };
	});


	app.post('/user/friends/:requesterId/decline', async (request, reply) => {
		const me = getUserId(request as any);
		const requesterId = (request.params as { requesterId: string }).requesterId;
		await userService.declineFriend(me, requesterId);
		return { success: true };
	});


	app.delete('/user/friends/:friendId', async (request, reply) => {
		const userId = getUserId(request as any);
		const friendId = (request.params as { friendId: string }).friendId;
		await userService.removeFriend(userId, friendId);
		return { success: true };
	});






	app.post('/user/status/online', async (request, reply) => {
		const userId = getUserId(request as any);
		try {
			await dbService.setUserStatus(userId, 1);
			return { success: true };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to update status' });
		}
	});


	app.post('/user/status/offline', async (request, reply) => {
		const userId = getUserId(request as any);
		try {
			await dbService.setUserStatus(userId, 0);
			return { success: true };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to update status' });
		}
	});

	app.post('/user/language', async (request, reply) => {
		const userId = getUserId(request as any);

		try {
			const body = request.body as { language?: string };

			const lang = (body.language || '').toLowerCase();


			const allowed = ['en', 'fr', 'es'];
			if (!allowed.includes(lang)) {
				return reply.code(400).send({
					success: false,
					message: 'Invalid language',
				});
			}

			await dbService.setUserLanguage(userId, lang);

			return { success: true };
		} catch (err: any) {
			request.log.error(err);
			return reply
				.code(500)
				.send({ success: false, message: 'Failed to update language' });
		}
	});

	try {
		await app.listen({ port: PORT, host: HOST } as any);
		app.log.info(`user service listening on http://${HOST}:${PORT}`);
	} catch (err) {
		app.log.error(err);
		process.exit(1);
	}
}

start();
