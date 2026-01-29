import { dbService } from './databaseService.js';
import { Tournament, CreateTournamentRequest, TournamentMatch, ApiResponse } from '../../utils/interfaces.js';
import { config } from '../../gateway/src/config.js';

export class TournamentService {
  async createTournament(creatorId: string, tournamentData: CreateTournamentRequest): Promise<ApiResponse<Tournament>> {
    try {
      const tournament = await dbService.createTournament({
        name: tournamentData.name,
        creatorId,
        maxPlayers: tournamentData.maxPlayers,
        format: tournamentData.format,
        settings: tournamentData.settings
      });

      return {
        success: true,
        data: tournament,
        message: 'Tournament created successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to create tournament',
        timestamp: new Date()
      };
    }
  }

  async joinTournament(playerId: string, tournamentId: string): Promise<ApiResponse<Tournament>> {
    try {
      const tournament = await dbService.getTournamentById(tournamentId);
      if (!tournament) {
        return {
          success: false,
          error: 'Tournament not found',
          timestamp: new Date()
        };
      }

      if (tournament.status !== 'waiting') {
        return {
          success: false,
          error: 'Tournament is not open for registration',
          timestamp: new Date()
        };
      }

      if (tournament.players.includes(playerId)) {
        return {
          success: false,
          error: 'Already registered for this tournament',
          timestamp: new Date()
        };
      }

      if (tournament.players.length >= tournament.maxPlayers) {
        return {
          success: false,
          error: 'Tournament is full',
          timestamp: new Date()
        };
      }

      const updatedTournament = await dbService.updateTournament(tournamentId, {
        players: [...tournament.players, playerId]
      });

      if (!updatedTournament) {
        return {
          success: false,
          error: 'Failed to join tournament',
          timestamp: new Date()
        };
      }

      // If tournament is full, start it
      if (updatedTournament.players.length === updatedTournament.maxPlayers) {
        await this.startTournament(tournamentId);
      }

      return {
        success: true,
        data: updatedTournament,
        message: 'Joined tournament successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to join tournament',
        timestamp: new Date()
      };
    }
  }

