class PongApp {
  constructor() {
    this.currentUser = null;
    this.isLoggedIn = false;
    this.chatMessages = [];
    this.tournaments = [];
    this.stats = {};
    this.gameSettings = null;
    this.currentGame = null;
    this.onlineUsers = ['Vous'];
    this.API_BASE_URL = 'http://localhost:8000/api';
    
    this.initializeApp();
  }

  async initializeApp() {
    
    const savedUser = localStorage.getItem('pongUser');
    const authToken = localStorage.getItem('authToken');
    
    if (savedUser && authToken) {
      try {
        this.currentUser = JSON.parse(savedUser);
        this.isLoggedIn = true;
        this.showUserInfo();
      } catch (error) {
        localStorage.removeItem('pongUser');
        localStorage.removeItem('authToken');
      }
    }
    
    this.initializeGameSettings();
    
    this.initializeChat();
    
    this.setupEventListeners();
    
    await this.showSection('home');
    
  }

  initializeGameSettings() {
    this.gameSettings = new GameSettings();
    this.gameSettings.init();
  }

  async makeAPICall(endpoint, options = {}) {
    try {
      const authToken = localStorage.getItem('authToken');
      const headers = {
        'Content-Type': 'application/json',
        ...options.headers
      };
      
      if (authToken) {
        headers['Authorization'] = `Bearer ${authToken}`;
      }
      
      const response = await fetch(this.API_BASE_URL + endpoint, {
        ...options,
        headers
      });
      
      if (!response.ok) {
        throw new Error(`HTTP error! status: ${response.status}`);
      }
      
      return response.json();
    } catch (error) {
      throw error;
    }
  }

  setupEventListeners() {
    // Auth form submission
    const authForm = document.getElementById('auth-form');
    if (authForm) {
      authForm.addEventListener('submit', (e) => this.handleAuth(e));
    }
    
    // Chat input enter key
    const chatInput = document.getElementById('chat-input');
    if (chatInput) {
      chatInput.addEventListener('keypress', (e) => {
        if (e.key === 'Enter') {
          this.sendMessage();
        }
      });
    }
  }

  // ===== COMPONENT LOADING SYSTEM =====
  async loadComponent(componentName) {
    try {
      const response = await fetch(`/components/${componentName}.html`);
      const html = await response.text();
      return html;
    } catch (error) {
      console.error(`Error loading component ${componentName}:`, error);
      return `<div class="text-center p-8"><h2>Error loading ${componentName}</h2></div>`;
    }
  }

  async showSection(sectionName) {
    
    try {
      // Show loading indicator
      this.showLoadingIndicator(true);
      
      // Load component content
      const content = await this.loadComponent(sectionName);
      
      // Update main content
      const mainContent = document.getElementById('main-content');
      if (mainContent) {
        mainContent.innerHTML = `<div class="container mx-auto px-4 py-8">${content}</div>`;
      }
      
      // Initialize section-specific features
      this.initializeSectionFeatures(sectionName);
      
      // Update navigation
      this.updateNavigation(sectionName);
      
      
    } catch (error) {
      console.error(`Error loading section ${sectionName}:`, error);
      this.showNotification('Error loading page', 'error');
    } finally {
      // Hide loading indicator
      this.showLoadingIndicator(false);
    }
  }

  showLoadingIndicator(show) {
    const indicator = document.getElementById('loading-indicator');
    if (indicator) {
      if (show) {
        indicator.classList.remove('hidden');
      } else {
        indicator.classList.add('hidden');
      }
    }
  }

  updateNavigation(activeSection) {
    // Update navigation buttons state if needed
    const navButtons = document.querySelectorAll('nav button');
    navButtons.forEach(button => {
      button.classList.remove('active');
    });
  }

