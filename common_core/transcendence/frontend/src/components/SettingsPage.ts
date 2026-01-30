import { Component } from '../core/Component';

export class SettingsPage extends Component {
  render(): string {
    return `
      <div class="max-w-7xl mx-auto">
        <h2 class="text-3xl font-bold mb-6" data-i18n-key="settings.title">
          ⚙️ Game Settings
        </h2>

        <div class="grid grid-cols-1 lg:grid-cols-3 gap-6">
          <!-- Settings Panel -->
          <div class="lg:col-span-2 space-y-6">
            <!-- Presets -->
            <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
              <h3 class="text-xl font-bold mb-4" data-i18n-key="settings.presets.title">
                Presets
              </h3>
              <div class="grid grid-cols-2 md:grid-cols-4 gap-3">
                <button
                  data-action="load-preset"
                  data-preset="casual"
                  class="bg-gray-800 hover:bg-gray-700 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="settings.presets.casual"
                >
                  Casual
                </button>
                <button
                  data-action="load-preset"
                  data-preset="balanced"
                  class="bg-gray-800 hover:bg-gray-700 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="settings.presets.balanced"
                >
                  Balanced
                </button>
                <button
                  data-action="load-preset"
                  data-preset="competitive"
                  class="bg-gray-800 hover:bg-gray-700 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="settings.presets.competitive"
                >
                  Competitive
                </button>
                <button
                  data-action="load-preset"
                  data-preset="chaos"
                  class="bg-gray-800 hover:bg-gray-700 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="settings.presets.chaos"
                >
                  Chaos
                </button>
              </div>
            </div>

            <!-- Custom Settings -->
            <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
              <h3 class="text-xl font-bold mb-4" data-i18n-key="settings.custom.title">
                Custom Settings
              </h3>
              <div class="space-y-6">
                <!-- Ball Speed -->
                <div>
                  <div class="flex justify-between mb-2">
                    <label class="text-gray-300" data-i18n-key="settings.ballSpeed.label">
                      Ball Speed
                    </label>
                    <span id="ball-speed-value" class="text-pong-blue font-semibold">0.3</span>
                  </div>
                  <input
                    type="range"
                    id="ball-speed"
                    min="0.3"
                    max="1.0"
                    step="0.1"
                    value="0.3"
                    class="w-full"
                  >
                </div>

                <!-- Player Speed -->
                <div>
                  <div class="flex justify-between mb-2">
                    <label class="text-gray-300" data-i18n-key="settings.playerSpeed.label">
                      Player Speed
                    </label>
                    <span id="player-speed-value" class="text-pong-blue font-semibold">1.0</span>
                  </div>
                  <input
                    type="range"
                    id="player-speed"
                    min="0.5"
                    max="3.0"
                    step="0.1"
                    value="1.0"
                    class="w-full"
                  >
                </div>

                <!-- Player Size -->
                <div>
                  <div class="flex justify-between mb-2">
                    <label class="text-gray-300" data-i18n-key="settings.playerSize.label">
                      Player Size
                    </label>
                    <span id="player-size-value" class="text-pong-blue font-semibold">30</span>
                  </div>
                  <input
                    type="range"
                    id="player-size"
                    min="10"
                    max="50"
                    step="5"
                    value="30"
                    class="w-full"
                  >
                </div>

                <!-- Win Score -->
                <div>
                  <div class="flex justify-between mb-2">
                    <label class="text-gray-300" data-i18n-key="settings.winScore.label">
                      Win Score
                    </label>
                    <span id="win-score-value" class="text-pong-blue font-semibold">7</span>
                  </div>
                  <input
                    type="range"
                    id="win-score"
                    min="3"
                    max="21"
                    step="1"
                    value="7"
                    class="w-full"
                  >
                </div>
              </div>
            </div>

            <!-- Actions -->
            <div class="flex space-x-3">
              <button
                data-action="launch-game"
                class="w-full bg-pong-green hover:bg-green-700 py-3 rounded font-semibold transition-colors text-lg"
                data-i18n-key="settings.play"
              >
                🎮 Play the Game
              </button>
            </div>
          </div>

          <!-- Preview Panel -->
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <h3 class="text-xl font-bold mb-4" data-i18n-key="settings.preview.title">
              Preview
            </h3>
            <div class="aspect-[3/2] bg-black rounded border border-gray-700 relative overflow-hidden">
              <!-- Preview Game Board -->
              <div class="absolute inset-4 flex items-center justify-between">
                <div id="preview-player1" class="bg-pong-blue" style="width: 6px; height: 45px;"></div>
                <div id="preview-ball" class="bg-white rounded-full" style="width: 12px; height: 12px;"></div>
                <div id="preview-player2" class="bg-pong-green" style="width: 6px; height: 45px;"></div>
              </div>
              <div class="absolute inset-x-0 top-1/2 h-px bg-gray-700 opacity-50"></div>
            </div>
            <div class="mt-4 text-sm text-gray-400 space-y-1">
              <p data-i18n-key="settings.preview.tip1">• Adjust settings to see preview changes</p>
              <p data-i18n-key="settings.preview.tip2">• Choose a preset for quick setup</p>
              <p data-i18n-key="settings.preview.tip3">• Settings are saved per user</p>
            </div>
          </div>
        </div>
      </div>
    `;
  }
}
