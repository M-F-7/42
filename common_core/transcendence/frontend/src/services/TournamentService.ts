import type { Tournament, ApiResponse, GameSettings } from '../types';
import { ApiService } from './ApiService';
import { NotificationService } from './NotificationService';
import { SettingsService } from './SettingsService';

export type LocalTournamentRound = 'semi_final_1' | 'semi_final_2' | 'final';

export interface LocalTournamentPlayer {
	id: string;
	name: string;
	seed: number;
}

export interface LocalTournamentMatch {
	id: string;
	round: LocalTournamentRound;
	player1: LocalTournamentPlayer | null;
	player2: LocalTournamentPlayer | null;
	score1: number | null;
	score2: number | null;
	winnerId: string | null;
}

export interface LocalTournamentState {
	id: string;
	backendId?: string;
	name: string;
	players: LocalTournamentPlayer[];
	matches: LocalTournamentMatch[];
	status: 'not_started' | 'in_progress' | 'finished';
}

export class TournamentService {
	private static instance: TournamentService;
	private api: ApiService;
	private notification: NotificationService;
	private tournaments: Tournament[] = [];
	private userTournaments: any[] = [];
	private localTournament: LocalTournamentState | null = null;


	private constructor() {
		this.api = ApiService.getInstance();
		this.notification = NotificationService.getInstance();
	}

	static getInstance(): TournamentService {
		if (!TournamentService.instance) {
			TournamentService.instance = new TournamentService();
		}
		return TournamentService.instance;
	}

	async fetchTournaments(): Promise<Tournament[]> {
		try {
			const response: ApiResponse<Tournament[]> = await this.api.get('/tournaments');

			if (response.success && response.data) {
				this.tournaments = response.data;
				return response.data;
			}
			return [];
		} catch (error) {
			console.error('Error fetching tournaments:', error);
			return [];
		}
	}

	async createTournament(name: string, maxParticipants: number): Promise<boolean> {
		try {
			const response: ApiResponse<Tournament> = await this.api.post('/tournaments', {
				name,
				maxParticipants,
			});

			if (response.success) {
				this.notification.show('Tournament created successfully!', 'success');
				await this.fetchTournaments();
				return true;
			} else {
				this.notification.show('Failed to create tournament', 'error');
				return false;
			}
		} catch (error) {
			console.error('Error creating tournament:', error);
			this.notification.show('Error creating tournament', 'error');
			return false;
		}
	}

	async joinTournament(tournamentId: string): Promise<boolean> {
		try {
			const response: ApiResponse = await this.api.post(
				`/tournaments/${tournamentId}/join`
			);

			if (response.success) {
				this.notification.show(`Joined tournament successfully!`, 'success');
				await this.fetchTournaments();
				return true;
			} else {
				this.notification.show('Failed to join tournament', 'error');
				return false;
			}
		} catch (error) {
			console.error('Error joining tournament:', error);
			this.notification.show('Error joining tournament', 'error');
			return false;
		}
	}

	async leaveTournament(tournamentId: string): Promise<boolean> {
		try {
			const response: ApiResponse = await this.api.post(
				`/tournaments/${tournamentId}/leave`
			);

			if (response.success) {
				this.notification.show('Left tournament successfully!', 'success');
				await this.fetchTournaments();
				return true;
			} else {
				this.notification.show('Failed to leave tournament', 'error');
				return false;
			}
		} catch (error) {
			console.error('Error leaving tournament:', error);
			this.notification.show('Error leaving tournament', 'error');
			return false;
		}
	}

	getTournaments(): Tournament[] {
		return this.tournaments;
	}

	getTournamentById(id: string): Tournament | undefined {
		return this.tournaments.find(t => t.id === id);
	}

	async createLocalTournament(
		name: string,
		playerNames: string[]
	): Promise<LocalTournamentState> {
		const trimmed = playerNames.map((p) => p.trim()).filter(Boolean);

		if (trimmed.length !== 4) {
			this.notification.show('You must have exactly 4 players.', 'error');
			throw new Error('INVALID_PLAYERS_COUNT');
		}

		const players: LocalTournamentPlayer[] = trimmed.map((n, idx) => ({
			id: `P${idx + 1}`,
			name: n,
			seed: idx + 1,
		}));

		const matches: LocalTournamentMatch[] = [
			{
				id: 'M1',
				round: 'semi_final_1',
				player1: players[0],
				player2: players[1],
				score1: null,
				score2: null,
				winnerId: null,
			},
			{
				id: 'M2',
				round: 'semi_final_2',
				player1: players[2],
				player2: players[3],
				score1: null,
				score2: null,
				winnerId: null,
			},
			{
				id: 'M3',
				round: 'final',
				player1: null,
				player2: null,
				score1: null,
				score2: null,
				winnerId: null,
			},
		];

		const state: LocalTournamentState = {
			id: `local-${Date.now()}`,
			name,
			players,
			matches,
			status: 'not_started',
		};

		try {
			const settingsService = SettingsService.getInstance();
			const settings = settingsService.getSettings
				? settingsService.getSettings()
				: {};

			const payload = {
				name: state.name,
				players: state.players.map((p) => p.name),
				settings,
			};

			const res: any = await this.api.post('/tournaments/create', payload);

			if (!res || res.statusCode >= 500 || res.success === false) {
				const msg =
					(res && res.message) ||
					'Failed to create tournament on server.';
				this.notification.show(msg, 'error');
				throw new Error('BACKEND_CREATE_FAILED');
			}

		} catch (err) {
			console.error('Failed to create tournament on server', err);
			this.notification.show(
				'Server unavailable. Tournament was not created.',
				'error'
			);
			throw new Error('NETWORK_OR_BACKEND_ERROR');
		}

		this.localTournament = state;
		this.notification.show('Tournament created & saved on server!', 'success');
		return state;
	}