  initializeSectionFeatures(sectionName) {
    switch (sectionName) {
      case 'chat':
        this.initializeChatInterface();
        break;
      case 'tournament':
        this.initializeTournamentInterface();
        break;
      case 'stats':
        this.initializeStatsInterface();
        break;
      case 'settings':
        this.initializeSettingsInterface();
        break;
      case 'game':
        // Game initialization happens when starting a specific game mode
        break;
    }
  }

  initializeSettingsInterface() {
    if (this.gameSettings) {
      this.gameSettings.init();
      this.gameSettings.updatePreview();
    }
  }

  // ===== AUTHENTICATION SYSTEM =====
  showLogin() {
    const modal = document.getElementById('auth-modal');
    const title = document.getElementById('auth-title');
    const emailField = document.getElementById('auth-email');
    const submitBtn = document.getElementById('auth-submit');
    
    if (modal && title && submitBtn) {
      modal.dataset.type = 'login';
      title.textContent = 'Login';
      submitBtn.textContent = 'Login';
      submitBtn.className = 'w-full bg-pong-blue hover:bg-blue-700 py-2 rounded font-semibold transition-colors';
      
      if (emailField) emailField.classList.add('hidden');
      modal.classList.remove('hidden');
    }
  }

  showRegister() {
    const modal = document.getElementById('auth-modal');
    const title = document.getElementById('auth-title');
    const emailField = document.getElementById('auth-email');
    const submitBtn = document.getElementById('auth-submit');
    
    if (modal && title && submitBtn) {
      modal.dataset.type = 'register';
      title.textContent = 'Register';
      submitBtn.textContent = 'Register';
      submitBtn.className = 'w-full bg-pong-green hover:bg-green-700 py-2 rounded font-semibold transition-colors';
      
      if (emailField) emailField.classList.remove('hidden');
      modal.classList.remove('hidden');
    }
  }

  closeAuth() {
    const modal = document.getElementById('auth-modal');
    if (modal) modal.classList.add('hidden');
  }

