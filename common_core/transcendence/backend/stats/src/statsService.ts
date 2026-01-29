import { dbService } from './databaseService.js';
import { User, Game, Tournament, UserStats, ApiResponse } from '../../utils/interfaces.js';

export class StatsService {
  async getUserStats(userId: string): Promise<ApiResponse<UserStats>> {
    try {
      const user = await dbService.getUserById(userId);
      if (!user) {
        return {
          success: false,
          error: 'User not found',
          timestamp: new Date()
        };
      }

      const games = await dbService.getUserGames(userId);
      const tournaments = await dbService.getUserTournaments(userId);

      const stats = this.calculateUserStats(userId, games, tournaments);

      return {
        success: true,
        data: stats,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get user stats',
        timestamp: new Date()
      };
    }
  }

  async getGlobalStats(): Promise<ApiResponse<any>> {
    try {
      const allUsers = await dbService.getAllUsers();
      const allGames = await dbService.getAllGames();
      const allTournaments = await dbService.getAllTournaments();

      const globalStats = {
        totalUsers: allUsers.length,
        totalGames: allGames.length,
        totalTournaments: allTournaments.length,
        activeUsers: allUsers.filter(u => u.isOnline).length,
        activeGames: allGames.filter(g => g.status === 'active').length,
        activeTournaments: allTournaments.filter(t => t.status === 'in-progress').length,
        topPlayers: await this.getTopPlayers(5),
        recentGames: allGames
          .filter(g => g.status === 'completed')
          .sort((a, b) => new Date(b.endTime || 0).getTime() - new Date(a.endTime || 0).getTime())
          .slice(0, 10)
      };

      return {
        success: true,
        data: globalStats,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get global stats',
        timestamp: new Date()
      };
    }
  }

  async getLeaderboard(limit: number = 10): Promise<ApiResponse<UserStats[]>> {
    try {
      const topStats = await this.getTopPlayers(limit);
      return {
        success: true,
        data: topStats,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get leaderboard',
        timestamp: new Date()
      };
    }
  }

  async getTournamentStats(tournamentId: string): Promise<ApiResponse<any>> {
    try {
      const tournament = await dbService.getTournamentById(tournamentId);
      if (!tournament) {
        return {
          success: false,
          error: 'Tournament not found',
          timestamp: new Date()
        };
      }

      const playerStats = await Promise.all(
        tournament.players.map(async (playerId) => {
          const playerGames = tournament.matches.filter(
            m => (m.player1Id === playerId || m.player2Id === playerId) && m.status === 'completed'
          );
          const wins = playerGames.filter(m => m.winnerId === playerId).length;
          const losses = playerGames.length - wins;

          const user = await dbService.getUserById(playerId);
          
          return {
            playerId,
            username: user?.username || 'Unknown',
            wins,
            losses,
            winRate: playerGames.length > 0 ? (wins / playerGames.length) * 100 : 0
          };
        })
      );

      const tournamentStats = {
        tournament: {
          id: tournament.id,
          name: tournament.name,
          status: tournament.status,
          totalPlayers: tournament.players.length,
          totalMatches: tournament.matches.length,
          completedMatches: tournament.matches.filter(m => m.status === 'completed').length
        },
        playerStats: playerStats.sort((a, b) => b.winRate - a.winRate),
        winner: tournament.winnerId ? await dbService.getUserById(tournament.winnerId) : null
      };

      return {
        success: true,
        data: tournamentStats,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get tournament stats',
        timestamp: new Date()
      };
    }
  }

  async getGameHistory(userId: string, limit: number = 20): Promise<ApiResponse<Game[]>> {
    try {
      const games = await dbService.getUserGames(userId);
      const recentGames = games
        .filter(g => g.status === 'completed')
        .sort((a, b) => new Date(b.endTime || 0).getTime() - new Date(a.endTime || 0).getTime())
        .slice(0, limit);

      return {
        success: true,
        data: recentGames,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get game history',
        timestamp: new Date()
      };
    }
  }

