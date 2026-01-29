import express from 'express';
import { createServer } from 'http';
import { Server } from 'socket.io';
import cors from 'cors';
import { config } from './gateway/src/config.js';
import { authService } from './services/authService.js';
import { gameService } from './services/gameService.js';
import { tournamentService } from './services/tournamentService.js';
import { chatService } from './services/chatService.js';
import { statsService } from './services/statsService.js';
import { settingsService } from './services/settingsService.js';
import { dbService } from './services/databaseService.js';
import type { 
  LoginRequest, 
  RegisterRequest, 
  CreateGameRequest, 
  CreateTournamentRequest 
} from './utils/interfaces.js';

const app = express();
const server = createServer(app);
const io = new Server(server, {
  cors: {
    origin: config.server.corsOrigin,
    methods: ["GET", "POST"]
  }
});

// Middleware
app.use(cors({
  origin: config.server.corsOrigin
}));
app.use(express.json());

// Health check
app.get('/health', (req, res) => {
  res.json({ status: 'ok', timestamp: new Date() });
});

// Auth routes
app.post('/api/auth/register', async (req, res) => {
  try {
    const userData: RegisterRequest = req.body;
    const result = await authService.register(userData);
    res.status(result.success ? 201 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/auth/login', async (req, res) => {
  try {
    const credentials: LoginRequest = req.body;
    const result = await authService.login(credentials);
    res.status(result.success ? 200 : 401).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

// Game routes
app.post('/api/games', async (req, res) => {
  try {
    const gameData: CreateGameRequest = req.body;
    const { userId } = req.body; // Should come from auth middleware
    const result = await gameService.createGame(userId, gameData);
    res.status(result.success ? 201 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/games/active', async (req, res) => {
  try {
    const result = await gameService.getActiveGames();
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/games/:gameId', async (req, res) => {
  try {
    const { gameId } = req.params;
    const result = await gameService.getGame(gameId);
    res.status(result.success ? 200 : 404).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/games/:gameId/join', async (req, res) => {
  try {
    const { gameId } = req.params;
    const { userId } = req.body; // Should come from auth middleware
    const result = await gameService.joinGame(gameId, userId);
    res.status(result.success ? 200 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

// Tournament routes
app.post('/api/tournaments', async (req, res) => {
  try {
    const tournamentData: CreateTournamentRequest = req.body;
    const { userId } = req.body; // Should come from auth middleware
    const result = await tournamentService.createTournament(userId, tournamentData);
    res.status(result.success ? 201 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/tournaments/active', async (req, res) => {
  try {
    const result = await tournamentService.getActiveTournaments();
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/tournaments/:tournamentId', async (req, res) => {
  try {
    const { tournamentId } = req.params;
    const result = await tournamentService.getTournament(tournamentId);
    res.status(result.success ? 200 : 404).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/tournaments/:tournamentId/join', async (req, res) => {
  try {
    const { tournamentId } = req.params;
    const { userId } = req.body; // Should come from auth middleware
    const result = await tournamentService.joinTournament(userId, tournamentId);
    res.status(result.success ? 200 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

// Stats routes
app.get('/api/stats/user/:userId', async (req, res) => {
  try {
    const { userId } = req.params;
    const result = await statsService.getUserStats(userId);
    res.status(result.success ? 200 : 404).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/stats/global', async (req, res) => {
  try {
    const result = await statsService.getGlobalStats();
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/stats/leaderboard', async (req, res) => {
  try {
    const limit = parseInt(req.query.limit as string) || 10;
    const result = await statsService.getLeaderboard(limit);
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

// Chat routes
app.get('/api/chat/messages', async (req, res) => {
  try {
    const channelId = req.query.channel as string || 'general';
    const limit = parseInt(req.query.limit as string) || 50;
    const result = await chatService.getChannelMessages(channelId, limit);
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/chat/online-users', async (req, res) => {
  try {
    const result = await chatService.getOnlineUsers();
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

// Settings routes
app.get('/api/settings/:userId', async (req, res) => {
  try {
    const { userId } = req.params;
    const result = await settingsService.getUserSettings(userId);
    res.status(result.success ? 200 : 404).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/settings/:userId', async (req, res) => {
  try {
    const { userId } = req.params;
    const settingsRequest = req.body;
    const result = await settingsService.saveUserSettings(userId, settingsRequest);
    res.status(result.success ? 200 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/settings/:userId/preset/:presetName', async (req, res) => {
  try {
    const { userId, presetName } = req.params;
    const result = await settingsService.loadPreset(userId, presetName);
    res.status(result.success ? 200 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/settings/:userId/reset', async (req, res) => {
  try {
    const { userId } = req.params;
    const result = await settingsService.resetToDefault(userId);
    res.status(result.success ? 200 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/settings/presets', async (req, res) => {
  try {
    const result = await settingsService.getAvailablePresets();
    res.json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/settings/presets/:presetName', async (req, res) => {
  try {
    const { presetName } = req.params;
    const result = await settingsService.getPresetByName(presetName);
    res.status(result.success ? 200 : 404).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.get('/api/settings/:userId/export', async (req, res) => {
  try {
    const { userId } = req.params;
    const result = await settingsService.exportUserSettings(userId);
    res.status(result.success ? 200 : 404).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

app.post('/api/settings/:userId/import', async (req, res) => {
  try {
    const { userId } = req.params;
    const importData = req.body;
    const result = await settingsService.importUserSettings(userId, importData);
    res.status(result.success ? 200 : 400).json(result);
  } catch (error) {
    res.status(500).json({ success: false, error: 'Internal server error' });
  }
});

// Socket.IO connection handling
io.on('connection', (socket) => {

  // Handle user authentication
  socket.on('authenticate', async (token: string) => {
    try {
      const result = await authService.verifyToken(token);
      if (result.success && result.data) {
        socket.data.userId = result.data.id;
        socket.data.username = result.data.username;
        
        // Update user online status
        await dbService.updateUser(result.data.id, { 
          isOnline: true, 
          lastActive: new Date() 
        });
        
        socket.emit('authenticated', { success: true, user: result.data });
        socket.broadcast.emit('user-online', { userId: result.data.id, username: result.data.username });
      } else {
        socket.emit('authenticated', { success: false, error: 'Invalid token' });
      }
    } catch (error) {
      socket.emit('authenticated', { success: false, error: 'Authentication failed' });
    }
  });

  // Handle chat messages
  socket.on('send-message', async (data: { content: string; channelId?: string }) => {
    if (!socket.data.userId) {
      socket.emit('error', { message: 'Not authenticated' });
      return;
    }

    try {
      const result = await chatService.sendMessage(
        socket.data.userId, 
        data.content, 
        data.channelId || 'general'
      );
      
      if (result.success) {
        // Broadcast message to all users in the channel
        io.emit('new-message', result.data);
      } else {
        socket.emit('error', { message: result.error });
      }
    } catch (error) {
      socket.emit('error', { message: 'Failed to send message' });
    }
  });

  // Handle game events
  socket.on('join-game', async (gameId: string) => {
    if (!socket.data.userId) {
      socket.emit('error', { message: 'Not authenticated' });
      return;
    }

    try {
      const result = await gameService.joinGame(gameId, socket.data.userId);
      if (result.success) {
        socket.join(`game-${gameId}`);
        socket.to(`game-${gameId}`).emit('player-joined', {
          gameId,
          playerId: socket.data.userId,
          username: socket.data.username
        });
        socket.emit('game-joined', result.data);
      } else {
        socket.emit('error', { message: result.error });
      }
    } catch (error) {
      socket.emit('error', { message: 'Failed to join game' });
    }
  });

  // Handle game updates (ball position, paddle position, etc.)
  socket.on('game-update', (data: { gameId: string; update: any }) => {
    socket.to(`game-${data.gameId}`).emit('game-update', data.update);
  });

  // Handle scoring
  socket.on('score-update', async (data: { gameId: string; playerId: string; score: any }) => {
    try {
      const result = await gameService.updateGameScore(data.gameId, data.playerId, data.score);
      if (result.success) {
        io.to(`game-${data.gameId}`).emit('score-updated', result.data);
      }
    } catch (error) {
      socket.emit('error', { message: 'Failed to update score' });
    }
  });

  // Handle disconnect
  socket.on('disconnect', async () => {
    
    if (socket.data.userId) {
      // Update user offline status
      await dbService.updateUser(socket.data.userId, { 
        isOnline: false, 
        lastActive: new Date() 
      });
      
      socket.broadcast.emit('user-offline', { 
        userId: socket.data.userId, 
        username: socket.data.username 
      });
    }
  });
});

// Start server
const PORT = config.server.port;
server.listen(PORT, () => {
});