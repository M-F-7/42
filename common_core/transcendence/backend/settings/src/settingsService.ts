import { dbService } from './databaseService.js';
import { GameSettings, ApiResponse, UserGameSettings, GamePreset, SaveSettingsRequest } from '../../utils/interfaces.js';

export class SettingsService {
  private readonly defaultSettings: GameSettings = {
    ballSpeed: 0.3,
    ballSize: 2.0,
    playerSpeed: 1.0,
    playerSize: 30,
    winScore: 7,
    aiDifficulty: 'medium'
  };

  private readonly presets: GamePreset[] = [
    {
      name: 'casual',
      displayName: 'Casual',
      description: 'Relaxed gameplay with slower pace and easier controls',
      settings: {
        ballSpeed: 0.2,
        ballSize: 3.0,
        playerSpeed: 0.8,
        playerSize: 40,
        winScore: 5,
        aiDifficulty: 'easy'
      }
    },
    {
      name: 'balanced',
      displayName: 'Balanced',
      description: 'Standard game settings for most players',
      settings: {
        ballSpeed: 0.3,
        ballSize: 2.0,
        playerSpeed: 1.0,
        playerSize: 30,
        winScore: 7,
        aiDifficulty: 'medium'
      }
    },
    {
      name: 'competitive',
      displayName: 'Competitive',
      description: 'Fast-paced gameplay for experienced players',
      settings: {
        ballSpeed: 0.6,
        ballSize: 1.5,
        playerSpeed: 1.8,
        playerSize: 20,
        winScore: 11,
        aiDifficulty: 'hard'
      }
    },
    {
      name: 'chaos',
      displayName: 'Chaos',
      description: 'Extreme settings for ultimate challenge',
      settings: {
        ballSpeed: 1.2,
        ballSize: 0.5,
        playerSpeed: 2.5,
        playerSize: 15,
        winScore: 15,
        aiDifficulty: 'expert'
      }
    }
  ];

  async getUserSettings(userId: string): Promise<ApiResponse<UserGameSettings>> {
    try {
      const user = await dbService.getUserById(userId);
      if (!user) {
        return {
          success: false,
          error: 'User not found',
          timestamp: new Date()
        };
      }

      // Try to get user settings from database
      const userSettings = await dbService.getUserSettings(userId);
      
      if (userSettings) {
        return {
          success: true,
          data: userSettings,
          timestamp: new Date()
        };
      }

      // Return default settings if no user settings found
      const defaultUserSettings: UserGameSettings = {
        id: `settings_${userId}`,
        userId,
        settings: this.defaultSettings,
        createdAt: new Date(),
        updatedAt: new Date()
      };

      return {
        success: true,
        data: defaultUserSettings,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get user settings',
        timestamp: new Date()
      };
    }
  }

  async saveUserSettings(userId: string, settingsRequest: SaveSettingsRequest): Promise<ApiResponse<UserGameSettings>> {
    try {
      const user = await dbService.getUserById(userId);
      if (!user) {
        return {
          success: false,
          error: 'User not found',
          timestamp: new Date()
        };
      }

      // Validate settings
      const validationResult = this.validateSettings(settingsRequest.settings);
      if (!validationResult.valid) {
        return {
          success: false,
          error: validationResult.error,
          timestamp: new Date()
        };
      }

      const existingSettings = await dbService.getUserSettings(userId);
      
      if (existingSettings) {
        // Update existing settings
        const updatedSettings = await dbService.updateUserSettings(userId, {
          settings: settingsRequest.settings,
          presetName: settingsRequest.presetName,
          updatedAt: new Date()
        });

        if (!updatedSettings) {
          return {
            success: false,
            error: 'Failed to update settings',
            timestamp: new Date()
          };
        }

        return {
          success: true,
          data: updatedSettings,
          message: 'Settings updated successfully',
          timestamp: new Date()
        };
      } else {
        // Create new settings
        const newSettings = await dbService.createUserSettings({
          userId,
          settings: settingsRequest.settings,
          presetName: settingsRequest.presetName
        });

        return {
          success: true,
          data: newSettings,
          message: 'Settings saved successfully',
          timestamp: new Date()
        };
      }
    } catch (error) {
      return {
        success: false,
        error: 'Failed to save settings',
        timestamp: new Date()
      };
    }
  }