  async handleAuth(event) {
    event.preventDefault();
    
    const modal = document.getElementById('auth-modal');
    const type = modal?.dataset.type || 'login';
    
    const username = document.getElementById('auth-username')?.value;
    const password = document.getElementById('auth-password')?.value;
    const email = document.getElementById('auth-email')?.value;
    
    if (!username || !password) {
      this.showNotification('Please fill in all fields', 'error');
      return;
    }
    
    if (type === 'register' && !email) {
      this.showNotification('Email is required for registration', 'error');
      return;
    }
    
    try {
      const endpoint = type === 'login' ? '/auth/login' : '/auth/register';
      const payload = type === 'login' 
        ? { username, password }
        : { username, password, email };
      
      const response = await fetch(this.API_BASE_URL + endpoint, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(payload)
      });
      
      const result = await response.json();
      
      if (result.success) {
        this.currentUser = result.data.user;
        this.isLoggedIn = true;
        
        // Store auth token if provided
        if (result.data.token) {
          localStorage.setItem('authToken', result.data.token);
        }
        
        localStorage.setItem('pongUser', JSON.stringify(this.currentUser));
        
        this.showUserInfo();
        this.closeAuth();
        this.showNotification(`${type === 'login' ? 'Logged in' : 'Registered'} successfully!`, 'success');
      } else {
        this.showNotification(result.message || `${type === 'login' ? 'Login' : 'Registration'} failed`, 'error');
      }
      
    } catch (error) {
      console.error('Auth error:', error);
      this.showNotification('Connection error. Please try again.', 'error');
    }
  }

  logout() {
    this.currentUser = null;
    this.isLoggedIn = false;
    localStorage.removeItem('pongUser');
    localStorage.removeItem('authToken');
    
    // Update UI
    const userInfo = document.getElementById('user-info');
    const authButtons = document.getElementById('auth-buttons');
    
    if (userInfo) userInfo.classList.add('hidden');
    if (authButtons) authButtons.classList.remove('hidden');
    
    this.showNotification('Logged out successfully', 'success');
    this.showSection('home');
  }

  showUserInfo() {
    if (!this.currentUser) return;
    
    const userInfo = document.getElementById('user-info');
    const authButtons = document.getElementById('auth-buttons');
    const userName = document.getElementById('user-name');
    
    if (userName) userName.textContent = this.currentUser.username;
    if (userInfo) userInfo.classList.remove('hidden');
    if (authButtons) authButtons.classList.add('hidden');
  }

  // ===== CHAT SYSTEM =====
  initializeChat() {
    // Initialize chat system
    this.chatMessages = [];
    this.onlineUsers = ['Vous'];
  }

  initializeChatInterface() {
    this.updateChatMessages();
    this.updateOnlineUsers();
    updateOnlineCount();
  }

  async sendMessage() {
    if (!this.isLoggedIn) {
      this.showNotification('Please login to send messages', 'error');
      return;
    }

    const chatInput = document.getElementById('chat-input');
    const message = chatInput?.value?.trim();
    
    if (!message) return;
    
    try {
      const result = await this.makeAPICall('/chat/messages', {
        method: 'POST',
        body: JSON.stringify({
          content: message,
          channelId: 'general'
        })
      });
      
      if (result.success) {
        chatInput.value = '';
        this.updateChatMessages();
      } else {
        this.showNotification('Failed to send message', 'error');
      }
    } catch (error) {
      console.error('Chat error:', error);
      this.showNotification('Chat connection error', 'error');
    }
  }

  updateChatMessages() {
    // Mock chat messages for now
    const chatContainer = document.getElementById('chat-messages');
    if (!chatContainer) return;
    
    chatContainer.innerHTML = `
      <div class="text-xs text-gray-500 mb-2">System: Welcome to the chat!</div>
      <div class="mb-2"><strong class="text-blue-400">Player1:</strong> Hello everyone!</div>
      <div class="mb-2"><strong class="text-green-400">You:</strong> Hi there!</div>
    `;
  }

  updateOnlineUsers() {
    const onlineContainer = document.getElementById('online-users');
    if (!onlineContainer) return;
    
    onlineContainer.innerHTML = this.onlineUsers.map(user => 
      `<div class="flex items-center space-x-2 p-2 hover:bg-gray-700 rounded">
        <div class="w-2 h-2 bg-green-400 rounded-full"></div>
        <span class="text-sm">${user}</span>
      </div>`
    ).join('');
  }

  // ===== TOURNAMENT SYSTEM =====
  initializeTournamentInterface() {
  }

  async joinTournament(tournamentId) {
    if (!this.isLoggedIn) {
      this.showNotification('Please login to join tournaments', 'error');
      return;
    }
    
    this.showNotification(`Joined tournament ${tournamentId}!`, 'success');
  }

  async createTournament() {
    if (!this.isLoggedIn) {
      this.showNotification('Please login to create tournaments', 'error');
      return;
    }
    
    this.showNotification('Tournament created!', 'success');
  }

  // ===== GAME SYSTEM =====
  startPvPGame() {
    if (!this.gameSettings) {
      this.showNotification('Game settings not available', 'error');
      return;
    }
    
    const settings = this.gameSettings.getSettings();
    this.showSection('game');
    
    // Initialize game with settings
    setTimeout(() => {
      try {
        this.currentGame = new PongGameSPA(settings, 'pvp');
      } catch (error) {
        console.error('Error starting PvP game:', error);
        this.showNotification('Error starting game', 'error');
      }
    }, 500);
  }

  startPvIAGame() {
    if (!this.gameSettings) {
      this.showNotification('Game settings not available', 'error');
      return;
    }
    
    const settings = this.gameSettings.getSettings();
    this.showSection('game');
    
    // Initialize game with settings  
    setTimeout(() => {
      try {
        this.currentGame = new PongGameSPA(settings, 'ai');
      } catch (error) {
        console.error('Error starting PvIA game:', error);
        this.showNotification('Error starting game', 'error');
      }
    }, 500);
  }

  // ===== STATS SYSTEM =====
  initializeStatsInterface() {
  }

  // ===== UTILITY FUNCTIONS =====
  showNotification(message, type = 'info') {
    // Create notification element
    const notification = document.createElement('div');
    notification.className = `fixed top-4 right-4 z-50 p-4 rounded-lg shadow-lg transition-all duration-300 ${this.getNotificationColor(type)}`;
    notification.innerHTML = `
      <div class="flex items-center space-x-2">
        <span>${message}</span>
        <button onclick="this.parentElement.parentElement.remove()" class="ml-2 text-white hover:text-gray-200">×</button>
      </div>
    `;
    
    document.body.appendChild(notification);
    
    // Auto remove after 3 seconds
    setTimeout(() => {
      if (notification.parentElement) {
        notification.remove();
      }
    }, 3000);
  }

  getNotificationColor(type) {
    switch (type) {
      case 'success': return 'bg-green-600 text-white';
      case 'error': return 'bg-red-600 text-white';
      case 'warning': return 'bg-yellow-600 text-white';
      default: return 'bg-blue-600 text-white';
    }
  }
}

