import type { GameSettings, GameMode, Player, Ball, GameResult } from '../types';
import { GameService } from "../services/GameService"

export class PongGame {
  private settings: GameSettings;
  private mode: GameMode;
  private isRunning: boolean = false;
  private isPaused: boolean = false;
  private animationId: number | null = null;
  private gameService: GameService;

  private onEndCallback?: (result: { score1: number; score2: number }) => void;
  private playerLabels?: { left: string; right: string };
  userId: string;

  private boardEl: HTMLElement | null;
  private player1El: HTMLElement | null;
  private player2El: HTMLElement | null;
  private ballEl: HTMLElement | null;
  private score1El: HTMLElement | null;
  private score2El: HTMLElement | null;

  private player1: Player;
  private player2: Player;
  private ball: Ball;

  private keys: Record<string, boolean> = {};

  private aiDirection: -1 | 0 | 1 = 0;
  private lastAiUpdate: number = 0;

  constructor(settings: GameSettings, mode: GameMode, options?: {
    onEnd?: (result: { score1: number; score2: number }) => void;
    playerLabels?: { left: string; right: string };
  }) {
    this.settings = settings;
    this.mode = mode;
    this.onEndCallback = options?.onEnd;
    this.playerLabels = options?.playerLabels;

    this.boardEl = document.getElementById('game-board');
    this.player1El = document.getElementById('game-player1');
    this.player2El = document.getElementById('game-player2');
    this.ballEl = document.getElementById('game-ball');
    this.score1El = document.getElementById('game-score-player1');
    this.score2El = document.getElementById('game-score-player2');

    this.applyPlayerLabels();

    this.player1 = this.createPlayer(0, 50);
    this.player2 = this.createPlayer(100, 50);
    this.ball = this.createBall();

    this.gameService = GameService.getInstance();
    this.initializeGame();
    this.setupEventListeners();
    this.start();
  }

  private applyPlayerLabels(): void {
    if (!this.playerLabels) return;

    const leftLabelEl = document.getElementById('game-player1-label');
    const rightLabelEl = document.getElementById('game-player2-label');

    if (leftLabelEl) leftLabelEl.textContent = this.playerLabels.left;
    if (rightLabelEl) rightLabelEl.textContent = this.playerLabels.right;
  }

  private createPlayer(x: number, y: number): Player {
    return {
      x,
      y,
      width: 5,
      height: this.settings.playerSize,
      speed: this.settings.playerSpeed,
      score: 0,
    };
  }

  private createBall(): Ball {
    return {
      x: 50,
      y: 50,
      radius: this.settings.ballSize,
      speed: this.settings.ballSpeed,
      dx: Math.random() > 0.5 ? 1 : -1,
      dy: (Math.random() - 0.5) * 0.5,
    };
  }

  private initializeGame(): void {
    this.setupBoard();
    this.updateDisplay();
  }

  private setupBoard(): void {
    if (!this.boardEl) return;
    this.updateBallSize();
    this.updatePlayerSizes();
  }

  private setupEventListeners(): void {
    const keyDownHandler = (e: KeyboardEvent) => {
      const key = e.key.toLowerCase();

      if ((this.mode === 'ai' || this.mode === 'training') && (key === '8' || key === '2')) {
        return;
      }

      this.keys[key] = true;

      if (e.key === 'Escape') {
        this.togglePause();
      }
    };

    const keyUpHandler = (e: KeyboardEvent) => {
      const key = e.key.toLowerCase();

      if ((this.mode === 'ai' || this.mode === 'training') && (key === '8' || key === '2')) {
        return;
      }

      this.keys[key] = false;
    };

    const resizeHandler = () => {
      this.setupBoard();
    };

    document.addEventListener('keydown', keyDownHandler);
    document.addEventListener('keyup', keyUpHandler);
    window.addEventListener('resize', resizeHandler);

    (this as any)._keyDownHandler = keyDownHandler;
    (this as any)._keyUpHandler = keyUpHandler;
    (this as any)._resizeHandler = resizeHandler;
  }

