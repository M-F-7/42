
import Fastify from 'fastify';
import cors from '@fastify/cors';
import jwtPlugin from '@fastify/jwt';
import xss from 'xss';
import { dbService } from './databaseService';

async function start() {
	const app = Fastify({ logger: true });
	const PORT = Number(process.env.TOURNAMENTS_PORT || 7777);
	const HOST = '0.0.0.0';

	await app.register(cors, {
		origin: true,
		credentials: true,
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

	await app.register(jwtPlugin, {
		secret: process.env.JWT_SECRET || 'super-secret-dev',
	});



	app.get('/tournaments/health', async () => ({ status: 'ok', service: 'tournaments' }));


	app.addHook('onRequest', async (request, reply) => {
		const auth = request.headers.authorization;
		if (request.url === '/tournaments/health') return;
		if (!request.url.startsWith('/tournaments/')) {
			return;
		}
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


	app.addContentTypeParser('application/json', { parseAs: 'string' }, (req, body, done) => {
		try {
			const json = JSON.parse(body as string);
			done(null, json);
		} catch (err) {
			done(new Error('Invalid JSON'));
		}
	});


	app.post('/tournaments/create', {
		schema: {
			body: {
				type: 'object',
				required: ['name', 'players', 'settings'],
				properties: {
					name: { type: 'string', minLength: 1, maxLength: 100 },
					players: {
						type: 'array',
						items: { type: 'string', minLength: 1, maxLength: 100 },
						minItems: 4,
						maxItems: 4,
						uniqueItems: true
					},
					settings: { type: 'object' }
				}
			}
		}
	}, async (request, reply) => {
		try {
			const userId = (request as any).user?.sub as string;
			const { name, players, settings } = request.body as { name: string, players: string[], settings: any };

			const data = await dbService.createTournament({ userId, name, players, settings });
			return { success: true, message: `Tournament '${name}' created for user ${userId} with players ${JSON.stringify(players)}`, data };
		} catch (err: any) {
			-
				request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to load profile' });
		}
	});


	app.post("/tournaments/update/:id", {
		schema: {
			body: { type: "string", minLength: 3, maxLength: 100, pattern: "^[0-9]{1,3}:[0-9]{1,3}$" },
		}
	}, async (request, reply) => {

		try {
			const { id } = request.params as { id: string };
			const creator_id = (request as any).user?.sub as string;
			const [score1, score2] = (request.body as string).split(":").map(s => parseInt(s, 10));
			const tournament = await dbService.getTournamentById(id);

			if (score1 == score2)
				return reply.code(400).send({ success: false, message: `Scores cannot be equal in tournament '${id}'` });
			if (!tournament)
				return reply.code(404).send({ success: false, message: `Tournament '${id}' not found` });
			if (tournament.creator_id !== creator_id)
				return reply.code(403).send({ success: false, message: `Not authorized to update tournament '${id}'` });
			if (tournament.status === 'completed')
				return reply.code(400).send({ success: false, message: `Tournament '${id}' is already completed` });

			tournament.matches.push(request.body as string);
			const res = await dbService.updateTournamentScores(id, tournament.matches);

			return { success: true, message: `Tournament '${id}' updated with new score ${request.body as string}`, res };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to update tournament' });
		}
	});

	app.get('/tournaments/profile/:id', async (request, reply) => {
		try {
			const { id } = request.params as { id: string };
			const data = await dbService.getUserTournaments(id);

			return { success: true, data };
		} catch (err: any) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Failed to load profile' });
		}
	});

	try {
		await app.listen({ port: PORT, host: HOST } as any);
		app.log.info(`tournaments service listening on http://${HOST}:${PORT}`);
	} catch (err) {
		app.log.error(err);
		process.exit(1);
	}
}

start();