// Classe du jeu Pong intégrée dans la SPA
class PongGameSPA {
    constructor(settings, mode) {
        this.settings = settings;
        this.mode = mode;
        this.isRunning = false;
        this.isPaused = false;
        this.animationId = null;
        
        // Éléments DOM
        this.boardEl = document.getElementById('game-board');
        this.player1El = document.getElementById('game-player1');
        this.player2El = document.getElementById('game-player2');
        this.ballEl = document.getElementById('game-ball');
        this.score1El = document.getElementById('game-score-player1');
        this.score2El = document.getElementById('game-score-player2');
        
        this.initializeGame();
        this.setupEventListeners();
        this.start();
    }

    initializeGame() {
        // Créer les objets de jeu (simulation simplifiée)
        this.player1 = {
            x: 0,
            y: 50,
            width: 5,
            height: this.settings.playerSize,
            speed: this.settings.playerSpeed,
            score: 0
        };

        this.player2 = {
            x: 100,
            y: 50,
            width: 5,
            height: this.settings.playerSize,
            speed: this.settings.playerSpeed,
            score: 0
        };

        this.ball = {
            x: 50,
            y: 50,
            radius: this.settings.ballSize,
            speed: this.settings.ballSpeed,
            dx: Math.random() > 0.5 ? 1 : -1,
            dy: (Math.random() - 0.5) * 0.5
        };

        this.setupBoard();
        this.updateDisplay();
    }

    setupBoard() {
        // Taille du terrain
        const screenHeight = window.innerHeight;
        const boardHeight = screenHeight * 0.7;
        const boardWidth = boardHeight * 1.5;

        this.boardEl.style.width = boardWidth + 'px';
        this.boardEl.style.height = boardHeight + 'px';

        // Taille des joueurs
        const playerHeight = (this.settings.playerSize / 100) * boardHeight;
        const playerWidth = playerHeight * 0.15;

        [this.player1El, this.player2El].forEach(el => {
            el.style.width = playerWidth + 'px';
            el.style.height = playerHeight + 'px';
        });

        // Taille de la balle
        const ballSize = (this.settings.ballSize / 100) * boardHeight * 0.1;
        this.ballEl.style.width = ballSize + 'px';
        this.ballEl.style.height = ballSize + 'px';
    }

    setupEventListeners() {
        this.keys = {};
        
        document.addEventListener('keydown', (e) => {
            this.keys[e.key.toLowerCase()] = true;
            
            if (e.key === 'Escape') {
                this.togglePause();
            }
        });

        document.addEventListener('keyup', (e) => {
            this.keys[e.key.toLowerCase()] = false;
        });
    }

