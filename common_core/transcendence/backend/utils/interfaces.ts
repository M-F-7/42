export interface User {
  id: string;
  username: string;
  email: string;
  password?: string;
  role: 'user' | 'admin';
  joinDate: Date;
  isOnline: boolean;
  lastActive: Date;
  stats: UserStats;
}

export interface UserStats {
  userId: string;
  gamesPlayed: number;
  gamesWon: number;
  gamesLost: number;
  winRate: number;
  tournamentsPlayed: number;
  tournamentsWon: number;
  currentStreak: number;
  longestWinStreak: number;
  averageGameDuration: number;
  lastActivity: Date;
  rank: string;
  // Legacy fields for compatibility
  wins?: number;
  losses?: number;
  tournaments?: number;
  totalPlayTime?: number;
  longestGame?: number;
  bestStreak?: number;
}

export interface GameSettings {
  ballSpeed: number;
  ballSize: number;
  playerSpeed: number;
  playerSize: number;
  winScore: number;
  aiDifficulty: 'easy' | 'medium' | 'hard' | 'expert';
}

export interface Game {
  id: string;
  player1Id: string;
  player2Id?: string;
  mode: 'pvp' | 'pvia' | 'tournament';
  settings: GameSettings;
  score: {
    player1: number;
    player2: number;
  };
  startTime: Date;
  endTime?: Date;
  duration?: number;
  winner?: string;
  winnerId?: string;
  status: 'waiting' | 'in-progress' | 'completed' | 'abandoned' | 'active';
  tournamentId?: string;
  gameEvents: GameEvent[];
  createdAt: Date;
  finishedAt?: Date;
}

export interface GameEvent {
  type: 'goal' | 'pause' | 'resume' | 'start' | 'end';
  playerId?: string;
  timestamp: Date;
  data?: any;
}

export interface Tournament {
  id: string;
  name: string;
  creatorId: string;
  players: string[];
  maxPlayers: number;
  format: 'single-elimination' | 'double-elimination' | 'round-robin';
  status: 'waiting' | 'in-progress' | 'completed';
  startTime?: Date;
  endTime?: Date;
  winnerId?: string;
  matches: TournamentMatch[];
  settings: GameSettings;
}

export interface TournamentMatch {
  id: string;
  tournamentId: string;
  round: number;
  player1Id: string;
  player2Id: string;
  winnerId?: string;
  gameId?: string;
  status: 'pending' | 'in-progress' | 'completed';
}

export interface ChatMessage {
  id: string;
  senderId: string;
  content: string;
  channelId: string;
  timestamp: Date;
  type: 'normal' | 'system' | 'tournament';
  isGlobal: boolean;
}

export interface ApiResponse<T = any> {
  success: boolean;
  data?: T;
  message?: string;
  error?: string;
  timestamp: Date;
}

export interface LoginRequest {
  username: string;
  password: string;
}

export interface RegisterRequest {
  username: string;
  email: string;
  password: string;
}

export interface CreateGameRequest {
  mode: 'pvp' | 'pvia' | 'tournament';
  settings: GameSettings;
  opponentId?: string;
}

export interface JoinGameRequest {
  gameId: string;
}

export interface CreateTournamentRequest {
  name: string;
  maxPlayers: number;
  format: 'single-elimination' | 'double-elimination' | 'round-robin';
  settings: GameSettings;
}

export interface UserGameSettings {
  id: string;
  userId: string;
  settings: GameSettings;
  presetName?: string;
  createdAt: Date;
  updatedAt: Date;
}

export interface GamePreset {
  name: string;
  displayName: string;
  description: string;
  settings: GameSettings;
}

export interface SaveSettingsRequest {
  settings: GameSettings;
  presetName?: string;
}