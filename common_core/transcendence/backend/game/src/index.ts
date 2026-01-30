import Fastify from 'fastify';
import cors from '@fastify/cors';
import xss from 'xss';
import jwtPlugin from '@fastify/jwt';
import { dbService } from './databaseService';

async function start() {
	const app = Fastify({ logger: true });
	const PORT = Number(process.env.GAME_PORT || 4002);
	const HOST = '0.0.0.0';

	await app.register(cors, {
		origin: true,
		credentials: true,
	});

	await app.register(jwtPlugin, {
		secret: process.env.JWT_SECRET || 'super-secret-dev',
	});

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

	app.get('/health', async () => ({ status: 'ok', service: 'game' }));


	app.addHook('onRequest', async (request, reply) => {
		const auth = request.headers.authorization;
		if (request.url === '/game/health') return;
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




	app.post('/game/save', async (request, reply) => {
		try {
			const player1id = (request as any).user?.sub as string;

			const { player1, player2, mode, settings } = request.body as { player1: number; player2: number, mode: string, settings: any };

			if (typeof player1 !== 'number' || typeof player2 !== 'number' || typeof mode !== 'string') {
				return reply.code(400).send({ success: false, message: 'Invalid request body' });
			}
			const gameData = { player1id, score: { player1, player2 }, mode, settings }
			const res = await dbService.createGame(gameData);

			return { success: true, message: `Game state saved for ${player1id} with scores ${player1} - ${player2}`, res };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to load profile' });
		}
	});


	app.get('/game/profile/:id', async (request, reply) => {
		try {
			const { id } = request.params as { id: string };
			const data = await dbService.getGamesByPlayerId(id);

			return { success: true, data };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to load profile' });
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
