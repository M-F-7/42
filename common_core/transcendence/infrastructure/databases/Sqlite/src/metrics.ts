import client from 'prom-client';
import fs from 'fs';

export const register = new client.Registry();
client.collectDefaultMetrics({ register });

// compteur pour le nombre de requêtes SQL
export const sqlCounter = new client.Counter({
  name: 'sqlite_sql_requests_total',
  help: 'Nombre total de requêtes SQL exécutées',
});

// gauge pour la taille du fichier SQLite
export const dbSizeGauge = new client.Gauge({
  name: 'sqlite_database_size_bytes',
  help: 'Taille du fichier SQLite en bytes',
});

register.registerMetric(sqlCounter);
register.registerMetric(dbSizeGauge);

// mettre à jour la taille toutes les 10 secondes
setInterval(() => {
  try {
    const stats = fs.statSync('./data/transcendence.db'); // chemin vers ton fichier SQLite
    dbSizeGauge.set(stats.size);
  } catch (err) {
    console.error('Erreur lecture taille DB:', err);
  }
}, 10000);
