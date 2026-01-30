import './style.css';
import { Router } from './core/Router';
import { I18nService } from './services/I18nService';
import { AccessibilityService } from './services/AccessibilityService';
import { AuthService } from './services/AuthService';
import { SettingsService } from './services/SettingsService';
import { PresenceService } from './services/PresenceService';
import { GameService } from './services/GameService';
import { TournamentService } from './services/TournamentService';
import { NotificationService } from './services/NotificationService';
import { FriendService } from './services/FriendService';
import { HomePage } from './components/HomePage';
import { GamePage } from './components/GamePage';
import { TournamentPage } from './components/TournamentPage';
import { StatsPage } from './components/StatsPage';
import { SettingsPage } from './components/SettingsPage';
import { PongGame } from './game/PongGame';
import type { GameMode } from './types';
import { ApiService } from './services/ApiService';

class App {
	private presenceTimer: number | null = null;
	private router: Router;
	private i18nService: I18nService;
	private accessibilityService: AccessibilityService;
	private authService: AuthService;
	private settingsService: SettingsService;
	private gameService: GameService;
	private friendService: FriendService;
	private tournamentService: TournamentService;
	private tournamentPage: TournamentPage | null = null;
	private notificationService: NotificationService;
	private currentGame: PongGame | null = null;
	private pendingGameMode: GameMode | null = null;
	private pendingTournament: { name: string; players: string[] } | null = null;
	private apiService: ApiService;

	private currentGameContext:
		| { type: 'normal' }
		| { type: 'tournament'; matchId: string } = { type: 'normal' };

	constructor() {
		this.router = Router.getInstance();
		this.i18nService = I18nService.getInstance();
		this.accessibilityService = AccessibilityService.getInstance();
		this.authService = AuthService.getInstance();
		this.settingsService = SettingsService.getInstance();
		this.gameService = GameService.getInstance();
		this.tournamentService = TournamentService.getInstance();
		this.notificationService = NotificationService.getInstance();
		this.friendService = FriendService.getInstance();
		this.apiService = ApiService.getInstance();

		this.i18nService.init();
		this.accessibilityService.init();
		this.setupRoutes();
		this.setupAuthUI();
		this.setupGlobalEventListeners();
		this.initialize();
		window.addEventListener('beforeunload', () => this.stopPresence());
	}

	private startPresence(): void {

		if (!this.authService.isAuthenticated()) return;

		PresenceService.online().catch(() => { });

		if (this.presenceTimer === null) {
			this.presenceTimer = window.setInterval(() => {
				if (this.authService.isAuthenticated()) {
					PresenceService.online().catch(() => { });
				}
			}, 15000);
		}
	}

	private stopPresence(): void {
		if (this.presenceTimer !== null) {
			clearInterval(this.presenceTimer);
			this.presenceTimer = null;
		}

		if (this.authService.isAuthenticated()) {
			PresenceService.offline().catch(() => { });
		}
	}


	private setupRoutes(): void {
		this.router.register('home', async () => {
			const page = new HomePage();
			page.mount();

			const main = document.getElementById('main-content') ?? document;
			this.i18nService.applyTranslations(main);

			setTimeout(() => {
				this.updateHomePageAuthState();
			}, 50);
		});

		this.router.register('game', async () => {
			const page = new GamePage();
			page.mount();

			const main = document.getElementById('main-content') ?? document;
			this.i18nService.applyTranslations(main);
		});

		this.router.register('tournament', async () => {
			this.tournamentPage = new TournamentPage();
			this.tournamentPage.mount();

			const main = document.getElementById('main-content') ?? document;
			this.i18nService.applyTranslations(main);

			await this.initializeTournamentPage();
		});

		this.router.register('stats', async () => {
			const page = new StatsPage();
			page.mount();

			const main = document.getElementById('main-content') ?? document;
			this.i18nService.applyTranslations(main);

			await this.initializeStatsPage();
		});

		this.router.register('settings', async () => {
			const page = new SettingsPage();
			page.mount();

			const main = document.getElementById('main-content') ?? document;
			this.i18nService.applyTranslations(main);

			this.initializeSettingsPage();
		});
	}

	private setupAuthUI(): void {
		this.authService.onAuthChange((user) => {
			const userInfo = document.getElementById('user-info');
			const authButtons = document.getElementById('auth-buttons');
			const userName = document.getElementById('user-name');
			const friendRequestBadge = document.getElementById('friend-request-badge');
			const notificationBadge = document.getElementById('notification-badge');

			const navAvatar = document.getElementById('nav-user-avatar') as HTMLElement | null;
			const navAvatarInitial = document.getElementById('nav-avatar-initial') as HTMLElement | null;

			if (user && userInfo && authButtons && userName) {

				userName.textContent = user.username;
				userInfo.classList.remove('hidden');
				authButtons.classList.add('hidden');

				const userLang = (user as any).language;
				if (userLang && ['en', 'fr', 'es'].includes(userLang)) {
					this.i18nService.setLanguage(userLang as 'en' | 'fr' | 'es');
				}

				if (navAvatar && navAvatarInitial) {
					if ((user as any).avatar_url) {
						navAvatar.style.backgroundImage = `url(${(user as any).avatar_url})`;
						navAvatar.style.backgroundSize = 'cover';
						navAvatar.style.backgroundPosition = 'center';
						navAvatarInitial.style.display = 'none';
					} else {
						navAvatar.style.backgroundImage = '';
						navAvatarInitial.style.display = 'block';
						navAvatarInitial.textContent = user.username.charAt(0).toUpperCase();
					}
				}

			} else if (userInfo && authButtons) {
				userInfo.classList.add('hidden');
				authButtons.classList.remove('hidden');
				friendRequestBadge?.classList.add('hidden');
				notificationBadge?.classList.add('hidden');
			}

			if (user) this.startPresence();
			else this.stopPresence();

			this.updateHomePageAuthState();
			this.updateNavButtonsAuthState();
		});

		const current = this.authService.getCurrentUser();
		if (current) {
			this.startPresence();
			const userInfo = document.getElementById('user-info');
			const authButtons = document.getElementById('auth-buttons');
			const userName = document.getElementById('user-name');
			const navAvatar = document.getElementById('nav-user-avatar') as HTMLElement | null;
			const navAvatarInitial = document.getElementById('nav-avatar-initial') as HTMLElement | null;

			if (userInfo && authButtons && userName) {
				userName.textContent = current.username;
				userInfo.classList.remove('hidden');
				authButtons.classList.add('hidden');
			}

			if (navAvatar && navAvatarInitial) {
				navAvatarInitial.textContent = current.username.charAt(0).toUpperCase();
			}

			this.updateHomePageAuthState();
			this.updateNavButtonsAuthState();
		}
	}