  private removeEventListeners(): void {
    if ((this as any)._keyDownHandler) {
      document.removeEventListener('keydown', (this as any)._keyDownHandler);
    }
    if ((this as any)._keyUpHandler) {
      document.removeEventListener('keyup', (this as any)._keyUpHandler);
    }
    if ((this as any)._resizeHandler) {
      window.removeEventListener('resize', (this as any)._resizeHandler);
    }
  }

  start(): void {
    this.isRunning = true;
    this.isPaused = false;
    this.lastAiUpdate = performance.now();
    this.gameLoop();
  }

  pause(): void {
    this.isPaused = true;
    const overlay = document.getElementById('game-pause-overlay');
    if (overlay) overlay.classList.remove('hidden');
  }

  resume(): void {
    this.isPaused = false;
    const overlay = document.getElementById('game-pause-overlay');
    if (overlay) overlay.classList.add('hidden');
    this.gameLoop();
  }

  togglePause(): void {
    if (this.isPaused) {
      this.resume();
    } else {
      this.pause();
    }
  }

  restart(settings: GameSettings, mode: GameMode): void {
    this.settings = settings;
    this.mode = mode;
    this.isPaused = false;

    const pauseOverlay = document.getElementById('game-pause-overlay');
    const endOverlay = document.getElementById('game-end-overlay');
    if (pauseOverlay) pauseOverlay.classList.add('hidden');
    if (endOverlay) endOverlay.classList.add('hidden');

    this.player1 = this.createPlayer(0, 50);
    this.player2 = this.createPlayer(100, 50);
    this.ball = this.createBall();

    this.initializeGame();
    this.start();
  }

  private gameLoop(): void {
    if (!this.isRunning || this.isPaused) return;

    this.handleInput();
    this.updatePhysics();
    this.updateDisplay();
    this.checkGameEnd();

    this.animationId = requestAnimationFrame(() => this.gameLoop());
  }

  private handleInput(): void {
    if (this.keys['w']) {
      this.player1.y = Math.max(
        this.player1.height / 2,
        this.player1.y - this.player1.speed
      );
    }
    if (this.keys['s']) {
      this.player1.y = Math.min(
        100 - this.player1.height / 2,
        this.player1.y + this.player1.speed
      );
    }

    if (this.mode === 'ai' || this.mode === 'training') {
      this.updateAI();
    }

    if (this.keys['8']) {
      this.player2.y = Math.max(
        this.player2.height / 2,
        this.player2.y - this.player2.speed
      );
    }
    if (this.keys['2']) {
      this.player2.y = Math.min(
        100 - this.player2.height / 2,
        this.player2.y + this.player2.speed
      );
    }
  }

  private updateAI(): void {
    const now = performance.now();

    if (now - this.lastAiUpdate >= 1000) {
      this.lastAiUpdate = now;
      this.recomputeAiDecision();
    }

    if (this.aiDirection < 0) {
      this.keys['8'] = true;
      this.keys['2'] = false;
    } else if (this.aiDirection > 0) {
      this.keys['8'] = false;
      this.keys['2'] = true;
    } else {
      this.keys['8'] = false;
      this.keys['2'] = false;
    }
  }

  private recomputeAiDecision(): void {
    const difficulty = this.getDifficultyFactor();
    const predictedY = this.predictBallYAtPlayer2();
    const playerY = this.player2.y;

    let targetY = predictedY;
    targetY += (Math.random() - 0.5) * (1 - difficulty) * 20;

    if (targetY < playerY - 1) {
      this.aiDirection = -1;
    } else if (targetY > playerY + 1) {
      this.aiDirection = 1;
    } else {
      this.aiDirection = 0;
    }
  }