  async loadPreset(userId: string, presetName: string): Promise<ApiResponse<UserGameSettings>> {
    try {
      const preset = this.presets.find(p => p.name === presetName);
      if (!preset) {
        return {
          success: false,
          error: 'Preset not found',
          timestamp: new Date()
        };
      }

      const settingsRequest: SaveSettingsRequest = {
        settings: preset.settings,
        presetName: preset.name
      };

      return await this.saveUserSettings(userId, settingsRequest);
    } catch (error) {
      return {
        success: false,
        error: 'Failed to load preset',
        timestamp: new Date()
      };
    }
  }

  async resetToDefault(userId: string): Promise<ApiResponse<UserGameSettings>> {
    try {
      const settingsRequest: SaveSettingsRequest = {
        settings: this.defaultSettings,
        presetName: 'balanced'
      };

      return await this.saveUserSettings(userId, settingsRequest);
    } catch (error) {
      return {
        success: false,
        error: 'Failed to reset settings',
        timestamp: new Date()
      };
    }
  }

  async getAvailablePresets(): Promise<ApiResponse<GamePreset[]>> {
    try {
      return {
        success: true,
        data: this.presets,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get presets',
        timestamp: new Date()
      };
    }
  }

  async getPresetByName(presetName: string): Promise<ApiResponse<GamePreset>> {
    try {
      const preset = this.presets.find(p => p.name === presetName);
      
      if (!preset) {
        return {
          success: false,
          error: 'Preset not found',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: preset,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get preset',
        timestamp: new Date()
      };
    }
  }

  private validateSettings(settings: GameSettings): { valid: boolean; error?: string } {
    // Validate ball speed (0.1 - 2.0)
    if (settings.ballSpeed < 0.1 || settings.ballSpeed > 2.0) {
      return { valid: false, error: 'Ball speed must be between 0.1 and 2.0' };
    }

    // Validate ball size (0.5 - 5.0)
    if (settings.ballSize < 0.5 || settings.ballSize > 5.0) {
      return { valid: false, error: 'Ball size must be between 0.5 and 5.0' };
    }

    // Validate player speed (0.5 - 3.0)
    if (settings.playerSpeed < 0.5 || settings.playerSpeed > 3.0) {
      return { valid: false, error: 'Player speed must be between 0.5 and 3.0' };
    }

    // Validate player size (10 - 60)
    if (settings.playerSize < 10 || settings.playerSize > 60) {
      return { valid: false, error: 'Player size must be between 10 and 60' };
    }

    // Validate win score (1 - 21)
    if (settings.winScore < 1 || settings.winScore > 21) {
      return { valid: false, error: 'Win score must be between 1 and 21' };
    }

    // Validate AI difficulty
    const validDifficulties = ['easy', 'medium', 'hard', 'expert'];
    if (!validDifficulties.includes(settings.aiDifficulty)) {
      return { valid: false, error: 'Invalid AI difficulty' };
    }

    return { valid: true };
  }

  async exportUserSettings(userId: string): Promise<ApiResponse<any>> {
    try {
      const settingsResult = await this.getUserSettings(userId);
      if (!settingsResult.success || !settingsResult.data) {
        return settingsResult;
      }

      const exportData = {
        settings: settingsResult.data.settings,
        presetName: settingsResult.data.presetName,
        exportDate: new Date(),
        version: '1.0'
      };

      return {
        success: true,
        data: exportData,
        message: 'Settings exported successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to export settings',
        timestamp: new Date()
      };
    }
  }

  async importUserSettings(userId: string, importData: any): Promise<ApiResponse<UserGameSettings>> {
    try {
      // Validate import data structure
      if (!importData.settings) {
        return {
          success: false,
          error: 'Invalid import data: missing settings',
          timestamp: new Date()
        };
      }

      // Validate settings
      const validationResult = this.validateSettings(importData.settings);
      if (!validationResult.valid) {
        return {
          success: false,
          error: `Invalid settings in import: ${validationResult.error}`,
          timestamp: new Date()
        };
      }

      const settingsRequest: SaveSettingsRequest = {
        settings: importData.settings,
        presetName: importData.presetName
      };

      const result = await this.saveUserSettings(userId, settingsRequest);
      if (result.success) {
        result.message = 'Settings imported successfully';
      }

      return result;
    } catch (error) {
      return {
        success: false,
        error: 'Failed to import settings',
        timestamp: new Date()
      };
    }
  }
}

export const settingsService = new SettingsService();