    start() {
        this.isRunning = true;
        this.isPaused = false;
        this.gameLoop();
    }

    pause() {
        this.isPaused = true;
        document.getElementById('game-pause-overlay').classList.remove('hidden');
    }

    resume() {
        this.isPaused = false;
        document.getElementById('game-pause-overlay').classList.add('hidden');
        this.gameLoop();
    }

    togglePause() {
        if (this.isPaused) {
            this.resume();
        } else {
            this.pause();
        }
    }

    restart(settings, mode) {
        this.settings = settings;
        this.mode = mode;
        this.isPaused = false;
        document.getElementById('game-pause-overlay').classList.add('hidden');
        document.getElementById('game-end-overlay').classList.add('hidden');
        this.initializeGame();
        this.start();
    }

    gameLoop() {
        if (!this.isRunning || this.isPaused) return;

        this.handleInput();
        this.updatePhysics();
        this.updateDisplay();
        this.checkGameEnd();

        this.animationId = requestAnimationFrame(() => this.gameLoop());
    }

    handleInput() {
        // Joueur 1 (W/S)
        if (this.keys['w']) {
            this.player1.y = Math.max(this.player1.height/2, this.player1.y - this.player1.speed);
        }
        if (this.keys['s']) {
            this.player1.y = Math.min(100 - this.player1.height/2, this.player1.y + this.player1.speed);
        }

        // Joueur 2 ou IA
        if (this.mode === 'pvp') {
            if (this.keys['arrowup']) {
                this.player2.y = Math.max(this.player2.height/2, this.player2.y - this.player2.speed);
            }
            if (this.keys['arrowdown']) {
                this.player2.y = Math.min(100 - this.player2.height/2, this.player2.y + this.player2.speed);
            }
        } else if (this.mode === 'ai' || this.mode === 'training') {
            this.updateAI();
        }
    }

    updateAI() {
        const difficulty = this.getDifficultyFactor();
        const ballY = this.ball.y;
        const playerY = this.player2.y;
        
        // IA simple avec facteur de difficulté
        const targetY = ballY + (Math.random() - 0.5) * (1 - difficulty) * 20;
        
        if (Math.abs(targetY - playerY) > 1) {
            const moveSpeed = this.player2.speed * difficulty;
            if (targetY < playerY) {
                this.player2.y = Math.max(this.player2.height/2, this.player2.y - moveSpeed);
            } else {
                this.player2.y = Math.min(100 - this.player2.height/2, this.player2.y + moveSpeed);
            }
        }
    }

    getDifficultyFactor() {
        const difficulties = {
            'easy': 0.3,
            'medium': 0.6,
            'hard': 0.8,
            'expert': 0.95
        };
        return difficulties[this.settings.aiDifficulty] || 0.6;
    }

    updatePhysics() {
        // Mouvement de la balle
        this.ball.x += this.ball.dx * this.ball.speed;
        this.ball.y += this.ball.dy * this.ball.speed;

        // Rebonds sur les murs haut/bas
        if (this.ball.y <= this.ball.radius || this.ball.y >= 100 - this.ball.radius) {
            this.ball.dy = -this.ball.dy;
            this.ball.y = Math.max(this.ball.radius, Math.min(100 - this.ball.radius, this.ball.y));
        }

        // Collisions avec les joueurs
        if (this.checkPlayerCollision(this.player1) || this.checkPlayerCollision(this.player2)) {
            this.ball.dx = -this.ball.dx;
            // Ajouter un peu d'angle basé sur où la balle frappe le joueur
            this.ball.dy += (Math.random() - 0.5) * 0.3;
        }

        // Buts
        if (this.ball.x <= 0) {
            this.player2.score++;
            this.resetBall();
        } else if (this.ball.x >= 100) {
            this.player1.score++;
            this.resetBall();
        }
    }

