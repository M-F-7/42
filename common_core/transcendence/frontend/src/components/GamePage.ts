import { Component } from '../core/Component';

export class GamePage extends Component {
  render(): string {
    return `
      <div class="flex flex-col items-center justify-center min-h-[80vh] px-4">
        <!-- Score Display Above Game -->
        <div class="flex justify-center items-center w-full max-w-[1200px] mb-6 gap-16">
          <div id="game-player1-label" class="text-pong-blue text-2xl font-bold" data-i18n-key="game.player1">
            User
          </div>
          <div class="flex items-center space-x-6">
            <span id="game-score-player1" class="text-6xl font-bold text-pong-blue">0</span>
            <span class="text-gray-400 text-5xl font-bold">-</span>
            <span id="game-score-player2" class="text-6xl font-bold text-pong-green">0</span>
          </div>
          <div id="game-player2-label" class="text-pong-green text-2xl font-bold" data-i18n-key="game.player2">
            Guest
          </div>
        </div>

        <!-- Game Board -->
        <div class="relative bg-black border-2 border-pong-blue rounded-lg w-full max-w-[1200px] aspect-[3/2] overflow-hidden" id="game-board">

          <!-- Player 1 -->
          <div id="game-player1" class="absolute bg-pong-blue rounded-lg"
            style="left: 0; top: 50%; width: 12px; height: 100px; transform: translateY(-50%);"></div>
          
          <!-- Player 2 -->
          <div id="game-player2" class="absolute bg-pong-green rounded-lg"
            style="right: 0; top: 50%; width: 12px; height: 100px; transform: translateY(-50%);"></div>

          <!-- Ball -->
          <div id="game-ball" class="absolute bg-white rounded-full"
            style="left: 50%; top: 50%; width: 24px; height: 24px; transform: translate(-50%, -50%);"></div>

          <!-- Center Line -->
          <div class="absolute left-1/2 top-0 bottom-0 w-px bg-gray-700 opacity-50"></div>

          <!-- Pause Overlay -->
          <div id="game-pause-overlay"
            class="hidden absolute inset-0 bg-black/80 flex items-center justify-center">
            <div class="text-center">
              <h2 class="text-4xl font-bold mb-6" data-i18n-key="game.paused">Game Paused</h2>
              <div class="space-y-3">
                <button data-action="resume-game"
                  class="block w-full bg-pong-blue hover:bg-blue-700 px-6 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="game.resume">
                  Resume (ESC)
                </button>
                <button data-action="restart-game"
                  class="block w-full bg-yellow-600 hover:bg-yellow-700 px-6 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="game.restart">
                  Restart
                </button>
                <button data-action="navigate-home"
                  class="block w-full bg-gray-700 hover:bg-gray-600 px-6 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="game.exit">
                  Exit to Menu
                </button>
              </div>
            </div>
          </div>

          <!-- Game End Overlay -->
          <div id="game-end-overlay"
            class="hidden absolute inset-0 bg-black/80 flex items-center justify-center">
            <div class="text-center">
              <h2 id="game-winner-text"
                class="text-4xl font-bold mb-4 text-pong-green"
                data-i18n-key="game.winnerText">
                Player 1 Wins!
              </h2>
              <p id="game-final-score"
                class="text-xl text-gray-400 mb-6"
                data-i18n-key="game.finalScore">
                Final Score: 7 - 5
              </p>
              <div class="space-y-3">
                <button data-action="restart-game"
                  class="block w-full bg-pong-green hover:bg-green-700 px-6 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="game.playAgain">
                  Play Again
                </button>
                <button data-action="navigate-home"
                  class="block w-full bg-gray-700 hover:bg-gray-600 px-6 py-3 rounded font-semibold transition-colors"
                  data-i18n-key="game.backToMenu">
                  Back to Menu
                </button>
              </div>
            </div>
          </div>
        </div>

        <!-- Controls Info -->
        <div class="mt-6 text-center text-gray-400 max-w-2xl">
          <p class="mb-2 text-sm md:text-base" data-i18n-key="game.controls">
            <span class="text-pong-blue font-semibold">Player 1:</span> W / S keys
            <span class="mx-2 md:mx-4">|</span>
            <span class="text-pong-green font-semibold">Player 2:</span> Arrow Up / Down keys
          </p>
          <p class="text-xs md:text-sm" data-i18n-key="game.pauseHint">
            Press <span class="font-semibold">ESC</span> to pause
          </p>
        </div>
      </div>
    `;
  }
}