  private calculateUserStats(userId: string, games: Game[], tournaments: Tournament[]): UserStats {
    const completedGames = games.filter(g => g.status === 'completed');
    const wins = completedGames.filter(g => g.winnerId === userId).length;
    const losses = completedGames.length - wins;
    const winRate = completedGames.length > 0 ? (wins / completedGames.length) * 100 : 0;

    const tournamentWins = tournaments.filter(t => t.winnerId === userId).length;
    const tournamentParticipations = tournaments.length;

    // Calculate average game duration
    const gameDurations = completedGames
      .filter(g => g.startTime && g.endTime)
      .map(g => new Date(g.endTime!).getTime() - new Date(g.startTime!).getTime());
    
    const averageGameDuration = gameDurations.length > 0 
      ? Math.round(gameDurations.reduce((a, b) => a + b, 0) / gameDurations.length / 1000) // in seconds
      : 0;

    // Get streaks
    const { currentStreak, longestWinStreak } = this.calculateStreaks(completedGames, userId);

    return {
      userId,
      gamesPlayed: completedGames.length,
      gamesWon: wins,
      gamesLost: losses,
      winRate,
      tournamentsPlayed: tournamentParticipations,
      tournamentsWon: tournamentWins,
      currentStreak,
      longestWinStreak,
      averageGameDuration,
      lastActivity: games.length > 0 
        ? new Date(Math.max(...games.map(g => new Date(g.createdAt).getTime())))
        : new Date(),
      rank: this.calculateRank(winRate, wins, tournamentWins)
    };
  }

  private calculateStreaks(games: Game[], userId: string): { currentStreak: number; longestWinStreak: number } {
    if (games.length === 0) {
      return { currentStreak: 0, longestWinStreak: 0 };
    }

    // Sort games by end time (most recent first)
    const sortedGames = games
      .filter(g => g.endTime)
      .sort((a, b) => new Date(b.endTime!).getTime() - new Date(a.endTime!).getTime());

    let currentStreak = 0;
    let longestWinStreak = 0;
    let tempWinStreak = 0;

    // Calculate current streak
    for (const game of sortedGames) {
      if (game.winnerId === userId) {
        currentStreak++;
      } else {
        break;
      }
    }

    // Calculate longest win streak
    for (const game of sortedGames.reverse()) {
      if (game.winnerId === userId) {
        tempWinStreak++;
        longestWinStreak = Math.max(longestWinStreak, tempWinStreak);
      } else {
        tempWinStreak = 0;
      }
    }

    return { currentStreak, longestWinStreak };
  }

  private calculateRank(winRate: number, wins: number, tournamentWins: number): string {
    const score = winRate + (wins * 0.1) + (tournamentWins * 5);

    if (score >= 80) return 'Master';
    if (score >= 60) return 'Expert';
    if (score >= 40) return 'Advanced';
    if (score >= 20) return 'Intermediate';
    return 'Beginner';
  }

  private async getTopPlayers(limit: number): Promise<UserStats[]> {
    try {
      const allUsers = await dbService.getAllUsers();
      const userStats = await Promise.all(
        allUsers.map(async (user) => {
          const games = await dbService.getUserGames(user.id);
          const tournaments = await dbService.getUserTournaments(user.id);
          return this.calculateUserStats(user.id, games, tournaments);
        })
      );

      return userStats
        .filter(stats => stats.gamesPlayed > 0)
        .sort((a, b) => {
          // Sort by win rate, then by games won, then by tournament wins
          if (b.winRate !== a.winRate) return b.winRate - a.winRate;
          if (b.gamesWon !== a.gamesWon) return b.gamesWon - a.gamesWon;
          return b.tournamentsWon - a.tournamentsWon;
        })
        .slice(0, limit);
    } catch (error) {
      return [];
    }
  }
}

export const statsService = new StatsService();