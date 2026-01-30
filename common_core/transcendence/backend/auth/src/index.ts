
import Fastify from 'fastify';
import cors from '@fastify/cors';
import jwtPlugin from '@fastify/jwt';
import multipart from '@fastify/multipart';
import fastifyStatic from '@fastify/static';
import path from 'path';
import xss from 'xss';
import fs from 'fs';

import { AuthService } from './authService';
import { dbService } from './databaseService';

async function start() {
	const app = Fastify({ logger: true });
	const PORT = Number(process.env.PORT || 4000);
	const HOST = '0.0.0.0';
	const uploadDir = path.join('/app', 'uploads');

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

	await app.register(multipart);


	await app.register(cors, {
		origin: true,
		credentials: true,
	});


	await app.register(jwtPlugin, {
		secret: process.env.JWT_SECRET || 'super-secret-dev',
	});


	await app.register(fastifyStatic, {
		root: uploadDir,
		prefix: '/uploads/',
	});

	const authService = new AuthService();


	app.get('/health', async () => ({ status: 'ok', service: 'auth' }));



	app.get('/auth/github', (req, res) => {
		const clientId = process.env.GITHUB_CLIENT_ID!;
		const redirectUri = 'https://localhost:3001/auth/github/callback';
		const scope = 'read:user user:email';

		const url =
			`https://github.com/login/oauth/authorize` +
			`?client_id=${clientId}` +
			`&redirect_uri=${encodeURIComponent(redirectUri)}` +
			`&scope=${encodeURIComponent(scope)}`;

		res.redirect(url);
	});


	app.get('/auth/github/callback', async (req, res) => {

		const { code } = req.query as { code?: string };

		if (!code) {
			return res
				.status(400)
				.send({ success: false, message: 'Missing "code" from GitHub OAuth callback' });
		}

		const clientId = process.env.GITHUB_CLIENT_ID!;
		const clientSecret = process.env.GITHUB_CLIENT_SECRET!;


		const tokenRes = await fetch('https://github.com/login/oauth/access_token', {
			method: 'POST',
			headers: {
				Accept: 'application/json',
				'Content-Type': 'application/json',
			},
			body: JSON.stringify({
				client_id: clientId,
				client_secret: clientSecret,
				code,
			}),
		});

		const tokenJson = await tokenRes.json();
		const accessToken = tokenJson.access_token;

		if (!accessToken) {
			req.log.error(tokenJson);
			return res
				.status(400)
				.send({ success: false, message: 'Could not get access token from GitHub' });
		}


		const userRes = await fetch('https://api.github.com/user', {
			headers: {
				Authorization: `Bearer ${accessToken}`,
				'User-Agent': 'gpoat-app',
			},
		});
		const ghUser = await userRes.json();


		const emailRes = await fetch('https://api.github.com/user/emails', {
			headers: {
				Authorization: `Bearer ${accessToken}`,
				'User-Agent': 'gpoat-app',
			},
		});
		const emails = await emailRes.json();
		const primaryEmail =
			emails.find((e: any) => e.primary && e.verified)?.email ??
			emails[0]?.email ??
			null;

		const githubId = String(ghUser.id);


		let user = await dbService.findUserByGithubIdOrEmail(githubId, primaryEmail);
		if (!user) {
			user = await dbService.createUserFromGithub({
				githubId,
				username: ghUser.login,
				email: primaryEmail,
				avatar_url: ghUser.avatar_url,
			});
		}


		const token = app.jwt.sign({
			sub: user.id,
			username: user.username,
			email: user.email ?? undefined,
		});


		const redirectFront = `https://localhost:4443/?oauthToken=${token}`;
		res.redirect(redirectFront);
	});




	app.post('/auth/login', async (request, reply) => {
		const body = request.body as { username: string; password: string };
		const result = await authService.login(body.username, body.password);
		if (!result.success) {
			return reply.code(401).send(result);
		}
		return result;
	});


	app.post('/auth/register', async (request, reply) => {
		const body = request.body as { username: string; password: string; email: string };
		const result = await authService.register(body.username, body.password, body.email);
		if (!result.success) {
			return reply.code(400).send(result);
		}
		return result;
	});


	app.get('/auth/me', async (request, reply) => {
		try {
			const auth = request.headers.authorization;
			if (!auth?.startsWith('Bearer ')) {
				return reply.code(401).send({ success: false, message: 'Missing token' });
			}

			const token = auth.slice('Bearer '.length);
			const payload = app.jwt.verify(token) as { sub: string };

			const user = await dbService.getUserById(payload.sub);
			if (!user) {
				return reply.code(404).send({ success: false, message: 'User not found' });
			}

			return {
				success: true,
				data: {
					user: {
						id: user.id,
						username: user.username,
						email: user.email,
						avatar_url: user.avatar_url ?? null,
						games_played: user.games_played ?? 0,
						games_won: user.games_won ?? 0,
						games_lost: user.games_lost ?? 0,
						win_rate: user.win_rate ?? 0,
						language: user.language,
					},
				},
			};
		} catch (err) {
			app.log.error(err);
			return reply.code(401).send({ success: false, message: 'Invalid token' });
		}
	});


	app.put('/auth/me', async (request, reply) => {
		try {
			const auth = request.headers.authorization;
			if (!auth?.startsWith('Bearer ')) {
				return reply.code(401).send({ success: false, message: 'Missing token' });
			}

			const token = auth.slice('Bearer '.length);
			const payload = app.jwt.verify(token) as { sub: string };

			const body = request.body as { username?: string; email?: string };

			const user = await dbService.getUserById(payload.sub);
			if (!user) {
				return reply.code(404).send({ success: false, message: 'User not found' });
			}

			const newUsername = body.username ?? user.username;
			const newEmail = body.email ?? user.email;

			await dbService.updateUser(payload.sub, {
				username: newUsername,
				email: newEmail,
			});

			return reply.send({
				success: true,
				data: {
					user: {
						id: payload.sub,
						username: newUsername,
						email: newEmail,
						avatar_url: user.avatar_url ?? null,
						games_played: user.games_played ?? 0,
						games_won: user.games_won ?? 0,
						games_lost: user.games_lost ?? 0,
						win_rate: user.win_rate ?? 0,
					},
				},
			});
		} catch (err) {
			app.log.error(err);
			return reply.code(500).send({ success: false, message: 'Could not update profile' });
		}
	});


	app.put('/auth/password', async (request, reply) => {
		try {
			const auth = request.headers.authorization;
			if (!auth?.startsWith('Bearer ')) {
				return reply.code(401).send({ success: false, message: 'Missing token' });
			}

			const token = auth.slice('Bearer '.length);
			const payload = app.jwt.verify(token) as { sub: string };

			const body = request.body as {
				currentPassword: string;
				newPassword: string;
			};

			if (!body.currentPassword || !body.newPassword) {
				return reply.code(400).send({ success: false, message: 'Missing fields' });
			}

			const authService = new AuthService();
			const ok = await authService.changePassword(payload.sub, body.currentPassword, body.newPassword);

			if (!ok) {
				return reply.code(400).send({ success: false, message: 'Current password invalid' });
			}

			return { success: true };
		} catch (err) {
			request.log.error(err);
			return reply.code(500).send({ success: false, message: 'Server error' });
		}
	});


	app.post('/auth/avatar', async (request, reply) => {
		const auth = request.headers.authorization;
		if (!auth?.startsWith('Bearer ')) {
			return reply.code(401).send({ success: false, message: 'Missing token' });
		}

		const token = auth.slice('Bearer '.length);
		const payload = app.jwt.verify(token) as { sub: string };

		if (!fs.existsSync(uploadDir)) {
			fs.mkdirSync(uploadDir, { recursive: true });
		}

		const parts = request.parts();

		for await (const part of parts) {
			if (part.file) {

				const filename = `avatar-${payload.sub}-${Date.now()}.png`;
				const filePath = path.join(uploadDir, filename);
				const writeStream = fs.createWriteStream(filePath);
				await part.file.pipe(writeStream);

				const publicUrl = `/uploads/${filename}`;
				await dbService.updateUserAvatar(payload.sub, publicUrl);

				return reply.send({
					success: true,
					data: { avatarUrl: publicUrl },
				});
			}
		}

		return reply.code(400).send({ success: false, message: 'No file uploaded' });
	});

	try {
		await app.listen({ port: PORT, host: HOST });
		app.log.info(`auth service listening on http://${HOST}:${PORT}`);
	} catch (err) {
		app.log.error(err);
		process.exit(1);
	}
}

start();