	private async syncLocalTournamentToBackend(state: LocalTournamentState): Promise<void> {
		try {
			const settingsService = SettingsService.getInstance();
			const settings = settingsService.getSettings
				? settingsService.getSettings()
				: {};

			const payload = {
				name: state.name,
				players: state.players.map((p) => p.name),
				settings,
			};

			const res: any = await this.api.post('/tournaments/create', payload);

			if (res && res.success && res.data && state === this.localTournament) {
				state.backendId = res.data.id;
				this.notification.show('Tournament saved on server', 'success');
			} else {
				this.notification.show(
					'Tournament created locally, but failed to save on server',
					'error'
				);
			}
		} catch (err) {
			console.error('syncLocalTournamentToBackend error', err);
			this.notification.show(
				'Tournament created locally, but server is unreachable',
				'error'
			);
		}
	}



	getLocalTournament(): LocalTournamentState | null {
		return this.localTournament;
	}

	resetLocalTournament(): void {
		this.localTournament = null;
	}

	getCurrentLocalMatch(): LocalTournamentMatch | null {
		if (!this.localTournament) return null;
		return (
			this.localTournament.matches.find(
				(m) => !m.winnerId && m.player1 && m.player2
			) || null
		);
	}

	async fetchUserTournaments(userId: string): Promise<any[]> {
		try {
			const res: any = await this.api.get(`/tournaments/profile/${userId}`);

			if (res && res.success && Array.isArray(res.data)) {
				this.userTournaments = res.data;
				return res.data;
			}
			this.userTournaments = [];
			return [];
		} catch (err) {
			console.error('Error fetching user tournaments', err);
			this.userTournaments = [];
			return [];
		}
	}

	getUserTournaments(): any[] {
		return this.userTournaments;
	}

	getUserTournamentById(id: string): any | undefined {
		return this.userTournaments.find((t) => t.id === id);
	}



	updateLocalMatchScore(
		matchId: string,
		score1: number,
		score2: number
	): LocalTournamentState | null {
		if (!this.localTournament) return null;

		const t = this.localTournament;
		const match = t.matches.find((m) => m.id === matchId);
		if (!match || !match.player1 || !match.player2) return t;

		if (score1 === score2) {
			this.notification.show('No draw allowed in Pong, pick a winner.', 'error');
			return t;
		}

		match.score1 = score1;
		match.score2 = score2;
		match.winnerId = score1 > score2 ? match.player1.id : match.player2.id;

		if (match.round === 'semi_final_1' || match.round === 'semi_final_2') {
			const semi1 = t.matches.find((m) => m.round === 'semi_final_1')!;
			const semi2 = t.matches.find((m) => m.round === 'semi_final_2')!;
			const final = t.matches.find((m) => m.round === 'final')!;

			if (semi1.winnerId && semi2.winnerId) {
				const w1 = t.players.find((p) => p.id === semi1.winnerId)!;
				const w2 = t.players.find((p) => p.id === semi2.winnerId)!;
				final.player1 = w1;
				final.player2 = w2;
				t.status = 'in_progress';
			} else {
				t.status = 'in_progress';
			}
		} else if (match.round === 'final') {
			t.status = 'finished';
			this.notification.show('Tournament finished! GG!', 'success');
		}


		this.syncMatchScoreToBackend(t, score1, score2).catch((err) => {
			console.error('Failed to sync match score', err);
		});

		return t;
	}

	private async syncMatchScoreToBackend(
		state: LocalTournamentState,
		score1: number,
		score2: number
	): Promise<void> {
		if (!state.backendId) {
			return;
		}

		try {
			const body = `${score1}:${score2}`;

			await this.api.post(`/tournaments/update/${state.backendId}`, body);
		} catch (err) {
			console.error('syncMatchScoreToBackend error', err);
			this.notification.show(
				'Failed to sync match score to server (local bracket is still updated).',
				'error'
			);
		}
	}

