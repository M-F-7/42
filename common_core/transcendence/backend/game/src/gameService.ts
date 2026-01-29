import { dbService } from '../../src/services/databaseService.js';
import { Game, CreateGameRequest, GameSettings, ApiResponse } from '../../utils/interfaces.js';
import { config } from '../../gateway/src/config.js';

export class GameService {
  private activeGames: Map<string, any> = new Map();

  async createGame(playerId: string, gameData: CreateGameRequest): Promise<ApiResponse<Game>> {
    try {
      // Check if user already has too many active games
      const userGames = await dbService.getGamesByPlayerId(playerId);
      const activeUserGames = userGames.filter(game => 
        game.status === 'waiting' || game.status === 'in-progress'
      );

      if (activeUserGames.length >= config.game.maxGamesPerUser) {
        return {
          success: false,
          error: 'Too many active games',
          timestamp: new Date()
        };
      }

      // Create the game
      const game = await dbService.createGame({
        player1Id: playerId,
        player2Id: gameData.mode === 'pvia' ? 'AI' : gameData.opponentId,
        mode: gameData.mode,
        settings: gameData.settings,
        score: { player1: 0, player2: 0 }
      });

      // Set timeout for game
      this.setGameTimeout(game.id);

      return {
        success: true,
        data: game,
        message: 'Game created successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to create game',
        timestamp: new Date()
      };
    }
  }

  async joinGame(playerId: string, gameId: string): Promise<ApiResponse<Game>> {
    try {
      const game = await dbService.getGameById(gameId);
      if (!game) {
        return {
          success: false,
          error: 'Game not found',
          timestamp: new Date()
        };
      }

      if (game.status !== 'waiting') {
        return {
          success: false,
          error: 'Game is not available to join',
          timestamp: new Date()
        };
      }

      if (game.player2Id && game.player2Id !== 'AI') {
        return {
          success: false,
          error: 'Game is already full',
          timestamp: new Date()
        };
      }

      if (game.player1Id === playerId) {
        return {
          success: false,
          error: 'Cannot join your own game',
          timestamp: new Date()
        };
      }

      // Join the game
      const updatedGame = await dbService.updateGame(gameId, {
        player2Id: playerId,
        status: 'in-progress'
      });

      if (!updatedGame) {
        return {
          success: false,
          error: 'Failed to join game',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: updatedGame,
        message: 'Joined game successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to join game',
        timestamp: new Date()
      };
    }
  }

  async updateGameScore(gameId: string, playerId: string, newScore: { player1: number; player2: number }): Promise<ApiResponse<Game>> {
    try {
      const game = await dbService.getGameById(gameId);
      if (!game) {
        return {
          success: false,
          error: 'Game not found',
          timestamp: new Date()
        };
      }

      if (game.status !== 'in-progress') {
        return {
          success: false,
          error: 'Game is not in progress',
          timestamp: new Date()
        };
      }

      if (game.player1Id !== playerId && game.player2Id !== playerId) {
        return {
          success: false,
          error: 'Not authorized to update this game',
          timestamp: new Date()
        };
      }

      // Update score
      const updatedGame = await dbService.updateGame(gameId, {
        score: newScore
      });

      if (!updatedGame) {
        return {
          success: false,
          error: 'Failed to update game',
          timestamp: new Date()
        };
      }

      // Check if game is won
      if (newScore.player1 >= game.settings.winScore || newScore.player2 >= game.settings.winScore) {
        await this.endGame(gameId);
      }

      return {
        success: true,
        data: updatedGame,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to update game score',
        timestamp: new Date()
      };
    }
  }

  async endGame(gameId: string): Promise<ApiResponse<Game>> {
    try {
      const game = await dbService.getGameById(gameId);
      if (!game) {
        return {
          success: false,
          error: 'Game not found',
          timestamp: new Date()
        };
      }

      const endTime = new Date();
      const duration = endTime.getTime() - game.startTime.getTime();
      
      // Determine winner
      let winner: string | undefined;
      if (game.score.player1 > game.score.player2) {
        winner = game.player1Id;
      } else if (game.score.player2 > game.score.player1) {
        winner = game.player2Id;
      }

      // Update game
      const updatedGame = await dbService.updateGame(gameId, {
        status: 'completed',
        endTime,
        duration,
        winner
      });

      if (!updatedGame) {
        return {
          success: false,
          error: 'Failed to end game',
          timestamp: new Date()
        };
      }

      // Update player stats
      if (winner && game.player2Id !== 'AI') {
        const loser = winner === game.player1Id ? game.player2Id : game.player1Id;
        if (loser) {
          await dbService.updateUserStats(winner, 'win', duration);
          await dbService.updateUserStats(loser, 'loss', duration);
        }
      } else if (winner && game.player2Id === 'AI') {
        await dbService.updateUserStats(game.player1Id, winner === game.player1Id ? 'win' : 'loss', duration);
      }

      // Clear timeout
      this.clearGameTimeout(gameId);

      return {
        success: true,
        data: updatedGame,
        message: 'Game ended successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to end game',
        timestamp: new Date()
      };
    }
  }

  async getGame(gameId: string): Promise<ApiResponse<Game>> {
    try {
      const game = await dbService.getGameById(gameId);
      if (!game) {
        return {
          success: false,
          error: 'Game not found',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: game,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get game',
        timestamp: new Date()
      };
    }
  }

  async getActiveGames(): Promise<ApiResponse<Game[]>> {
    try {
      const games = await dbService.getActiveGames();
      return {
        success: true,
        data: games,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get active games',
        timestamp: new Date()
      };
    }
  }

  private setGameTimeout(gameId: string): void {
    const timeout = setTimeout(async () => {
      await dbService.updateGame(gameId, {
        status: 'abandoned'
      });
      this.activeGames.delete(gameId);
    }, config.game.gameTimeout);

    this.activeGames.set(gameId, timeout);
  }

  private clearGameTimeout(gameId: string): void {
    const timeout = this.activeGames.get(gameId);
    if (timeout) {
      clearTimeout(timeout);
      this.activeGames.delete(gameId);
    }
  }
}

export const gameService = new GameService();