  private predictBallYAtPlayer2(): number {
    let x = this.ball.x;
    let y = this.ball.y;
    let dx = this.ball.dx;
    let dy = this.ball.dy;
    const speed = this.ball.speed;

    const targetX = 100 - this.player2.width;
    let iterations = 0;

    while ((dx > 0 && x < targetX) || (dx < 0 && x > targetX)) {
      x += dx * speed * 0.1;
      y += dy * speed * 0.1;

      if (y <= this.ball.radius || y >= 100 - this.ball.radius) {
        dy = -dy;
        y = Math.max(this.ball.radius, Math.min(100 - this.ball.radius, y));
      }

      iterations++;
      if (iterations > 300) break;
    }

    return y;
  }

  private getDifficultyFactor(): number {
    const difficulties: Record<string, number> = {
      easy: 0.3,
      medium: 0.6,
      hard: 0.8,
      expert: 0.95,
    };
    return difficulties[this.settings.aiDifficulty] || 0.6;
  }

  private updatePhysics(): void {
    this.ball.x += this.ball.dx * this.ball.speed;
    this.ball.y += this.ball.dy * this.ball.speed;

    if (this.ball.y <= this.ball.radius || this.ball.y >= 100 - this.ball.radius) {
      this.ball.dy = -this.ball.dy;
      this.ball.y = Math.max(
        this.ball.radius,
        Math.min(100 - this.ball.radius, this.ball.y)
      );
    }

    if (this.checkPlayerCollision(this.player1)) {
      this.ball.dx = -this.ball.dx;
      const hitPosition = this.calculateHitPosition(this.player1);
      this.ball.dy = hitPosition * 2.5;
      this.ball.speed = Math.min(this.ball.speed * 1.08, this.settings.ballSpeed * 2);
      this.ball.x = this.player1.width + this.ball.radius;
    } else if (this.checkPlayerCollision(this.player2)) {
      this.ball.dx = -this.ball.dx;
      const hitPosition = this.calculateHitPosition(this.player2);
      this.ball.dy = hitPosition * 2.5;
      this.ball.speed = Math.min(this.ball.speed * 1.08, this.settings.ballSpeed * 2);
      this.ball.x = 100 - this.player2.width - this.ball.radius;
    }

    if (this.ball.x < 0) {
      this.player2.score++;
      this.resetBall();
    } else if (this.ball.x > 100) {
      this.player1.score++;
      this.resetBall();
    }
  }

  private calculateHitPosition(player: Player): number {
    const relativeY = this.ball.y - player.y;
    const normalizedY = relativeY / (player.height / 2);
    return Math.max(-1, Math.min(1, normalizedY));
  }

  private checkPlayerCollision(player: Player): boolean {
    const ballTop = this.ball.y - this.ball.radius;
    const ballBottom = this.ball.y + this.ball.radius;
    const playerTop = player.y - player.height / 2;
    const playerBottom = player.y + player.height / 2;

    if (ballTop > playerBottom || ballBottom < playerTop) {
      return false;
    }

    const boardEl = document.getElementById('game-board');
    if (!boardEl) return false;
    const boardRect = boardEl.getBoundingClientRect();
    const aspectRatio = boardRect.width / boardRect.height;
    const ballRadiusX = (this.ball.radius * aspectRatio) * 0.1;

    if (player.x === 0) {
      const ballLeftEdge = this.ball.x - ballRadiusX;
      const ballRightEdge = this.ball.x + ballRadiusX;

      return ballRightEdge >= 0 && ballLeftEdge <= player.width && this.ball.dx < 0;
    } else {
      const ballLeftEdge = this.ball.x - ballRadiusX;
      const ballRightEdge = this.ball.x + ballRadiusX;
      const paddleLeft = 100 - player.width;

      return ballLeftEdge <= 100 && ballRightEdge >= paddleLeft && this.ball.dx > 0;
    }
  }

  private resetBall(): void {
    this.ball.x = 50;
    this.ball.y = 50;
    this.ball.speed = this.settings.ballSpeed;
    this.ball.dx = Math.random() > 0.5 ? 1 : -1;
    this.ball.dy = (Math.random() - 0.5) * 0.5;

    this.updateBallSize();
    this.updatePlayerSizes();
  }

