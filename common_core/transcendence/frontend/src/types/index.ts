

export interface User {
	id: string;
	username: string;
	email?: string;
	avatar_url?: string | null;
	games_played?: number;
	games_won?: number;
	games_lost?: number;
	win_rate?: number;
}

export interface AuthResponse {
	success: boolean;
	message?: string;
	data?: {
		user: User;
		token: string;
	};
}

export interface ApiResponse<T = any> {
	success: boolean;
	message?: string;
	data?: T;
}

export interface ChatMessage {
	id: string;
	username: string;
	content: string;
	timestamp: Date;
	channelId: string;
}

export interface Tournament {
	id: string;
	name: string;
	status: 'pending' | 'active' | 'completed';
	participants: string[];
	maxParticipants: number;
	startDate?: Date;
}

export interface GameSettings {
	ballSpeed: number;
	ballSize: number;
	playerSpeed: number;
	playerSize: number;
	winScore: number;
	aiDifficulty: 'easy' | 'medium' | 'hard' | 'expert';
}

export interface GameStats {
	gamesPlayed: number;
	gamesWon: number;
	gamesLost: number;
	totalScore: number;
	highestScore: number;
	winRate: number;
}

export interface GameResult {
	mode: GameMode;
	settings: GameSettings;
	userId?: string;
	player1: number;
	player2: number;
}

export interface Player {
	x: number;
	y: number;
	width: number;
	height: number;
	speed: number;
	score: number;
}

export interface Ball {
	x: number;
	y: number;
	radius: number;
	speed: number;
	dx: number;
	dy: number;
}


export type GameMode = 'pvp' | 'ai' | 'training' | 'tournament';

export type NotificationType = 'success' | 'error' | 'warning' | 'info';

export interface GameSettingsPreset {
	name: string;
	settings: GameSettings;
}


