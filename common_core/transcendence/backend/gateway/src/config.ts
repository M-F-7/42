import dotenv from 'dotenv';

dotenv.config();

export const config = {
  server: {
    port: parseInt(process.env.PORT || '3001'),
    host: process.env.HOST || 'localhost',
    environment: process.env.NODE_ENV || 'development',
    corsOrigin: ['http://localhost:5173', 'http://localhost:8080', 'http://localhost:8082', 'http://localhost:3000'],
    cors: {
      origin: ['http://localhost:5173', 'http://localhost:8080', 'http://localhost:8082', 'http://localhost:3000'],
      credentials: true
    }
  },
  
  jwt: {
    secret: process.env.JWT_SECRET || 'pong-secret-key-dev',
    expiresIn: process.env.JWT_EXPIRES_IN || '24h'
  },
  
  bcrypt: {
    saltRounds: parseInt(process.env.BCRYPT_SALT_ROUNDS || '10')
  },
  
  game: {
    maxGamesPerUser: parseInt(process.env.MAX_GAMES_PER_USER || '5'),
    gameTimeout: parseInt(process.env.GAME_TIMEOUT || '300000'), // 5 minutes
    tournamentTimeout: parseInt(process.env.TOURNAMENT_TIMEOUT || '1800000') // 30 minutes
  },
  
  chat: {
    maxMessageLength: parseInt(process.env.MAX_MESSAGE_LENGTH || '500'),
    rateLimitMessages: parseInt(process.env.RATE_LIMIT_MESSAGES || '10'),
    rateLimitWindow: parseInt(process.env.RATE_LIMIT_WINDOW || '60000') // 1 minute
  },
  
  environment: process.env.NODE_ENV || 'development',
  
  isDevelopment: () => config.environment === 'development',
  isProduction: () => config.environment === 'production'
};