import { Component } from '../core/Component';

export class HomePage extends Component {
  render(): string {
    return `
      <div class="max-w-7xl mx-auto space-y-8">
        <!-- Welcome message -->
        <div class="text-center">
          <h2
            class="text-4xl font-bold mb-4 bg-gradient-to-r from-pong-blue to-pong-green bg-clip-text text-transparent"
            data-i18n-key="home.title"
          >
            Welcome to Pong Arena!
          </h2>
          <p
            class="text-xl text-gray-400 mb-8"
            data-i18n-key="home.subtitle"
          >
            Challenge your friends, participate in tournaments, and Grind!
          </p>
        </div>

        <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          <!-- Player vs Player -->
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6 hover:border-pong-blue transition-colors group">
            <div class="text-center">
              <div class="text-4xl mb-4 group-hover:scale-110 transition-transform">⚔️</div>
              <h3
                class="text-xl font-bold mb-2"
                data-i18n-key="home.pvp.title"
              >
                Player vs Player
              </h3>
              <p
                class="text-gray-400 mb-4"
                data-i18n-key="home.pvp.description"
              >
                Challenge a friend in real-time
              </p>
              <button
                data-action="start-pvp"
                class="w-full bg-pong-blue hover:bg-blue-700 py-2 rounded font-semibold transition-colors"
                data-i18n-key="home.pvp.button"
              >
                Play Now
              </button>
            </div>
          </div>

          <!-- Player vs AI -->
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6 hover:border-pong-green transition-colors group">
            <div class="text-center">
              <div class="text-4xl mb-4 group-hover:scale-110 transition-transform">🤖</div>
              <h3
                class="text-xl font-bold mb-2"
                data-i18n-key="home.ai.title"
              >
                Player vs AI
              </h3>
              <p
                class="text-gray-400 mb-4"
                data-i18n-key="home.ai.description"
              >
                Challenge the artificial intelligence
              </p>
              <button
                data-action="start-ai"
                class="w-full bg-pong-green hover:bg-green-700 py-2 rounded font-semibold transition-colors"
                data-i18n-key="home.ai.button"
              >
                Play Against AI
              </button>
            </div>
          </div>

          <!-- Tournament -->
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6 hover:border-yellow-500 transition-colors group">
            <div class="text-center">
              <div class="text-4xl mb-4 group-hover:scale-110 transition-transform">🏆</div>
              <h3
                class="text-xl font-bold mb-2"
                data-i18n-key="home.tournament.title"
              >
                Tournament
              </h3>
              <p
                class="text-gray-400 mb-4"
                data-i18n-key="home.tournament.description"
              >
                Participate in competitions
              </p>
              <button
                data-action="navigate-tournament"
                class="w-full bg-yellow-600 hover:bg-yellow-700 py-2 rounded font-semibold transition-colors"
                data-i18n-key="home.tournament.button"
              >
                View Tournaments
              </button>
            </div>
          </div>

          <!-- Stats -->
          <div
            id="home-stats-box"
            class="bg-gray-900/50 border border-gray-800 rounded-lg p-6 transition-colors group opacity-30 pointer-events-none"
          >
            <div class="text-center">
              <div class="text-4xl mb-4">📊</div>
              <h3
                class="text-xl font-bold mb-2"
                data-i18n-key="home.stats.title"
              >
                Stats
              </h3>
              <p
                class="text-gray-400 mb-4"
                data-i18n-key="home.stats.description"
              >
                Check your performance
              </p>
              <button
                id="home-stats-button"
                data-action="navigate-stats"
                class="w-full bg-orange-400 py-2 rounded font-semibold transition-colors"
                data-i18n-key="home.stats.button"
              >
                View My Stats
              </button>
            </div>
          </div>
        </div>
      </div>
    `;
  }
}