    checkPlayerCollision(player) {
        const ballLeft = this.ball.x - this.ball.radius;
        const ballRight = this.ball.x + this.ball.radius;
        const ballTop = this.ball.y - this.ball.radius;
        const ballBottom = this.ball.y + this.ball.radius;

        const playerLeft = player.x - player.width/2;
        const playerRight = player.x + player.width/2;
        const playerTop = player.y - player.height/2;
        const playerBottom = player.y + player.height/2;

        return ballRight > playerLeft && ballLeft < playerRight &&
               ballBottom > playerTop && ballTop < playerBottom;
    }

    resetBall() {
        this.ball.x = 50;
        this.ball.y = 50;
        this.ball.dx = Math.random() > 0.5 ? 1 : -1;
        this.ball.dy = (Math.random() - 0.5) * 0.5;
    }

    updateDisplay() {
        // Position des joueurs
        this.player1El.style.left = this.player1.x + '%';
        this.player1El.style.top = (this.player1.y - this.player1.height/2) + '%';

        this.player2El.style.left = (this.player2.x - this.player2.width) + '%';
        this.player2El.style.top = (this.player2.y - this.player2.height/2) + '%';

        // Position de la balle
        this.ballEl.style.left = (this.ball.x - this.ball.radius/2) + '%';
        this.ballEl.style.top = (this.ball.y - this.ball.radius/2) + '%';

        // Scores
        this.score1El.textContent = this.player1.score;
        this.score2El.textContent = this.player2.score;
    }

    checkGameEnd() {
        if (this.player1.score >= this.settings.winScore || this.player2.score >= this.settings.winScore) {
            this.endGame();
        }
    }

    endGame() {
        this.isRunning = false;
        
        // Afficher l'écran de fin
        const winnerText = document.getElementById('game-winner-text');
        const finalScore = document.getElementById('game-final-score');
        
        let winner = '';
        if (this.player1.score >= this.settings.winScore) {
            winner = 'Joueur 1 Gagne !';
        } else {
            if (this.mode === 'ai' || this.mode === 'training') {
                winner = 'IA Gagne !';
            } else {
                winner = 'Joueur 2 Gagne !';
            }
        }
        
        winnerText.textContent = winner;
        finalScore.textContent = `Score final: ${this.player1.score} - ${this.player2.score}`;
        
        document.getElementById('game-end-overlay').classList.remove('hidden');
    }
}

// GameSettings class definition
class GameSettings {
    constructor() {
        this.defaultSettings = {
            ballSpeed: 0.3,
            ballSize: 2.0,
            playerSpeed: 1.0,
            playerSize: 30,
            winScore: 7,
            aiDifficulty: 'medium'
        };

        this.presets = {
            casual: {
                ballSpeed: 0.2,
                ballSize: 3.0,
                playerSpeed: 0.8,
                playerSize: 40,
                winScore: 5,
                aiDifficulty: 'easy'
            },
            balanced: {
                ballSpeed: 0.3,
                ballSize: 2.0,
                playerSpeed: 1.0,
                playerSize: 30,
                winScore: 7,
                aiDifficulty: 'medium'
            },
            competitive: {
                ballSpeed: 0.6,
                ballSize: 1.5,
                playerSpeed: 1.8,
                playerSize: 20,
                winScore: 11,
                aiDifficulty: 'hard'
            },
            chaos: {
                ballSpeed: 1.2,
                ballSize: 0.5,
                playerSpeed: 2.5,
                playerSize: 15,
                winScore: 15,
                aiDifficulty: 'expert'
            }
        };

        this.currentSettings = { ...this.defaultSettings };
    }

    async init() {
        await this.loadSettings();
        this.setupEventListeners();
        this.updateAllDisplays();
        this.updatePreview();
    }