	private updateHomePageAuthState(): void {
		const chatBox = document.getElementById('home-chat-box');
		const statsBox = document.getElementById('home-stats-box');
		const chatIcon = chatBox?.querySelector('.text-4xl.mb-4');
		const statsIcon = statsBox?.querySelector('.text-4xl.mb-4');
		const chatButton = document.getElementById('home-chat-button');
		const statsButton = document.getElementById('home-stats-button');
		const isAuthenticated = this.authService.isAuthenticated();

		if (chatBox) {
			if (isAuthenticated) {
				chatBox.classList.remove('opacity-30', 'pointer-events-none');
				chatBox.classList.add('hover:border-purple-500');
				if (chatIcon) {
					chatIcon.classList.add('group-hover:scale-110', 'transition-transform');
				}
				if (chatButton) {
					chatButton.classList.remove('bg-purple-400');
					chatButton.classList.add('bg-purple-600', 'hover:bg-purple-700');
				}
			} else {
				chatBox.classList.add('opacity-30', 'pointer-events-none');
				chatBox.classList.remove('hover:border-purple-500');
				if (chatIcon) {
					chatIcon.classList.remove('group-hover:scale-110', 'transition-transform');
				}
				if (chatButton) {
					chatButton.classList.remove('bg-purple-600', 'hover:bg-purple-700');
					chatButton.classList.add('bg-purple-400');
				}
			}
		}

		if (statsBox) {
			if (isAuthenticated) {
				statsBox.classList.remove('opacity-30', 'pointer-events-none');
				statsBox.classList.add('hover:border-orange-500');
				if (statsIcon) {
					statsIcon.classList.add('group-hover:scale-110', 'transition-transform');
				}
				if (statsButton) {
					statsButton.classList.remove('bg-orange-400');
					statsButton.classList.add('bg-orange-600', 'hover:bg-orange-700');
				}
			} else {
				statsBox.classList.add('opacity-30', 'pointer-events-none');
				statsBox.classList.remove('hover:border-orange-500');
				if (statsIcon) {
					statsIcon.classList.remove('group-hover:scale-110', 'transition-transform');
				}
				if (statsButton) {
					statsButton.classList.remove('bg-orange-600', 'hover:bg-orange-700');
					statsButton.classList.add('bg-orange-400');
				}
			}
		}
	}

	private updateNavButtonsAuthState(): void {
		const navStatsButton = document.getElementById('nav-stats-button');
		const isAuthenticated = this.authService.isAuthenticated();

		if (navStatsButton) {
			if (isAuthenticated) {
				navStatsButton.classList.remove('hidden');
			} else {
				navStatsButton.classList.add('hidden');
			}
		}
	}

	private setupGlobalEventListeners(): void {
		const userMenuButton = document.getElementById('user-menu-button');
		const userMenuDropdown = document.getElementById('user-menu-dropdown');

		if (userMenuButton && userMenuDropdown) {
			userMenuButton.addEventListener('click', (e) => {
				e.stopPropagation();
				userMenuDropdown.classList.toggle('hidden');
			});
		}

		const notificationsButton = document.getElementById('notifications-button');
		const notificationsDropdown = document.getElementById('notifications-dropdown');

		if (notificationsButton && notificationsDropdown) {
			notificationsButton.addEventListener('click', (e) => {
				e.stopPropagation();
				notificationsDropdown.classList.toggle('hidden');
			});
		}

		document.addEventListener('click', (e) => {
			const target = e.target as HTMLElement;

			let actionElement = target;
			let action = target.dataset.action;

			if (!action) {
				actionElement = target.closest('[data-action]') as HTMLElement;
				if (actionElement) {
					action = actionElement.dataset.action;
				}
			}

			if (userMenuDropdown && !userMenuDropdown.contains(target) && !userMenuButton?.contains(target)) {
				userMenuDropdown.classList.add('hidden');
			}

			if (notificationsDropdown && !notificationsDropdown.contains(target) && !notificationsButton?.contains(target)) {
				notificationsDropdown.classList.add('hidden');
			}

			if (target.id === 'profile-modal') {
				this.closeProfileModal();
			}

			if (target.id === 'friendlist-modal') {
				this.closeFriendlistModal();
			}

			if (!action) return;

			this.handleAction(action, actionElement);
		});

		document.addEventListener('keydown', (e) => {
			if (e.key === 'Escape') {
				const authModal = document.getElementById('auth-modal');
				const profileModal = document.getElementById('profile-modal');
				const friendlistModal = document.getElementById('friendlist-modal');

				if (authModal && !authModal.classList.contains('hidden')) {
					this.closeAuthModal();
				} else if (profileModal && !profileModal.classList.contains('hidden')) {
					this.closeProfileModal();
				} else if (friendlistModal && !friendlistModal.classList.contains('hidden')) {
					this.closeFriendlistModal();
				} else {
					this.closeUserMenu();
					this.closeNotificationsMenu();
					const currentRoute = this.router.getCurrentRoute();
					if (['settings', 'tournament', 'stats'].includes(currentRoute)) {
						this.router.navigate('home');
					}
				}
			}
		});
	}

	private closeNotificationsMenu(): void {
		const menu = document.getElementById('notifications-dropdown');
		if (menu) menu.classList.add('hidden');
	}

