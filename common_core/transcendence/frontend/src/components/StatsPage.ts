
import { Component } from '../core/Component';

export class StatsPage extends Component {
	render(): string {
		return `
      <div class="max-w-7xl mx-auto">
        <h2 class="text-3xl font-bold mb-6" data-i18n-key="stats.title">
          📊 Your Statistics
        </h2>

        <!-- Overview Cards -->
        <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-6 mb-8">
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <div class="text-gray-400 text-sm mb-1" data-i18n-key="stats.overview.gamesPlayed">
              Games Played
            </div>
            <div class="text-3xl font-bold text-pong-blue" id="stat-games-played">0</div>
          </div>

          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <div class="text-gray-400 text-sm mb-1" data-i18n-key="stats.overview.gamesWon">
              Games Won
            </div>
            <div class="text-3xl font-bold text-pong-green" id="stat-games-won">0</div>
          </div>

          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <div class="text-gray-400 text-sm mb-1" data-i18n-key="stats.overview.winRate">
              Win Rate
            </div>
            <div class="text-3xl font-bold text-yellow-500" id="stat-win-rate">0%</div>
          </div>

          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <div class="text-gray-400 text-sm mb-1" data-i18n-key="stats.overview.gamesLost">
              Games Lost
            </div>
            <div class="text-3xl font-bold text-red-500" id="stat-games-lost">0</div>
          </div>
        </div>

        <!-- Detailed Stats -->
        <div class="grid grid-cols-1 lg:grid-cols-2 gap-6">
          <!-- Recent Matches -->
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <h3 class="text-xl font-bold mb-4" data-i18n-key="stats.recent.title">
              Recent Matches
            </h3>
            <div id="recent-matches" class="space-y-3">
              <div class="text-center py-8 text-gray-400">
                <p data-i18n-key="stats.recent.empty.title">
                  No match history yet
                </p>
                <p class="text-sm" data-i18n-key="stats.recent.empty.subtitle">
                  Play some games to see your stats!
                </p>
              </div>
            </div>
          </div>

          <!-- Performance Overview (graph) -->
          <div class="bg-gray-900/50 border border-gray-800 rounded-lg p-6">
            <h3 class="text-xl font-bold mb-4">
              Performance Overview
            </h3>

            <!-- Graphe Win / Loss -->
            <div class="mb-4">
              <div class="text-gray-400 text-sm mb-2">
                Win / Loss ratio
              </div>
              <div id="stat-winloss-chart">
                <div class="text-sm text-gray-500">No data yet</div>
              </div>
            </div>

            <!-- Petit récap -->
            <div class="grid grid-cols-2 gap-3 text-sm">
              <div class="bg-gray-800/70 rounded p-3">
                <div class="text-gray-400 text-xs">Total games</div>
                <div class="text-lg font-semibold" id="perf-total-games">0</div>
              </div>
              <div class="bg-gray-800/70 rounded p-3">
                <div class="text-gray-400 text-xs">Current win rate</div>
                <div class="text-lg font-semibold text-yellow-400" id="perf-win-rate">0%</div>
              </div>
            </div>
          </div>
        </div>
      </div>
    `;
	}
}