    setupEventListeners() {
        this.setupSlider('ball-speed', 'ballSpeed');
        this.setupSlider('ball-size', 'ballSize');
        this.setupSlider('player-speed', 'playerSpeed');
        this.setupSlider('player-size', 'playerSize');
        this.setupSlider('win-score', 'winScore');

        const aiSelect = document.getElementById('ai-difficulty');
        if (aiSelect) {
            aiSelect.addEventListener('change', (e) => {
                this.currentSettings.aiDifficulty = e.target.value;
            });
        }
    }

    setupSlider(sliderId, settingKey) {
        const slider = document.getElementById(sliderId);
        const valueDisplay = document.getElementById(sliderId + '-value');
        
        if (slider && valueDisplay) {
            slider.addEventListener('input', (e) => {
                const value = settingKey === 'winScore' ? parseInt(e.target.value) : parseFloat(e.target.value);
                this.currentSettings[settingKey] = value;
                valueDisplay.textContent = value;
                this.updatePreview();
            });
        }
    }

    updateAllDisplays() {
        Object.keys(this.currentSettings).forEach(key => {
            const sliderId = this.getSliderIdFromKey(key);
            const slider = document.getElementById(sliderId);
            const valueDisplay = document.getElementById(sliderId + '-value');
            
            if (slider) slider.value = this.currentSettings[key];
            if (valueDisplay) valueDisplay.textContent = this.currentSettings[key];
        });

        const aiSelect = document.getElementById('ai-difficulty');
        if (aiSelect) aiSelect.value = this.currentSettings.aiDifficulty;
    }

    getSliderIdFromKey(key) {
        const mapping = {
            ballSpeed: 'ball-speed',
            ballSize: 'ball-size',
            playerSpeed: 'player-speed',
            playerSize: 'player-size',
            winScore: 'win-score'
        };
        return mapping[key] || key;
    }

    updatePreview() {
        const ball = document.getElementById('preview-ball');
        const player1 = document.getElementById('preview-player1');
        const player2 = document.getElementById('preview-player2');

        if (ball) {
            const ballSizePx = Math.max(2, this.currentSettings.ballSize * 6);
            ball.style.width = ballSizePx + 'px';
            ball.style.height = ballSizePx + 'px';
        }

        if (player1 && player2) {
            const playerHeight = Math.max(20, this.currentSettings.playerSize * 1.5);
            const playerWidth = Math.max(4, playerHeight * 0.15);
            
            [player1, player2].forEach(player => {
                player.style.height = playerHeight + 'px';
                player.style.width = playerWidth + 'px';
            });
        }
    }

    async loadPreset(presetName) {
        if (this.presets[presetName]) {
            this.currentSettings = { ...this.presets[presetName] };
            this.updateAllDisplays();
            this.updatePreview();
            
            // Save to backend if user is logged in
            if (window.app && window.app.isLoggedIn && window.app.currentUser) {
                try {
                    await window.app.makeAPICall(`/settings/${window.app.currentUser.id}/preset/${presetName}`, {
                        method: 'POST'
                    });
                } catch (error) {
                    console.error('Error saving preset to backend:', error);
                }
            }
            
            this.showNotification(`Configuration "${presetName}" chargée !`, 'success');
        }
    }

    async resetToDefault() {
        this.currentSettings = { ...this.defaultSettings };
        this.updateAllDisplays();
        this.updatePreview();
        
        // Save to backend if user is logged in
        if (window.app && window.app.isLoggedIn && window.app.currentUser) {
            try {
                await window.app.makeAPICall(`/settings/${window.app.currentUser.id}/reset`, {
                    method: 'POST'
                });
            } catch (error) {
                console.error('Error resetting settings in backend:', error);
            }
        }
        
        this.showNotification('Paramètres remis à zéro', 'info');
    }

    async saveSettings() {
        try {
            // Save locally
            localStorage.setItem('pongGameSettings', JSON.stringify(this.currentSettings));
            
            // Save to backend if user is logged in
            if (window.app && window.app.isLoggedIn && window.app.currentUser) {
                await window.app.makeAPICall(`/settings/${window.app.currentUser.id}`, {
                    method: 'POST',
                    body: JSON.stringify({
                        settings: this.currentSettings
                    })
                });
            }
            
            this.showNotification('Paramètres sauvegardés !', 'success');
        } catch (error) {
            console.error('Error saving settings:', error);
            this.showNotification('Erreur lors de la sauvegarde', 'error');
        }
    }

