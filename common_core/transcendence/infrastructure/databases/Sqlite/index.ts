// index.ts
import Fastify from 'fastify';
import { dbService } from './src/databaseService';
import { register, dbSizeGauge } from './src/metrics';

const fastify = Fastify({ logger: true });
const PORT = 4007;

// on force l’init de la DB
(async () => {
  try {
    await dbService.getAllUsers();
    fastify.log.info('DB initialized ✅');
  } catch (err) {
    // 👉 format que Fastify accepte bien
    fastify.log.error({ err }, 'DB init failed');
  }
})();

fastify.get('/health', async () => {
  return { status: 'ok', service: 'sqlite' };
});

fastify.get('/metrics', async (_, reply) => {
  reply.header('Content-Type', register.contentType);
  return register.metrics();
});



fastify
  .listen({ port: PORT, host: '0.0.0.0' })
  .then(() => fastify.log.info(`SQLite service listening on 0.0.0.0:${PORT}`))
  .catch((err) => {
    fastify.log.error({ err }, 'Failed to start Fastify');
    process.exit(1);
  });
