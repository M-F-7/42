import type { GameSettings } from '../types';
import { ApiService } from './ApiService';
import { StorageService } from './StorageService';
import { NotificationService } from './NotificationService';
import { AuthService } from './AuthService';

export class SettingsService {
  private static instance: SettingsService;
  private api: ApiService;
  private storage: StorageService;
  private notification: NotificationService;
  private auth: AuthService;

  private defaultSettings: GameSettings = {
    ballSpeed: 0.3,
    ballSize: 2.0,
    playerSpeed: 1.0,
    playerSize: 30,
    winScore: 7,
    aiDifficulty: 'medium',
  };

  private presets: Record<string, GameSettings> = {
    casual: {
      ballSpeed: 0.3,
      ballSize: 3.0,
      playerSpeed: 0.8,
      playerSize: 40,
      winScore: 5,
      aiDifficulty: 'easy',
    },
    balanced: {
      ballSpeed: 0.3,
      ballSize: 2.0,
      playerSpeed: 1.0,
      playerSize: 30,
      winScore: 7,
      aiDifficulty: 'medium',
    },
    competitive: {
      ballSpeed: 0.6,
      ballSize: 1.5,
      playerSpeed: 1.8,
      playerSize: 20,
      winScore: 11,
      aiDifficulty: 'hard',
    },
    chaos: {
      ballSpeed: 1.0,
      ballSize: 0.5,
      playerSpeed: 2.5,
      playerSize: 15,
      winScore: 15,
      aiDifficulty: 'expert',
    },
  };

  private currentSettings: GameSettings;

  private constructor() {
    this.api = ApiService.getInstance();
    this.storage = StorageService.getInstance();
    this.notification = NotificationService.getInstance();
    this.auth = AuthService.getInstance();
    this.currentSettings = { ...this.defaultSettings };
    //this.loadSettings();
  }

  static getInstance(): SettingsService {
    if (!SettingsService.instance) {
      SettingsService.instance = new SettingsService();
    }
    return SettingsService.instance;
  }

  async loadSettings(): Promise<void> {
    try {
      if (this.auth.isAuthenticated()) {
        const user = this.auth.getCurrentUser();
        if (user) {
          const response = await this.api.get<{ settings: GameSettings }>(
            `/settings/${user.id}`
          );

          if (response.success && response.data?.settings) {
            this.currentSettings = { ...this.defaultSettings, ...response.data.settings };
            return;
          }
        }
      }

      const saved = this.storage.get<GameSettings>('pongGameSettings');
      if (saved) {
        this.currentSettings = { ...this.defaultSettings, ...saved };
      }
    } catch (error) {
      console.warn('Error loading settings:', error);
    }
  }

  async saveSettings(): Promise<void> {
    try {
      this.storage.set('pongGameSettings', this.currentSettings);

      if (this.auth.isAuthenticated()) {
        const user = this.auth.getCurrentUser();
        if (user) {
          await this.api.post(`/settings/${user.id}`, {
            settings: this.currentSettings,
          });
        }
      }

      this.notification.show('Settings saved!', 'success');
    } catch (error) {
      console.error('Error saving settings:', error);
      this.notification.show('Error saving settings', 'error');
    }
  }

  async loadPreset(presetName: string): Promise<void> {
    if (this.presets[presetName]) {
      this.currentSettings = { ...this.presets[presetName] };

      if (this.auth.isAuthenticated()) {
        const user = this.auth.getCurrentUser();
        if (user) {
          try {
            await this.api.post(`/settings/${user.id}/preset/${presetName}`);
          } catch (error) {
            console.error('Error saving preset to backend:', error);
          }
        }
      }

      this.notification.show(`Configuration "${presetName}" loaded!`, 'success');
    }
  }

  async resetToDefault(): Promise<void> {
    this.currentSettings = { ...this.defaultSettings };

    if (this.auth.isAuthenticated()) {
      const user = this.auth.getCurrentUser();
      if (user) {
        try {
          await this.api.post(`/settings/${user.id}/reset`);
        } catch (error) {
          console.error('Error resetting settings in backend:', error);
        }
      }
    }

    this.notification.show('Settings reset to default', 'info');
  }

  getSettings(): GameSettings {
    return { ...this.currentSettings };
  }

  updateSetting<K extends keyof GameSettings>(key: K, value: GameSettings[K]): void {
    this.currentSettings[key] = value;
  }

  getPresets(): Record<string, GameSettings> {
    return { ...this.presets };
  }
}