	private async handleAction(action: string, element: HTMLElement): Promise<void> {
		switch (action) {

			case 'navigate-home':
				this.currentGame?.destroy();
				this.currentGame = null;
				await this.router.navigate('home');
				break;
			case 'navigate-tournament':
				await this.router.navigate('tournament');
				break;
			case 'navigate-stats':
				await this.router.navigate('stats');
				break;
			case 'navigate-settings':
				await this.router.navigate('settings');
				break;
			case 'navigate-profile':
				this.showProfileModal();
				this.closeUserMenu();
				break;
			case 'save-profile':
				await this.handleProfileSubmit();
				break;
			case 'close-profile':
				await this.closeProfileModal();
				break;
			case 'show-password-view':
				this.showPasswordView();
				break;
			case 'update-password':
				this.handlePasswordSubmit();
				break;
			case 'profile-back':
				this.showMainProfileView();
				break;
			case 'navigate-friendlist':
				this.showFriendlistModal();
				this.closeUserMenu();
				break;
			case 'close-friendlist':
				this.closeFriendlistModal();
				break;
			case 'friendlist-friends-tab':
				this.switchFriendlistTab('friends');
				break;
			case 'friendlist-requests-tab':
				this.switchFriendlistTab('requests');
				break;
			case 'add-friend':
				this.handleAddFriend();
				break;
			case 'remove-friend': {
				const id = element.dataset.friendId;
				if (id) {
					await this.handleRemoveFriend(id);
					await this.loadFriendList();
				}
				break;
			}
			case 'accept-friend': {
				const id = element.dataset.friendId;
				if (id) {
					await this.friendService.acceptFriend(id);
					await this.loadFriendRequests();
					await this.loadFriendList();
				}
				break;
			}
			case 'decline-friend': {
				const id = element.dataset.friendId;
				if (id) {
					await this.friendService.declineFriend(id);
					await this.loadFriendRequests();
				}
				break;
			}
			case 'open-friend-profile': {
				const id = element.dataset.friendId;
				if (id) await this.showFriendProfile(id);
				break;
			}
			case 'close-friend-profile':
				this.closeFriendProfile();
				break;


			case 'start-pvp':
				this.pendingGameMode = 'pvp';
				await this.router.navigate('settings');
				break;
			case 'start-ai':
				this.pendingGameMode = 'ai';
				await this.router.navigate('settings');
				break;
			case 'launch-game':
				const mode = this.pendingGameMode || 'pvp';
				await this.startGame(mode);
				this.pendingGameMode = null;
				break;
			case 'resume-game':
				this.currentGame?.resume();
				break;
			case 'restart-game':
				if (this.currentGame) {
					const settings = this.settingsService.getSettings();
					this.currentGame.restart(settings, 'pvp');
				}
				break;
			case 'pause-game':
				this.currentGame?.pause();
				break;


			case 'show-login':
				this.showLoginModal();
				break;
			case 'show-register':
				this.showRegisterModal();
				break;
			case 'login-github':
				window.location.href = 'https://localhost:3001/auth/github';
				break;
			case 'close-auth':
				this.closeAuthModal();
				break;
			case 'logout':
				await this.authService.logout();
				await this.router.navigate('home');
				this.closeUserMenu();
				this.closeNotificationsMenu();
				break;

			case 'load-tournament': {
				const tid = element.dataset.tournamentId;
				if (tid) {
					await this.loadTournamentFromBackend(tid);
				}
				break;
			}



			case 'join-tournament':
				const tournamentId = element.dataset.tournamentId;
				if (tournamentId) await this.joinTournament(tournamentId);
				break;
			case 'create-tournament':
				this.showTournamentModal();
				break;
			case 'close-tournament-modal':
				this.closeTournamentModal();
				break;
			case 'confirm-tournament-settings':
				if (!this.pendingTournament) {
					this.closeTournamentSettingsModal();
					break;
				}

				try {
					await this.tournamentService.createLocalTournament(
						this.pendingTournament.name,
						this.pendingTournament.players
					);
				} catch (e: any) {
					if (e?.message === 'INVALID_PLAYERS_COUNT') {
						alert('You must have exactly 4 players.');
					} else {
						alert('Failed to create tournament on server.');
					}
					this.pendingTournament = null;
					this.closeTournamentSettingsModal();
					break;
				}

				this.pendingTournament = null;
				this.closeTournamentSettingsModal();

				await this.router.navigate('tournament');
				if (this.tournamentPage) {
					this.tournamentPage.refreshFromService();
				}
				break;
			case 'confirm-create-tournament':
				await this.handleCreateTournamentConfirm();
				break;
			case 'open-tournament-result-modal': {
				const matchId = element.dataset.matchId;
				if (matchId) this.showTournamentResultModal(matchId);
				break;
			}
			case 'close-tournament-result-modal':
				this.closeTournamentResultModal();
				break;
			case 'confirm-tournament-result':
				await this.handleConfirmTournamentResult();
				break;
			case 'start-tournament-match': {
				const matchId = element.dataset.matchId;
				const p1 = element.dataset["data-player-id1"];
				const p2 = element.dataset["data-player-id2"];
				const userid = element.dataset["data-userid"];
				if (matchId) {
					await this.startGame('tournament', { type: 'tournament', matchId, userId: (p1 == userid || p2 == userid) ? true : false });
				}
				break;
			}


			case 'save-settings':
				await this.settingsService.saveSettings();
				break;
			case 'reset-settings':
				await this.settingsService.resetToDefault();
				this.updateSettingsUI();
				break;
			case 'load-preset':
				const preset = element.dataset.preset;
				if (preset) {
					await this.settingsService.loadPreset(preset);
					this.updateSettingsUI();
				}
				break;
			case 'set-language': {
				const lang = element.dataset.lang as 'en' | 'fr' | 'es' | undefined;
				console.log("triggered")
				if (lang) {
					this.i18nService.setLanguage(lang);
					await this.updateUserLanguage(lang);
				}
				break;
			}

			case 'toggle-high-contrast':
				this.accessibilityService.toggleHighContrast();
				break;

			case 'increase-font':
				this.accessibilityService.increaseFont();
				break;

			case 'decrease-font':
				this.accessibilityService.decreaseFont();
				break;

		}
	}

	private async updateUserLanguage(lang: 'en' | 'fr' | 'es'): Promise<void> {
		if (!this.authService.isAuthenticated()) return;

		try {
			const res = await this.apiService.post<unknown>('/user/language', {
				language: lang,
			});

			if (!res.success) {
				console.error('Failed to update language on backend:', res.message);
			}
		} catch (e) {
			console.error('Failed to update language on backend', e);
		}
	}




	private async startGame(
		mode: GameMode,
		context?: { type: 'tournament'; matchId: string }
	): Promise<void> {
		if (this.currentGame) {
			this.currentGame.destroy();
			this.currentGame = null;
		}
		this.currentGameContext = context ?? { type: 'normal' };

		await this.router.navigate('game');

		setTimeout(() => {
			const settings = this.settingsService.getSettings();

			const onEnd = ({ score1, score2 }: { score1: number; score2: number }) => {

				if (context?.type === 'tournament') {
					const t = this.tournamentService.getLocalTournament();
					if (t) {
						const match = t.matches.find((m) => m.id === context.matchId);
						const firstPlayer = t.players[0];

						const involvesFirstPlayer =
							!!match &&
							!!firstPlayer &&
							(
								match.player1?.id === firstPlayer.id ||
								match.player2?.id === firstPlayer.id
							);

						if (involvesFirstPlayer) {
							this.gameService.saveGame({
								mode: 'tournament',
								settings,
								player1: score1,
								player2: score2,
							});
						}

						this.tournamentService.updateLocalMatchScore(
							context.matchId,
							score1,
							score2
						);
					}


					this.router.navigate('tournament');
					if (this.tournamentPage) {
						this.tournamentPage.refreshFromService();
					}
					return;
				}


				this.gameService.saveGame({
					mode,
					settings,
					player1: score1,
					player2: score2,
				});
			};

			let options:
				| undefined
				| {
					onEnd?: (result: { score1: number; score2: number }) => void;
					playerLabels?: { left: string; right: string };
				};

			if (context?.type === 'tournament') {
				const t = this.tournamentService.getLocalTournament();
				if (t) {
					const match = t.matches.find((m) => m.id === context.matchId);
					if (match?.player1 && match?.player2) {
						options = {
							playerLabels: {
								left: match.player1.name,
								right: match.player2.name,
							},
							onEnd,
						};
					} else {
						options = { onEnd };
					}
				} else {
					options = { onEnd };
				}
			} else {
				options = { onEnd };
			}

			this.currentGame = new PongGame(settings, mode, options);
		}, 100);
	}