	hydrateLocalFromBackendRecord(record: any): LocalTournamentState {

		let playersNames: string[] = [];
		if (Array.isArray(record.players)) {
			playersNames = record.players;
		} else if (typeof record.players === 'string') {
			try {
				const parsed = JSON.parse(record.players);
				if (Array.isArray(parsed)) playersNames = parsed;
			} catch {

			}
		}

		const trimmed = playersNames.map((p) => String(p).trim()).filter(Boolean).slice(0, 4);

		const players: LocalTournamentPlayer[] = trimmed.map((name, idx) => ({
			id: `P${idx + 1}`,
			name,
			seed: idx + 1,
		}));


		while (players.length < 4) {
			const idx = players.length;
			players.push({
				id: `P${idx + 1}`,
				name: `Player ${idx + 1}`,
				seed: idx + 1,
			});
		}


		let scores: string[] = [];
		if (Array.isArray(record.matches)) {
			scores = record.matches;
		} else if (typeof record.matches === 'string') {
			try {
				const parsed = JSON.parse(record.matches);
				if (Array.isArray(parsed)) scores = parsed;
			} catch {

			}
		}

		const parseScore = (s?: string) => {
			if (!s) return { s1: null as number | null, s2: null as number | null };
			const [a, b] = s.split(':');
			const n1 = Number(a);
			const n2 = Number(b);
			return {
				s1: Number.isFinite(n1) ? n1 : null,
				s2: Number.isFinite(n2) ? n2 : null,
			};
		};

		const m1Score = parseScore(scores[0]);
		const m2Score = parseScore(scores[1]);

		const hasFinal = scores.length >= 3;
		const finalScore = hasFinal ? parseScore(scores[2]) : { s1: null, s2: null };


		const m1: LocalTournamentMatch = {
			id: 'M1',
			round: 'semi_final_1',
			player1: players[0] || null,
			player2: players[1] || null,
			score1: m1Score.s1,
			score2: m1Score.s2,
			winnerId:
				m1Score.s1 != null && m1Score.s2 != null
					? m1Score.s1 > m1Score.s2
						? players[0]?.id ?? null
						: players[1]?.id ?? null
					: null,
		};

		const m2: LocalTournamentMatch = {
			id: 'M2',
			round: 'semi_final_2',
			player1: players[2] || null,
			player2: players[3] || null,
			score1: m2Score.s1,
			score2: m2Score.s2,
			winnerId:
				m2Score.s1 != null && m2Score.s2 != null
					? m2Score.s1 > m2Score.s2
						? players[2]?.id ?? null
						: players[3]?.id ?? null
					: null,
		};

		const winnerSemi1 = m1.winnerId
			? players.find((p) => p.id === m1.winnerId) ?? null
			: null;
		const winnerSemi2 = m2.winnerId
			? players.find((p) => p.id === m2.winnerId) ?? null
			: null;

		const m3: LocalTournamentMatch = {
			id: 'M3',
			round: 'final',
			player1: winnerSemi1,
			player2: winnerSemi2,
			score1: finalScore.s1,
			score2: finalScore.s2,
			winnerId:
				hasFinal &&
					finalScore.s1 != null &&
					finalScore.s2 != null &&
					winnerSemi1 &&
					winnerSemi2
					? finalScore.s1 > finalScore.s2
						? winnerSemi1.id
						: winnerSemi2.id
					: null,
		};


		let status: LocalTournamentState['status'];

		if (record.winner_id || record.status === 'completed' || record.status === 'finished') {
			status = 'finished';
		} else if (m3.winnerId) {
			status = 'finished';
		} else if (m1.winnerId || m2.winnerId || record.status === 'in-progress' || record.status === 'in_progress') {
			status = 'in_progress';
		} else {
			status = 'not_started';
		}
		const state: LocalTournamentState = {
			id: `local-${record.id}`,
			backendId: record.id,
			name: record.name ?? 'Tournament',
			players,
			matches: [m1, m2, m3],
			status,
		};

		try {
			let rawSettings = record.settings;

			if (rawSettings) {
				const parsed =
					typeof rawSettings === 'string' ? JSON.parse(rawSettings) : rawSettings;

				const settingsService = SettingsService.getInstance();

				const keys: (keyof GameSettings)[] = [
					'ballSpeed',
					'ballSize',
					'playerSpeed',
					'playerSize',
					'winScore',
					'aiDifficulty',
				];

				for (const key of keys) {
					if (parsed[key] !== undefined) {
						let value = parsed[key];

						if (key === 'ballSpeed' || key === 'ballSize' || key === 'playerSpeed' || key === 'playerSize') {
							value = Number(value);
						}
						if (key === 'winScore') {
							value = parseInt(String(value), 10);
						}

						settingsService.updateSetting(key, value as any);
					}
				}
			}
		} catch (e) {
			console.error('Failed to hydrate tournament settings from record', e);
		}

		this.localTournament = state;
		return state;
	}



}