    async loadSettings() {
        try {
            // Try to load from backend if user is logged in
            if (window.app && window.app.isLoggedIn && window.app.currentUser) {
                const result = await window.app.makeAPICall(`/settings/${window.app.currentUser.id}`);
                if (result.success && result.data.settings) {
                    this.currentSettings = { ...this.defaultSettings, ...result.data.settings };
                    return;
                }
            }
            
            // Fallback to local storage
            const saved = localStorage.getItem('pongGameSettings');
            if (saved) {
                const parsedSettings = JSON.parse(saved);
                this.currentSettings = { ...this.defaultSettings, ...parsedSettings };
            }
        } catch (error) {
            console.warn('Erreur lors du chargement des paramètres:', error);
        }
    }

    showNotification(message, type = 'info') {
        // Utiliser le système de notification de l'app principale
        if (window.app) {
            window.app.showNotification(message, type);
        }
    }

    getSettings() {
        return { ...this.currentSettings };
    }
}

// Settings functions (delegated to GameSettings)
function loadPreset(presetName) {
  if (app?.gameSettings) {
    app.gameSettings.loadPreset(presetName);
  }
}

function resetToDefault() {
  if (app?.gameSettings) {
    app.gameSettings.resetToDefault();
  }
}

function saveSettings() {
  if (app?.gameSettings) {
    app.gameSettings.saveSettings();
  }
}

// Game functions
function startPvPGame() {
  app?.startPvPGame();
}

function startPvIAGame() {
  app?.startPvIAGame();
}

function startPvP() {
  app?.startPvPGame();
}

function startPvIA() {
  app?.startPvIAGame();
}

function resumeGame() {
  if (app?.currentGame) {
    app.currentGame.resume();
  }
}

function restartGame() {
  if (app?.currentGame && app?.gameSettings) {
    const settings = app.gameSettings.getSettings();
    app.currentGame.restart(settings, app.currentGame.mode);
  }
}

function pauseGame() {
  if (app?.currentGame) {
    app.currentGame.pause();
  }
}

async function updateOnlineCount() {
  try {
    const response = await fetch('/api/chat/online-users');
    if (!response.ok) {
      console.warn('Failed to fetch online users:', response.status);
      return;
    }
    const data = await response.json();
    const countElement = document.getElementById('online-count');
    if (countElement) {
      countElement.textContent = (data.data?.length ?? 0).toString();
    }
  } catch (error) {
    console.error('Error updating online count:', error);
    // Set default value if there's an error
    const countElement = document.getElementById('online-count');
    if (countElement) {
      countElement.textContent = '0';
    }
  }
}

// Remove the DOMContentLoaded event listener for updateOnlineCount
// document.addEventListener('DOMContentLoaded', updateOnlineCount);

// Global app instance and functions
let app;

// Initialize app when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
  app = new PongApp();
  window.app = app; // Make it globally accessible
});

// Global functions for HTML onclick handlers
function showSection(section) { app?.showSection(section); }
function showLogin() { app?.showLogin(); }
function showRegister() { app?.showRegister(); }
function closeAuth() { app?.closeAuth(); }
function logout() { app?.logout(); }
function sendMessage() { app?.sendMessage(); }
function joinTournament(id) { app?.joinTournament(id); }
function createTournament() { app?.createTournament(); }
function showChat() { app?.showSection('chat'); }
function showTournament() { app?.showSection('tournament'); }
function showStats() { app?.showSection('stats'); }
function showGameSettings() { app?.showSection('settings'); }
function openGameSettings() { app?.showSection('settings'); }