	private showLoginModal(): void {
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

	private showRegisterModal(): void {
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

	private closeAuthModal(): void {
		const modal = document.getElementById('auth-modal');
		if (modal) modal.classList.add('hidden');
	}

	private closeUserMenu(): void {
		const menu = document.getElementById('user-menu-dropdown');
		if (menu) menu.classList.add('hidden');
	}

	private async showProfileModal(): Promise<void> {
		const modal = document.getElementById('profile-modal');


		await this.authService.refreshCurrentUser();
		const user = this.authService.getCurrentUser();
		(document.getElementById('profile-games-played') as HTMLElement)!.textContent = String(user?.games_played ?? 0);
		(document.getElementById('profile-games-won') as HTMLElement)!.textContent = String(user?.games_won ?? 0);
		(document.getElementById('profile-games-lost') as HTMLElement)!.textContent = String(user?.games_lost ?? 0);
		const wr = user?.win_rate ?? 0;
		(document.getElementById('profile-win-rate') as HTMLElement)!.textContent = `${wr.toFixed(1)}%`;

		const idEl = document.getElementById('profile-user-id') as HTMLElement | null;
		if (idEl && user?.id) {

			idEl.textContent = `#${user.id}`;
		}

		if (modal && user) {
			const usernameInput = document.getElementById('profile-username') as HTMLInputElement;
			if (usernameInput) usernameInput.value = user.username;

			const emailInput = document.getElementById('profile-email') as HTMLInputElement;
			if (emailInput && user.email) emailInput.value = user.email;

			const avatarPreview = document.getElementById('profile-avatar-preview') as HTMLElement | null;
			if (avatarPreview) {
				if (user.avatar_url) {
					avatarPreview.style.backgroundImage = `url(${user.avatar_url})`;
					avatarPreview.style.backgroundSize = 'cover';
					avatarPreview.style.backgroundPosition = 'center';
					const span = avatarPreview.querySelector('span') as HTMLElement | null;
					if (span) span.style.display = 'none';
				} else {

				}
			}


			const avatarInput = document.getElementById('profile-avatar-upload') as HTMLInputElement;
			if (avatarInput && !avatarInput.dataset.bound) {
				avatarInput.addEventListener('change', (e) => this.handleAvatarUpload(e));

				avatarInput.dataset.bound = 'true';
			}

			this.showMainProfileView();
			modal.classList.remove('hidden');
		}
	}


	private closeProfileModal(): void {
		const modal = document.getElementById('profile-modal');
		if (modal) modal.classList.add('hidden');
	}

	private showPasswordView(): void {
		const mainView = document.getElementById('profile-main-view');
		const passwordView = document.getElementById('profile-password-view');
		const backButton = document.querySelector('[data-action="profile-back"]');

		if (mainView && passwordView && backButton) {
			mainView.classList.add('hidden');
			passwordView.classList.remove('hidden');
			backButton.classList.remove('hidden');


			const currentPasswordInput = document.getElementById('profile-current-password') as HTMLInputElement;
			const newPasswordInput = document.getElementById('profile-new-password') as HTMLInputElement;
			const confirmPasswordInput = document.getElementById('profile-confirm-password') as HTMLInputElement;

			if (currentPasswordInput) currentPasswordInput.value = '';
			if (newPasswordInput) newPasswordInput.value = '';
			if (confirmPasswordInput) confirmPasswordInput.value = '';
		}
	}

	private showMainProfileView(): void {
		const mainView = document.getElementById('profile-main-view');
		const passwordView = document.getElementById('profile-password-view');
		const backButton = document.querySelector('[data-action="profile-back"]');

		if (mainView && passwordView && backButton) {
			mainView.classList.remove('hidden');
			passwordView.classList.add('hidden');
			backButton.classList.add('hidden');
		}
	}

	private async showFriendlistModal(): Promise<void> {
		const modal = document.getElementById('friendlist-modal');
		if (modal) modal.classList.remove('hidden');

		const errorDiv = document.getElementById('friendlist-error');
		const searchInput = document.getElementById('friendlist-search') as HTMLInputElement;

		if (errorDiv) errorDiv.classList.add('hidden');
		if (searchInput) {
			searchInput.classList.remove('border-red-500', 'focus:border-red-600');
			searchInput.classList.add('border-gray-700', 'focus:border-pong-blue');
			searchInput.value = '';
		}

		this.switchFriendlistTab('friends');

		await this.loadFriendList();
	}

	private async loadFriendList(): Promise<void> {
		const list = document.getElementById('friends-list');
		if (!list) return;


		list.innerHTML = `<div class="text-gray-400 text-sm">Loading friends...</div>`;

		const friends = await this.friendService.getFriends();

		if (!friends.length) {
			list.innerHTML = `<div class="text-gray-400 text-sm">No friends yet.</div>`;
			return;
		}

		list.innerHTML = friends
			.map((f) => {
				const isOnline = Number((f as any).status) === 1;
				const dot = `<span class="inline-block w-2 h-2 rounded-full ${isOnline ? 'bg-green-400' : 'bg-gray-500'}"></span>`;
				const label = isOnline ? 'Online' : 'Offline';
				const labelClass = isOnline ? 'text-green-400' : 'text-gray-500';
				const avatarStyle = f.avatar_url
					? `background-image:url(${f.avatar_url});background-size:cover;background-position:center;`
					: '';

				return `
          <div class="flex items-center justify-between py-2 border-b border-gray-800">
            <div class="flex items-center gap-3 cursor-pointer"
                data-action="open-friend-profile" data-friend-id="${f.id}">
              <div class="w-8 h-8 rounded-full bg-gray-700 flex items-center justify-center text-sm font-semibold overflow-hidden" style="${avatarStyle}">
                ${!f.avatar_url ? this.escapeHtml(f.username.charAt(0).toUpperCase()) : ''}
              </div>
              <div>
                <div class="text-white text-sm flex items-center gap-2">
                  ${this.escapeHtml(f.username)} ${dot}
                </div>
                <div class="${labelClass} text-xs">${label}</div>
                ${f.email ? `<div class="text-gray-500 text-xs">${this.escapeHtml(f.email)}</div>` : ''}
              </div>
            </div>
            <button
              class="text-xs text-red-400 hover:text-red-200"
              data-action="remove-friend"
              data-friend-id="${f.id}"
            >
              Remove
            </button>
          </div>
        `;
			})
			.join('');


	}



	private closeFriendlistModal(): void {
		const modal = document.getElementById('friendlist-modal');
		if (modal) modal.classList.add('hidden');
	}

	private switchFriendlistTab(tab: 'friends' | 'requests'): void {
		const friendsList = document.getElementById('friends-list');
		const requestsList = document.getElementById('requests-list');
		const friendsTab = document.querySelector('[data-action="friendlist-friends-tab"]');
		const requestsTab = document.querySelector('[data-action="friendlist-requests-tab"]');

		if (tab === 'friends') {
			if (friendsList) friendsList.classList.remove('hidden');
			if (requestsList) requestsList.classList.add('hidden');

			if (friendsTab) {
				friendsTab.classList.remove('text-gray-400');
				friendsTab.classList.add('text-white', 'font-semibold', 'border-b-2', 'border-pong-blue');
			}
			if (requestsTab) {
				requestsTab.classList.remove('text-white', 'font-semibold', 'border-b-2', 'border-pong-blue');
				requestsTab.classList.add('text-gray-400');
			}
			this.loadFriendList();
		} else {
			if (friendsList) friendsList.classList.add('hidden');
			if (requestsList) requestsList.classList.remove('hidden');

			if (requestsTab) {
				requestsTab.classList.remove('text-gray-400');
				requestsTab.classList.add('text-white', 'font-semibold', 'border-b-2', 'border-pong-blue');
			}
			if (friendsTab) {
				friendsTab.classList.remove('text-white', 'font-semibold', 'border-b-2', 'border-pong-blue');
				friendsTab.classList.add('text-gray-400');
			}
			this.loadFriendRequests();
		}
	}

	private async handleAddFriend(): Promise<void> {
		const searchInput = document.getElementById('friendlist-search') as HTMLInputElement;
		const errorDiv = document.getElementById('friendlist-error');

		if (!searchInput || !searchInput.value.trim()) {
			return;
		}

		const value = searchInput.value.trim();

		if (value.startsWith('user-')) {
			const ok = await this.friendService.addFriendById(value);
			if (ok) {

				await this.loadFriendList();
				searchInput.value = '';
				if (errorDiv) errorDiv.classList.add('hidden');
				return;
			} else {
			}
		}

		searchInput.classList.remove('border-gray-700', 'focus:border-pong-blue');
		searchInput.classList.add('border-red-500', 'focus:border-red-600');

		if (errorDiv) {
			errorDiv.textContent = 'Pour le moment, entre un ID utilisateur (user-xxxx).';
			errorDiv.classList.remove('hidden');
		}

		searchInput.addEventListener(
			'input',
			() => {
				searchInput.classList.remove('border-red-500', 'focus:border-red-600');
				searchInput.classList.add('border-gray-700', 'focus:border-pong-blue');
				if (errorDiv) errorDiv.classList.add('hidden');
			},
			{ once: true }
		);
	}


	private async handleRemoveFriend(friendId: string): Promise<void> {
		await this.friendService.removeFriend(friendId);
	}

	private async loadFriendRequests(): Promise<void> {
		const container = document.getElementById('requests-list');
		if (!container) return;

		container.innerHTML = `<div class="text-gray-400 text-sm">Loading requests...</div>`;

		const reqs = await this.friendService.getFriendRequests();

		if (!reqs.length) {
			container.innerHTML = `<div class="text-gray-400 text-sm">No friend requests.</div>`;
			return;
		}

		container.innerHTML = reqs
			.map(
				(r) => `
        <div class="flex items-center justify-between py-2 border-b border-gray-800">
          <div class="flex items-center gap-3">
            <div class="w-8 h-8 rounded-full bg-gray-700 flex items-center justify-center text-sm font-semibold">
              ${r.username ? r.username.charAt(0).toUpperCase() : 'U'}
            </div>
            <div>
              <div class="text-white text-sm">${this.escapeHtml(r.username)}</div>
              ${r.email ? `<div class="text-gray-500 text-xs">${this.escapeHtml(r.email)}</div>` : ''}
            </div>
          </div>
          <div class="flex gap-2">
            <button class="text-xs bg-pong-green px-2 py-1 rounded" data-action="accept-friend" data-friend-id="${r.id}">
              Accept
            </button>
            <button class="text-xs text-red-400" data-action="decline-friend" data-friend-id="${r.id}">
              Decline
            </button>
          </div>
        </div>
      `
			)
			.join('');
	}


	private async handleAuthSubmit(e: Event): Promise<void> {
		e.preventDefault();

		const modal = document.getElementById('auth-modal');
		const type = modal?.dataset.type || 'login';

		const usernameInput = document.getElementById('auth-username') as HTMLInputElement;
		const passwordInput = document.getElementById('auth-password') as HTMLInputElement;
		const emailInput = document.getElementById('auth-email') as HTMLInputElement;

		if (!usernameInput?.value || !passwordInput?.value) return;

		let success = false;
		if (type === 'login') {
			success = await this.authService.login(usernameInput.value, passwordInput.value);
		} else {
			if (!emailInput?.value) return;
			success = await this.authService.register(
				usernameInput.value,
				passwordInput.value,
				emailInput.value
			);
		}

		if (success) {
			this.closeAuthModal();
			usernameInput.value = '';
			passwordInput.value = '';
			if (emailInput) emailInput.value = '';
		}
	}

	private async showFriendProfile(friendId: string): Promise<void> {
		const modal = document.getElementById('friend-profile-modal');
		if (!modal) return;

		const data = await this.friendService.getFriendProfile(friendId);
		if (!data) return;

		const avatar = document.getElementById('friend-profile-avatar') as HTMLElement | null;
		const initial = document.getElementById('friend-profile-initial') as HTMLElement | null;
		const username = document.getElementById('friend-profile-username');
		const played = document.getElementById('friend-profile-played');
		const won = document.getElementById('friend-profile-won');
		const lost = document.getElementById('friend-profile-lost');
		const wr = document.getElementById('friend-profile-wr');


		if (avatar && initial) {
			if (data.avatar_url) {
				avatar.style.backgroundImage = `url(${data.avatar_url})`;
				avatar.style.backgroundSize = 'cover';
				avatar.style.backgroundPosition = 'center';
				initial.style.display = 'none';
			} else {
				avatar.style.backgroundImage = '';
				initial.style.display = 'flex';
				initial.textContent = data.username.charAt(0).toUpperCase();
			}
		}

		if (username) username.textContent = data.username;

		const games_played = Number(
			(data as any).games_played ?? (data as any).gamesPlayed ?? 0
		);
		const games_won = Number(
			(data as any).games_won ?? (data as any).gamesWon ?? 0
		);
		const games_lost = Number(
			(data as any).games_lost ?? (data as any).gamesLost ?? 0
		);

		if (played) played.textContent = String(Number.isFinite(games_played) ? games_played : 0);
		if (won) won.textContent = String(Number.isFinite(games_won) ? games_won : 0);
		if (lost) lost.textContent = String(Number.isFinite(games_lost) ? games_lost : 0);

		let win_rate = Number((data as any).win_rate ?? 0);

		if (win_rate <= 1 && (games_won + games_lost > 0 || (data as any).win_rate <= 1)) {
			win_rate = win_rate * 100;
		}

		if (!(data as any).win_rate && games_played > 0) {
			win_rate = (games_won / games_played) * 100;
		}

		if (!Number.isFinite(win_rate)) {
			win_rate = 0;
		}

		if (wr) wr.textContent = `${win_rate.toFixed(1)}%`;

		modal.classList.remove('hidden');
	}



	private closeFriendProfile(): void {
		const modal = document.getElementById('friend-profile-modal');
		if (modal) modal.classList.add('hidden');
	}

	private showTournamentModal(): void {
		if (!this.authService.isAuthenticated()) {
			this.showLoginModal();
			return;
		}

		const modal = document.getElementById('tournament-modal');
		if (modal) modal.classList.remove('hidden');
	}

	private closeTournamentModal(): void {
		const modal = document.getElementById('tournament-modal');
		if (modal) modal.classList.add('hidden');
	}

	private async joinTournament(id: string): Promise<void> {
		if (!this.authService.isAuthenticated()) {
			this.showLoginModal();
			return;
		}

		await this.tournamentService.joinTournament(id);
	}

	private async initializeTournamentPage(): Promise<void> {
		if (!this.authService.isAuthenticated()) {
			if (this.tournamentPage) {
				this.tournamentPage.renderUserTournaments([]);
				this.tournamentPage.refreshFromService();
			}
			return;
		}

		await this.authService.refreshCurrentUser?.();
		const user = this.authService.getCurrentUser?.();
		if (!user || !(user as any).id) return;

		const tournaments = await this.tournamentService.fetchUserTournaments(
			(user as any).id
		);

		let local = this.tournamentService.getLocalTournament();
		let recordToLoad: any | undefined;

		if (!local) {
			const inProgress = tournaments.filter((t: any) => t.status === 'in-progress');
			recordToLoad = inProgress[0] ?? tournaments[0];

			if (recordToLoad) {
				this.tournamentService.hydrateLocalFromBackendRecord(recordToLoad);
				local = this.tournamentService.getLocalTournament();
			} else {
				this.tournamentService.resetLocalTournament();
				local = null;
			}
		} else {
			recordToLoad = tournaments.find((t: any) => t.id === local?.backendId) ?? undefined;
		}

		if (this.tournamentPage) {
			const selectedId = local?.backendId ?? recordToLoad?.id ?? null;

			this.tournamentPage.renderUserTournaments(tournaments, selectedId);
			this.tournamentPage.refreshFromService();
		}
	}






	private async initializeStatsPage(): Promise<void> {
		if (!this.authService.isAuthenticated()) {
			return;
		}

		await this.authService.refreshCurrentUser();
		const user = this.authService.getCurrentUser();
		if (!user) return;

		const gamesPlayed = user.games_played ?? 0;
		const gamesWon = user.games_won ?? 0;
		const gamesLost = user.games_lost ?? 0;
		const winRate = Number.isFinite(user.win_rate) ? user.win_rate : 0;

		const playedEl = document.getElementById('stat-games-played');
		const wonEl = document.getElementById('stat-games-won');
		const lostEl = document.getElementById('stat-games-lost');
		const wrEl = document.getElementById('stat-win-rate');

		if (playedEl) playedEl.textContent = String(gamesPlayed);
		if (wonEl) wonEl.textContent = String(gamesWon);
		if (lostEl) lostEl.textContent = String(gamesLost);
		if (wrEl) wrEl.textContent = `${winRate.toFixed(1)}%`;

		const totalPerfEl = document.getElementById('perf-total-games');
		const perfWrEl = document.getElementById('perf-win-rate');
		if (totalPerfEl) totalPerfEl.textContent = String(gamesPlayed);
		if (perfWrEl) perfWrEl.textContent = `${winRate.toFixed(1)}%`;

		const chart = document.getElementById('stat-winloss-chart');
		if (chart) {
			const total = gamesWon + gamesLost;

			if (total === 0) {
				chart.innerHTML = `<div class="text-sm text-gray-500">No games yet</div>`;
			} else {
				const winPct = (gamesWon / total) * 100;
				const lossPct = (gamesLost / total) * 100;

				chart.innerHTML = `
          <div class="h-4 bg-gray-800 rounded-full overflow-hidden flex">
            <div
              class="bg-pong-green"
              style="width: ${winPct}%; transition: width 0.3s ease;"
            ></div>
            <div
              class="bg-red-500"
              style="width: ${lossPct}%; transition: width 0.3s ease;"
            ></div>
          </div>
          <div class="flex justify-between mt-2 text-xs text-gray-400">
            <span>Wins: ${gamesWon} (${winPct.toFixed(0)}%)</span>
            <span>Losses: ${gamesLost} (${lossPct.toFixed(0)}%)</span>
          </div>
        `;
			}
		}

		const container = document.getElementById('recent-matches');
		if (!container) return;

		const games = await this.gameService.getMyGames();
		if (!games.length) {
			container.innerHTML = `
        <div class="text-center py-8 text-gray-400">
          <p data-i18n-key="stats.recent.empty.title">No match history yet</p>
          <p class="text-sm" data-i18n-key="stats.recent.empty.subtitle">
            Play some games to see your stats!
          </p>
        </div>
      `;
			return;
		}

		const getTime = (g: any): number => {
			const raw = g.created_at || g.createdAt || g.date;
			if (!raw) return 0;
			const d = new Date(String(raw).replace(' ', 'T'));
			return isNaN(d.getTime()) ? 0 : d.getTime();
		};

		const sorted = [...games].sort((a, b) => getTime(b) - getTime(a));

		const recent = sorted.slice(0, 5);

		container.innerHTML = recent
			.map((g: any) => {
				let p1 = 0;
				let p2 = 0;

				if (typeof g.score === 'string') {
					try {
						const parsed = JSON.parse(g.score);
						p1 = Number(parsed.player1 ?? 0);
						p2 = Number(parsed.player2 ?? 0);
					} catch {
					}
				} else if (typeof g.score === 'object' && g.score !== null) {
					p1 = Number(g.score.player1 ?? 0);
					p2 = Number(g.score.player2 ?? 0);
				}

				let resultLabel = 'Draw';
				let resultClass = 'text-gray-300';
				if (p1 > p2) { resultLabel = 'Win'; resultClass = 'text-pong-green'; }
				else if (p1 < p2) { resultLabel = 'Loss'; resultClass = 'text-red-400'; }

				const mode = g.mode || 'pvp';

				const rawDate = g.created_at || g.createdAt || g.date;
				let dateLabel = '';
				if (rawDate) {
					const d = new Date(String(rawDate).replace(' ', 'T'));
					dateLabel = isNaN(d.getTime()) ? rawDate : d.toLocaleString();
				}

				return `
          <div class="flex justify-between items-center p-3 bg-gray-800 rounded">
            <div>
              <div class="font-semibold">
                Mode: ${this.escapeHtml(String(mode))}
              </div>
              <div class="text-sm text-gray-400">
                ${this.escapeHtml(dateLabel)}
              </div>
            </div>
            <div class="text-right">
              <div class="font-bold ${resultClass}">
                ${resultLabel}
              </div>
              <div class="text-sm text-gray-400">
                ${p1} - ${p2}
              </div>
            </div>
          </div>
        `;
			})
			.join('');

	}




	private initializeSettingsPage(): void {
		this.updateSettingsUI();
		this.setupSettingsListeners();
		this.updatePreview();
	}

	private updateSettingsUI(): void {
		const settings = this.settingsService.getSettings();

		const sliders = [
			{ id: 'ball-speed', key: 'ballSpeed' as const },
			{ id: 'ball-size', key: 'ballSize' as const },
			{ id: 'player-speed', key: 'playerSpeed' as const },
			{ id: 'player-size', key: 'playerSize' as const },
			{ id: 'win-score', key: 'winScore' as const },
		];

		sliders.forEach(({ id, key }) => {
			const slider = document.getElementById(id) as HTMLInputElement;
			const value = document.getElementById(`${id}-value`);
			if (slider) slider.value = settings[key].toString();
			if (value) value.textContent = settings[key].toString();
		});

		this.updatePreview();
	}

	private setupSettingsListeners(): void {
		const sliders = ['ball-speed', 'ball-size', 'player-speed', 'player-size', 'win-score'];

		sliders.forEach((id) => {
			const slider = document.getElementById(id) as HTMLInputElement;
			const valueDisplay = document.getElementById(`${id}-value`);

			if (slider && valueDisplay) {
				slider.addEventListener('input', (e) => {
					const value = (e.target as HTMLInputElement).value;
					valueDisplay.textContent = value;

					const key = this.getSettingKey(id);
					if (key) {
						this.settingsService.updateSetting(
							key,
							id === 'win-score' ? parseInt(value) : parseFloat(value)
						);
						this.updatePreview();
					}
				});
			}
		});
	}

	private getSettingKey(sliderId: string): keyof import('./types').GameSettings | null {
		const mapping: Record<string, keyof import('./types').GameSettings> = {
			'ball-speed': 'ballSpeed',
			'ball-size': 'ballSize',
			'player-speed': 'playerSpeed',
			'player-size': 'playerSize',
			'win-score': 'winScore',
		};
		return mapping[sliderId] || null;
	}

	private updatePreview(): void {
		const settings = this.settingsService.getSettings();

		const previewBoardHeight = 200;

		const ball = document.getElementById('preview-ball');
		const player1 = document.getElementById('preview-player1');
		const player2 = document.getElementById('preview-player2');

		if (ball) {
			const baseBallSize = 16;
			const ballSizePx = baseBallSize * (settings.ballSize / 2.0);
			ball.style.width = ballSizePx + 'px';
			ball.style.height = ballSizePx + 'px';

			ball.style.animation = 'none';
			setTimeout(() => {
				if (ball) {
					const duration = Math.max(0.5, 2.5 - settings.ballSpeed);
					ball.style.animation = `ballPreview ${duration}s ease-in-out infinite alternate`;
				}
			}, 10);
		}

		if (player1 && player2) {
			const playerHeight = (settings.playerSize / 100) * previewBoardHeight;
			const playerWidth = 12;

			[player1, player2].forEach((player) => {
				player.style.height = playerHeight + 'px';
				player.style.width = playerWidth + 'px';
			});

			const speed = settings.playerSpeed;
			[player1, player2].forEach((player) => {
				(player as HTMLElement).style.animation = 'none';
				setTimeout(() => {
					if (player) {
						const duration = Math.max(0.8, 2.5 - speed);
						(player as HTMLElement).style.animation = `playerPreview ${duration}s ease-in-out infinite alternate`;
					}
				}, 10);
			});
		}
	}

	private escapeHtml(text: string): string {
		const div = document.createElement('div');
		div.textContent = text;
		return div.innerHTML;
	}

	private async initialize(): Promise<void> {
		const params = new URLSearchParams(window.location.search);
		const oauthToken = params.get('oauthToken');

		if (oauthToken) {
			await this.authService.handleOAuthCallback(oauthToken);

			const cleanUrl = window.location.origin + window.location.pathname + window.location.hash;
			window.history.replaceState({}, '', cleanUrl);
		} else {
			await this.authService.refreshCurrentUser?.();
		}

		const user = this.authService.getCurrentUser?.();
		if (user && (user as any).language) {
			this.i18nService.setLanguage((user as any).language as 'en' | 'fr' | 'es');
		}

		const authForm = document.getElementById('auth-form');
		if (authForm) {
			authForm.addEventListener('submit', (e) => this.handleAuthSubmit(e));
		}

		await this.router.init();

		this.updateNavButtonsAuthState();
		this.updateHomePageAuthState();
	}


	private async handleAvatarUpload(e: Event): Promise<void> {
		const input = e.target as HTMLInputElement;
		const file = input.files?.[0];
		if (!file) return;

		const reader = new FileReader();
		reader.onload = (event) => {
			const preview = document.getElementById('profile-avatar-preview');
			if (preview && event.target?.result) {
				(preview as HTMLElement).style.backgroundImage = `url(${event.target.result})`;
				(preview as HTMLElement).style.backgroundSize = 'cover';
				(preview as HTMLElement).style.backgroundPosition = 'center';
				const span = preview.querySelector('span') as HTMLElement;
				if (span) span.style.display = 'none';
			}
		};
		reader.readAsDataURL(file);

		const url = await this.authService.uploadAvatar(file);
		if (!url) {
			alert('Could not upload avatar');
		}
	}


	private async handleProfileSubmit(e?: Event): Promise<void> {
		e?.preventDefault();

		const usernameInput = document.getElementById('profile-username') as HTMLInputElement;
		const emailInput = document.getElementById('profile-email') as HTMLInputElement;

		const newUsername = usernameInput?.value?.trim();
		const newEmail = emailInput?.value?.trim();

		const ok = await this.authService.updateProfile({
			username: newUsername,
			email: newEmail,
		});

		if (ok) {
			this.closeProfileModal();
			this.updateHomePageAuthState();
			this.updateNavButtonsAuthState();
		}
	}


	private async handlePasswordSubmit(e?: Event): Promise<void> {
		e?.preventDefault();

		const currentPasswordInput = document.getElementById('profile-current-password') as HTMLInputElement;
		const newPasswordInput = document.getElementById('profile-new-password') as HTMLInputElement;
		const confirmPasswordInput = document.getElementById('profile-confirm-password') as HTMLInputElement;

		const currentPassword = currentPasswordInput?.value?.trim();
		const newPassword = newPasswordInput?.value?.trim();
		const confirmPassword = confirmPasswordInput?.value?.trim();

		if (!currentPassword || !newPassword || !confirmPassword) {
			alert('Please fill in all fields!');
			return;
		}

		if (newPassword !== confirmPassword) {
			alert('New passwords do not match!');
			return;
		}

		const ok = await this.authService.changePassword({
			currentPassword,
			newPassword,
		});

		if (ok) {
			this.showMainProfileView();
			currentPasswordInput.value = '';
			newPasswordInput.value = '';
			confirmPasswordInput.value = '';
		}
	}

	private async handleCreateTournamentConfirm(): Promise<void> {
		if (!this.authService.isAuthenticated()) {
			this.showLoginModal();
			return;
		}

		const nameInput = document.getElementById('tournament-name') as HTMLInputElement | null;
		const p1Input = document.getElementById('tournament-player-1') as HTMLInputElement | null;
		const p2Input = document.getElementById('tournament-player-2') as HTMLInputElement | null;
		const p3Input = document.getElementById('tournament-player-3') as HTMLInputElement | null;
		const p4Input = document.getElementById('tournament-player-4') as HTMLInputElement | null;

		const name = nameInput?.value.trim() || 'Local 4-Player Cup';

		const players = [
			p1Input?.value.trim() || 'Player 1',
			p2Input?.value.trim() || 'Player 2',
			p3Input?.value.trim() || 'Player 3',
			p4Input?.value.trim() || 'Player 4',
		];

		this.pendingTournament = { name, players };

		this.closeTournamentModal();
		this.showTournamentSettingsModal();
	}

	private showTournamentSettingsModal(): void {
		const modal = document.getElementById('tournament-settings-modal');
		if (!modal) return;

		modal.classList.remove('hidden');
		this.initializeTournamentSettingsUI();
	}

	private closeTournamentSettingsModal(): void {
		const modal = document.getElementById('tournament-settings-modal');
		if (modal) modal.classList.add('hidden');
	}

	private initializeTournamentSettingsUI(): void {
		const settings = this.settingsService.getSettings();

		type Key = keyof import('./types').GameSettings;

		const sliders: { id: string; valueId: string; key: Key }[] = [
			{ id: 'tournament-ball-speed', valueId: 'tournament-ball-speed-value', key: 'ballSpeed' },
			{ id: 'tournament-ball-size', valueId: 'tournament-ball-size-value', key: 'ballSize' },
			{ id: 'tournament-player-speed', valueId: 'tournament-player-speed-value', key: 'playerSpeed' },
			{ id: 'tournament-player-size', valueId: 'tournament-player-size-value', key: 'playerSize' },
			{ id: 'tournament-win-score', valueId: 'tournament-win-score-value', key: 'winScore' },
		];

		sliders.forEach(({ id, valueId, key }) => {
			const slider = document.getElementById(id) as HTMLInputElement | null;
			const valueLabel = document.getElementById(valueId);

			if (!slider || !valueLabel) return;

			slider.value = String(settings[key]);
			valueLabel.textContent = String(settings[key]);

			if (!slider.dataset.bound) {
				slider.addEventListener('input', (e) => {
					const valStr = (e.target as HTMLInputElement).value;
					valueLabel.textContent = valStr;

					const numericValue =
						key === 'winScore' ? parseInt(valStr, 10) : parseFloat(valStr);

					this.settingsService.updateSetting(key, numericValue as any);
				});

				slider.dataset.bound = 'true';
			}
		});
	}


	private showTournamentResultModal(matchId: string): void {
		const modal = document.getElementById('tournament-result-modal');
		const playersText = document.getElementById('tournament-result-players');

		const score1Input = document.getElementById('tournament-score-1') as HTMLInputElement | null;
		const score2Input = document.getElementById('tournament-score-2') as HTMLInputElement | null;

		const t = this.tournamentService.getLocalTournament();
		if (!modal || !playersText || !t) return;

		const match = t.matches.find((m) => m.id === matchId);
		if (!match || !match.player1 || !match.player2) return;

		playersText.textContent = `${match.player1.name} vs ${match.player2.name}`;
		if (score1Input) score1Input.value = match.score1 != null ? String(match.score1) : '';
		if (score2Input) score2Input.value = match.score2 != null ? String(match.score2) : '';

		(modal as HTMLElement).dataset.matchId = matchId;

		modal.classList.remove('hidden');
	}

	private closeTournamentResultModal(): void {
		const modal = document.getElementById('tournament-result-modal');
		if (modal) modal.classList.add('hidden');
	}

	private async handleConfirmTournamentResult(): Promise<void> {
		const modal = document.getElementById('tournament-result-modal') as HTMLElement | null;
		if (!modal) return;

		const matchId = modal.dataset.matchId;
		if (!matchId) return;

		const score1Input = document.getElementById('tournament-score-1') as HTMLInputElement | null;
		const score2Input = document.getElementById('tournament-score-2') as HTMLInputElement | null;

		const s1 = Number(score1Input?.value ?? NaN);
		const s2 = Number(score2Input?.value ?? NaN);

		if (!Number.isFinite(s1) || !Number.isFinite(s2)) {
			alert('Please enter valid scores');
			return;
		}

		const updated = this.tournamentService.updateLocalMatchScore(matchId, s1, s2);
		if (!updated) return;

		this.closeTournamentResultModal();

		if (this.tournamentPage) {
			this.tournamentPage.refreshFromService();
		}
	}

	private async loadTournamentFromBackend(tournamentId: string): Promise<void> {
		const record = this.tournamentService.getUserTournamentById(tournamentId);
		if (!record) return;

		this.tournamentService.hydrateLocalFromBackendRecord(record);

		if (this.tournamentPage) {
			this.tournamentPage.refreshFromService();
			this.tournamentPage.renderUserTournaments(
				this.tournamentService.getUserTournaments(),
				tournamentId
			);
		}
	}

}

document.addEventListener('DOMContentLoaded', () => {
	new App();
});


