import fs from 'fs';
import Fastify from 'fastify';
import cors from '@fastify/cors';
import httpProxy from '@fastify/http-proxy';
import fastifyJwt from '@fastify/jwt';
import xss from 'xss';
import { config } from './config';

const app = Fastify({

	https: {
		key: fs.readFileSync('./data/certs/server.key'),
		cert: fs.readFileSync('./data/certs/server.crt')
	}
});

app.register(cors, {
	origin: [
		'https://localhost',
		'https://localhost:4443',
		'https://localhost:443',
		'http://localhost',
	],
	methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'],
	allowedHeaders: ['Content-Type', 'Authorization'],
	credentials: true,
});

app.register(fastifyJwt, {
	secret: process.env.JWT_SECRET || 'supersecretkeychangeme',
});

app.addHook('onRequest', async (request, reply) => {
	const url = request.raw.url || '';

	if (url === '/health') return;
	if (url.startsWith('/auth')) return;
	if (url.startsWith('/uploads/')) return;
	if (url.startsWith("/injection")) return;

	try {
		const user = await request.jwtVerify();
		request.user = user;
	} catch (err) {
		request.log.warn({ err }, 'JWT invalid');
		return reply.code(401).send({ success: false, message: 'Unauthorized' });
	}
});



app.addHook('preValidation', async (request, reply) => {
	const dangerous = [
		/<script.*?>/i,
		/javascript:/i,
		/onerror=/i,
		/onclick=/i,
		/onload=/i,
	];

	const scan = (value: unknown): boolean => {
		if (typeof value === 'string') {
			for (const pattern of dangerous) if (pattern.test(value)) return true;
			return false;
		}















		return false;
	};

	if (request.method !== 'POST') return;

	const toScan = [request.body, request.params, request.query];
	console.log(request.body);
	for (const part of toScan) {
		if (part && scan(part)) {
			request.log.warn('XSS detected in request payload');
			return reply.code(400).send({ ok: false, message: 'XSS detected' });
		}
	}
});

























































app.register(httpProxy, {
	upstream: 'http://auth:4000',
	prefix: '/auth',
	rewritePrefix: '/auth',
});


app.register(httpProxy, {
	upstream: 'http://auth:4000',
	prefix: '/uploads',
	rewritePrefix: '/uploads',
});


app.register(httpProxy, {
	upstream: 'http://user:4006',
	prefix: '/user',
	rewritePrefix: '/user',
});


app.register(httpProxy, {
	upstream: 'http://game:4002',
	prefix: '/game',
	rewritePrefix: '/game',
});

app.register(httpProxy, {
	upstream: 'http://tournaments:4005',
	prefix: '/tournaments',
	rewritePrefix: '/tournaments',
});

const port = config.server.port;
const host = '0.0.0.0';

app.get('/health', async () => ({ status: 'ok' }));





app
	.listen({ port, host })
	.then(() => {
		app.log.info(`Gateway running on https://${host}:${port}`);
	})
	.catch((err) => {
		app.log.error(err);
		process.exit(1);
	});