  async startTournament(tournamentId: string): Promise<ApiResponse<Tournament>> {
    try {
      const tournament = await dbService.getTournamentById(tournamentId);
      if (!tournament) {
        return {
          success: false,
          error: 'Tournament not found',
          timestamp: new Date()
        };
      }

      if (tournament.status !== 'waiting') {
        return {
          success: false,
          error: 'Tournament cannot be started',
          timestamp: new Date()
        };
      }

      const matches = this.generateMatches(tournament);
      
      const updatedTournament = await dbService.updateTournament(tournamentId, {
        status: 'in-progress',
        startTime: new Date(),
        matches
      });

      if (!updatedTournament) {
        return {
          success: false,
          error: 'Failed to start tournament',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: updatedTournament,
        message: 'Tournament started successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to start tournament',
        timestamp: new Date()
      };
    }
  }

  async updateMatchResult(tournamentId: string, matchId: string, winnerId: string): Promise<ApiResponse<Tournament>> {
    try {
      const tournament = await dbService.getTournamentById(tournamentId);
      if (!tournament) {
        return {
          success: false,
          error: 'Tournament not found',
          timestamp: new Date()
        };
      }

      const matchIndex = tournament.matches.findIndex(m => m.id === matchId);
      if (matchIndex === -1) {
        return {
          success: false,
          error: 'Match not found',
          timestamp: new Date()
        };
      }

      const match = tournament.matches[matchIndex];
      if (match.winnerId) {
        return {
          success: false,
          error: 'Match already completed',
          timestamp: new Date()
        };
      }

      // Update match
      tournament.matches[matchIndex] = {
        ...match,
        winnerId,
        status: 'completed'
      };

      // Check if tournament is complete
      const isComplete = this.checkTournamentComplete(tournament);
      let tournamentWinner: string | undefined;

      if (isComplete) {
        tournamentWinner = this.determineTournamentWinner(tournament);
      }

      const updatedTournament = await dbService.updateTournament(tournamentId, {
        matches: tournament.matches,
        status: isComplete ? 'completed' : 'in-progress',
        endTime: isComplete ? new Date() : undefined,
        winnerId: tournamentWinner
      });

      if (!updatedTournament) {
        return {
          success: false,
          error: 'Failed to update tournament',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: updatedTournament,
        message: isComplete ? 'Tournament completed' : 'Match result updated',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to update match result',
        timestamp: new Date()
      };
    }
  }

  async getTournament(tournamentId: string): Promise<ApiResponse<Tournament>> {
    try {
      const tournament = await dbService.getTournamentById(tournamentId);
      if (!tournament) {
        return {
          success: false,
          error: 'Tournament not found',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: tournament,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get tournament',
        timestamp: new Date()
      };
    }
  }

  async getActiveTournaments(): Promise<ApiResponse<Tournament[]>> {
    try {
      const tournaments = await dbService.getActiveTournaments();
      return {
        success: true,
        data: tournaments,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get active tournaments',
        timestamp: new Date()
      };
    }
  }

  private generateMatches(tournament: Tournament): TournamentMatch[] {
    const matches: TournamentMatch[] = [];
    const players = [...tournament.players];

    if (tournament.format === 'single-elimination') {
      return this.generateSingleEliminationMatches(tournament.id, players);
    } else if (tournament.format === 'double-elimination') {
      return this.generateDoubleEliminationMatches(tournament.id, players);
    } else if (tournament.format === 'round-robin') {
      return this.generateRoundRobinMatches(tournament.id, players);
    }

    return matches;
  }

  private generateSingleEliminationMatches(tournamentId: string, players: string[]): TournamentMatch[] {
    const matches: TournamentMatch[] = [];
    let round = 1;
    let currentPlayers = [...players];

    while (currentPlayers.length > 1) {
      for (let i = 0; i < currentPlayers.length; i += 2) {
        if (i + 1 < currentPlayers.length) {
          matches.push({
            id: `${tournamentId}-r${round}-m${Math.floor(i / 2) + 1}`,
            tournamentId,
            round,
            player1Id: currentPlayers[i],
            player2Id: currentPlayers[i + 1],
            status: 'pending'
          });
        }
      }
      currentPlayers = new Array(Math.ceil(currentPlayers.length / 2)).fill('');
      round++;
    }

    return matches;
  }

  private generateDoubleEliminationMatches(tournamentId: string, players: string[]): TournamentMatch[] {
    // Simplified double elimination - just return single elimination for now
    return this.generateSingleEliminationMatches(tournamentId, players);
  }

  private generateRoundRobinMatches(tournamentId: string, players: string[]): TournamentMatch[] {
    const matches: TournamentMatch[] = [];
    let matchId = 1;

    for (let i = 0; i < players.length; i++) {
      for (let j = i + 1; j < players.length; j++) {
        matches.push({
          id: `${tournamentId}-rr-m${matchId}`,
          tournamentId,
          round: 1,
          player1Id: players[i],
          player2Id: players[j],
          status: 'pending'
        });
        matchId++;
      }
    }

    return matches;
  }

  private checkTournamentComplete(tournament: Tournament): boolean {
    return tournament.matches.every(match => match.status === 'completed');
  }

  private determineTournamentWinner(tournament: Tournament): string | undefined {
    if (tournament.format === 'single-elimination') {
      const finalMatch = tournament.matches
        .filter(m => m.round === Math.max(...tournament.matches.map(match => match.round)))
        .find(m => m.winnerId);
      return finalMatch?.winnerId;
    } else if (tournament.format === 'round-robin') {
      // Count wins for each player
      const winCounts = new Map<string, number>();
      tournament.players.forEach(player => winCounts.set(player, 0));
      
      tournament.matches.forEach(match => {
        if (match.winnerId) {
          winCounts.set(match.winnerId, (winCounts.get(match.winnerId) || 0) + 1);
        }
      });

      // Find player with most wins
      let maxWins = 0;
      let winner: string | undefined;
      winCounts.forEach((wins, playerId) => {
        if (wins > maxWins) {
          maxWins = wins;
          winner = playerId;
        }
      });

      return winner;
    }

    return undefined;
  }
}

export const tournamentService = new TournamentService();