  private updateBallSize(): void {
    if (!this.boardEl || !this.ballEl) return;

    const boardRect = this.boardEl.getBoundingClientRect();
    const boardHeight = boardRect.height;

    const baseBallSize = 16;
    const ballSizePx = baseBallSize * (this.settings.ballSize / 2.0);
    const ballRadiusPercent = (ballSizePx / boardHeight) * 100;
    this.ball.radius = ballRadiusPercent;

    this.ballEl.style.width = ballSizePx + 'px';
    this.ballEl.style.height = ballSizePx + 'px';
  }

  private updatePlayerSizes(): void {
    if (!this.boardEl || !this.player1El || !this.player2El) return;

    const boardRect = this.boardEl.getBoundingClientRect();
    const boardHeight = boardRect.height;
    const boardWidth = boardRect.width;

    const playerHeight = (this.settings.playerSize / 100) * boardHeight;
    const playerWidthPx = 12;

    const playerWidthPercent = (playerWidthPx / boardWidth) * 100;
    const playerHeightPercent = (playerHeight / boardHeight) * 100;

    this.player1.width = playerWidthPercent;
    this.player1.height = playerHeightPercent;
    this.player2.width = playerWidthPercent;
    this.player2.height = playerHeightPercent;

    [this.player1El, this.player2El].forEach(el => {
      if (el) {
        el.style.width = playerWidthPx + 'px';
        el.style.height = playerHeight + 'px';
      }
    });
  }

  private updateDisplay(): void {
    if (!this.player1El || !this.player2El || !this.ballEl) return;

    this.player1El.style.left = this.player1.x + '%';
    this.player1El.style.top = this.player1.y + '%';
    this.player1El.style.transform = 'translateY(-50%)';

    this.player2El.style.right = (100 - this.player2.x) + '%';
    this.player2El.style.left = 'auto';
    this.player2El.style.top = this.player2.y + '%';
    this.player2El.style.transform = 'translateY(-50%)';

    this.ballEl.style.left = this.ball.x + '%';
    this.ballEl.style.top = this.ball.y + '%';
    this.ballEl.style.transform = 'translate(-50%, -50%)';

    if (this.score1El) this.score1El.textContent = this.player1.score.toString();
    if (this.score2El) this.score2El.textContent = this.player2.score.toString();
  }

  private checkGameEnd(): void {
    if (
      this.player1.score >= this.settings.winScore ||
      this.player2.score >= this.settings.winScore
    ) {
      this.endGame();
    }
  }

  private endGame(): void {
    this.isRunning = false;

    const winnerText = document.getElementById('game-winner-text');
    const finalScore = document.getElementById('game-final-score');

    let winner = '';
    if (this.player1.score >= this.settings.winScore) {
      winner = 'Player 1 Wins!';
    } else {
      if (this.mode === 'ai' || this.mode === 'training') {
        winner = 'AI Wins!';
      } else {
        winner = 'Player 2 Wins!';
      }
    }

    const gameResult: GameResult = {
      mode: this.mode,
      settings: this.settings,
      player1: this.player1.score,
      player2: this.player2.score,
    };

    if (this.onEndCallback) {
      this.onEndCallback({
        score1: this.player1.score,
        score2: this.player2.score,
      });
    } else {
      this.gameService.saveGame(gameResult);
    }

    if (winnerText) winnerText.textContent = winner;
    if (finalScore) {
      finalScore.textContent = `Final Score: ${this.player1.score} - ${this.player2.score}`;
    }

    const endOverlay = document.getElementById('game-end-overlay');
    if (endOverlay) endOverlay.classList.remove('hidden');
  }

  destroy(): void {
    this.isRunning = false;
    if (this.animationId) {
      cancelAnimationFrame(this.animationId);
    }
    this.removeEventListeners();
  }
}
