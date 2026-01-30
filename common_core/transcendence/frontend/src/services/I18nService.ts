
type Language = 'en' | 'fr' | 'es';

type Translations = Record<string, string>;

export class I18nService {
	private static instance: I18nService;
	private currentLang: Language = 'en';
	private readonly STORAGE_KEY = 'gpoat_language';

	private translations: Record<Language, Translations> = {
		en: {
			'nav.brand': '🏓 GPOAT',
			'nav.home': 'Home',
			'nav.play': 'Play',
			'nav.tournaments': 'Tournaments',
			'nav.stats': 'Stats',
			'auth.login': 'Login',
			'auth.register': 'Register',
			'auth.or': 'or',
			'auth.github': 'Continue with GitHub',
			'auth.username': 'Username',
			'auth.password': 'Password',
			'auth.email': 'Email',
			'profile.edit': 'Edit Profile',
			'friendlist.title': 'Friendlist',
			'notifications.title': 'Notifications',
			'notifications.empty': 'No notifications',
			'accessibility.highContrastOn': 'High contrast',
			'accessibility.fontPlus': 'A+',
			'accessibility.fontMinus': 'A-',
			'home.title': 'Welcome to Pong Arena!',
			'home.subtitle': 'Challenge your friends, participate in tournaments, and grind!',

			'home.pvp.title': 'Player vs Player',
			'home.pvp.description': 'Challenge a friend in real-time',
			'home.pvp.button': 'Play Now',

			'home.ai.title': 'Player vs AI',
			'home.ai.description': 'Challenge the artificial intelligence',
			'home.ai.button': 'Play Against AI',

			'home.tournament.title': 'Tournament',
			'home.tournament.description': 'Participate in competitions',
			'home.tournament.button': 'View Tournaments',

			'home.chat.title': 'Chat',
			'home.chat.description': 'Discuss with the community',
			'home.chat.button': 'Open Chat',

			'home.stats.title': 'Stats',
			'home.stats.description': 'Check your performance',
			'home.stats.button': 'View My Stats',
			'game.player1': 'User',
			'game.player2': 'Guest',

			'game.paused': 'Game Paused',
			'game.resume': 'Resume (ESC)',
			'game.restart': 'Restart',
			'game.exit': 'Exit to Menu',

			'game.winnerText': 'Player 1 Wins!',
			'game.finalScore': 'Final Score:',
			'game.playAgain': 'Play Again',
			'game.backToMenu': 'Back to Menu',

			'game.controls': 'Player 1: W/S keys | Player 2: Arrow Up/Down keys',
			'game.pauseHint': 'Press ESC to pause',
			'settings.title': '⚙️ Game Settings',
			'settings.presets.title': 'Presets',
			'settings.presets.casual': 'Casual',
			'settings.presets.balanced': 'Balanced',
			'settings.presets.competitive': 'Competitive',
			'settings.presets.chaos': 'Chaos',

			'settings.custom.title': 'Custom Settings',
			'settings.ballSpeed.label': 'Ball Speed',
			'settings.ballSize.label': 'Ball Size',
			'settings.playerSpeed.label': 'Player Speed',
			'settings.playerSize.label': 'Player Size',
			'settings.winScore.label': 'Win Score',

			'settings.play': '🎮 Play the Game',

			'settings.preview.title': 'Preview',
			'settings.preview.tip1': '• Adjust settings to see preview changes',
			'settings.preview.tip2': '• Choose a preset for quick setup',
			'settings.preview.tip3': '• Settings are saved per user',
			'stats.title': '📊 Your Statistics',

			'stats.overview.gamesPlayed': 'Games Played',
			'stats.overview.gamesWon': 'Games Won',
			'stats.overview.winRate': 'Win Rate',
			'stats.overview.highestScore': 'Highest Score',

			'stats.recent.title': 'Recent Matches',
			'stats.recent.example.opponent': 'vs Player2',
			'stats.recent.example.time': '2 hours ago',
			'stats.recent.example.result': 'Win',
			'stats.recent.example.score': '7 - 5',
			'stats.recent.empty.title': 'No match history yet',
			'stats.recent.empty.subtitle': 'Play some games to see your stats!',

			'stats.achievements.title': 'Achievements',
			'stats.achievements.firstVictory.title': 'First Victory',
			'stats.achievements.firstVictory.desc': 'Win your first game',
			'stats.achievements.streak.title': 'Winning Streak',
			'stats.achievements.streak.desc': 'Win 5 games in a row',
			'stats.achievements.tournament.title': 'Tournament Winner',
			'stats.achievements.tournament.desc': 'Win a tournament',
			'tournaments.title': '🏆 Tournaments',
			'tournaments.create.button': 'Create Tournament',

			'tournaments.card.sample.title': 'Championship 2025',
			'tournaments.card.status.active': 'Active',
			'tournaments.card.participants.label': 'Participants:',
			'tournaments.card.status.label': 'Status:',
			'tournaments.card.status.registrationOpen': 'Registration Open',
			'tournaments.card.join': 'Join Tournament',

			'tournaments.empty.title': 'No tournaments available',
			'tournaments.empty.subtitle': 'Be the first to create one!',

			'tournaments.modal.title': 'Create Tournament',
			'tournaments.modal.namePlaceholder': 'Tournament Name',
			'tournaments.modal.option4': '4 Players',
			'tournaments.modal.option8': '8 Players',
			'tournaments.modal.option16': '16 Players',
			'tournaments.modal.create': 'Create',
			'tournament.page.title': 'Tournaments',
			'tournament.page.subtitle': 'Local 4-player bracket. Create a cup and play match by match.',
			'tournament.page.createButton': '+ Create 4-player tournament',

			'tournament.local.empty': 'No local tournament yet.',
			'tournament.local.empty.highlight': 'Click on "Create 4-player tournament" to start.',

			'tournament.status.label': 'Status:',
			'tournament.status.notStarted': 'Not started',
			'tournament.status.inProgress': 'In progress',
			'tournament.status.finished': 'Finished',

			'tournament.bracket.title': 'Bracket',
			'tournament.bracket.semifinals': 'Semi-finals',
			'tournament.bracket.finalTitle': 'Final',
			'tournament.bracket.semi1': 'Semi-final 1',
			'tournament.bracket.semi2': 'Semi-final 2',
			'tournament.bracket.final': 'Final',
			'tournament.bracket.playMatch': 'Play match',
			'tournament.bracket.winner': 'Winner:',

			'tournament.winner.title': 'Winner',
			'tournament.winner.championOf': 'Champion of',
			'tournament.winner.unknown': 'Unknown',
			'tournament.winner.newTournamentButton': 'Start a new tournament',

			'tournament.next.title': 'Next match',
			'tournament.next.noMatch': 'All matches are already set.',
			'tournament.next.roundLabel': 'Round:',
			'tournament.next.round.final': 'Final',
			'tournament.next.round.semi': 'Semi-final',
			'tournament.next.seed': 'Seed',
			'tournament.next.playButton': 'Play this match',
			'tournament.next.help':
				'This will launch a local Pong game with these 2 nicknames. When the game ends, the score is stored in the bracket and the next match becomes available.',

			'tournament.userTournaments.empty': 'No ongoing tournaments. Create one to start playing.',
			'tournament.userTournaments.players': 'Players:',

			'settings.aiDifficulty.label': 'AI Difficulty',
			'settings.aiDifficulty.easy': 'Easy',
			'settings.aiDifficulty.medium': 'Medium',
			'settings.aiDifficulty.hard': 'Hard',
			'settings.aiDifficulty.expert': 'Expert',


		},
		fr: {
			'nav.brand': '🏓 GPOAT',
			'nav.home': 'Accueil',
			'nav.play': 'Jouer',
			'nav.tournaments': 'Tournois',
			'nav.stats': 'Stats',
			'auth.login': 'Connexion',
			'auth.register': 'Inscription',
			'auth.or': 'ou',
			'auth.github': 'Continuer avec GitHub',
			'auth.username': "Nom d'utilisateur",
			'auth.password': 'Mot de passe',
			'auth.email': 'Email',
			'profile.edit': 'Modifier le profil',
			'friendlist.title': 'Liste d’amis',
			'notifications.title': 'Notifications',
			'notifications.empty': 'Aucune notification',
			'accessibility.highContrastOn': 'Contraste élevé',
			'accessibility.fontPlus': 'A+',
			'accessibility.fontMinus': 'A-',
			'home.title': 'Bienvenue sur Pong Arena !',
			'home.subtitle': 'Défiez vos amis, participez à des tournois et progressez !',

			'home.pvp.title': 'Joueur vs Joueur',
			'home.pvp.description': 'Défiez un ami en temps réel',
			'home.pvp.button': 'Jouer maintenant',

			'home.ai.title': 'Joueur vs IA',
			'home.ai.description': 'Affrontez l’intelligence artificielle',
			'home.ai.button': 'Jouer contre l’IA',

			'home.tournament.title': 'Tournoi',
			'home.tournament.description': 'Participez à des compétitions',
			'home.tournament.button': 'Voir les tournois',

			'home.chat.title': 'Chat',
			'home.chat.description': 'Discutez avec la communauté',
			'home.chat.button': 'Ouvrir le chat',

			'home.stats.title': 'Statistiques',
			'home.stats.description': 'Consultez vos performances',
			'home.stats.button': 'Voir mes statistiques',
			'game.player1': 'Utilisateur',
			'game.player2': 'Invité',

			'game.paused': 'Jeu en pause',
			'game.resume': 'Reprendre (ESC)',
			'game.restart': 'Recommencer',
			'game.exit': 'Retour au menu',

			'game.winnerText': 'Le joueur 1 a gagné !',
			'game.finalScore': 'Score final :',
			'game.playAgain': 'Rejouer',
			'game.backToMenu': 'Retour au menu',

			'game.controls': 'Joueur 1 : touches W/S | Joueur 2 : flèches Haut/Bas',
			'game.pauseHint': 'Appuyez sur ESC pour mettre en pause',
			'settings.title': '⚙️ Paramètres du jeu',

			'settings.presets.title': 'Préréglages',
			'settings.presets.casual': 'Détente',
			'settings.presets.balanced': 'Équilibré',
			'settings.presets.competitive': 'Compétitif',
			'settings.presets.chaos': 'Chaos',

			'settings.custom.title': 'Paramètres personnalisés',
			'settings.ballSpeed.label': 'Vitesse de la balle',
			'settings.ballSize.label': 'Taille de la balle',
			'settings.playerSpeed.label': 'Vitesse du joueur',
			'settings.playerSize.label': 'Taille du joueur',
			'settings.winScore.label': 'Score de victoire',

			'settings.play': '🎮 Lancer la partie',

			'settings.preview.title': 'Aperçu',
			'settings.preview.tip1': '• Ajustez les paramètres pour voir les changements',
			'settings.preview.tip2': '• Choisissez un préréglage pour une configuration rapide',
			'settings.preview.tip3': '• Les paramètres sont enregistrés par utilisateur',
			'stats.title': '📊 Vos statistiques',

			'stats.overview.gamesPlayed': 'Parties jouées',
			'stats.overview.gamesWon': 'Parties gagnées',
			'stats.overview.winRate': 'Taux de victoire',
			'stats.overview.highestScore': 'Meilleur score',

			'stats.recent.title': 'Matchs récents',
			'stats.recent.example.opponent': 'vs Joueur2',
			'stats.recent.example.time': 'Il y a 2 heures',
			'stats.recent.example.result': 'Victoire',
			'stats.recent.example.score': '7 - 5',
			'stats.recent.empty.title': "Aucun historique de matchs pour l'instant",
			'stats.recent.empty.subtitle': 'Jouez quelques parties pour voir vos statistiques !',

			'stats.achievements.title': 'Succès',
			'stats.achievements.firstVictory.title': 'Première victoire',
			'stats.achievements.firstVictory.desc': 'Gagnez votre première partie',
			'stats.achievements.streak.title': 'Série de victoires',
			'stats.achievements.streak.desc': 'Gagnez 5 parties d’affilée',
			'stats.achievements.tournament.title': 'Vainqueur de tournoi',
			'stats.achievements.tournament.desc': 'Gagnez un tournoi',
			'tournaments.title': '🏆 Tournois',
			'tournaments.create.button': 'Créer un tournoi',

			'tournaments.card.sample.title': 'Championnat 2025',
			'tournaments.card.status.active': 'Actif',
			'tournaments.card.participants.label': 'Participants :',
			'tournaments.card.status.label': 'Statut :',
			'tournaments.card.status.registrationOpen': 'Inscriptions ouvertes',
			'tournaments.card.join': 'Rejoindre le tournoi',

			'tournaments.empty.title': 'Aucun tournoi disponible',
			'tournaments.empty.subtitle': 'Soyez le premier à en créer un !',

			'tournaments.modal.title': 'Créer un tournoi',
			'tournaments.modal.namePlaceholder': 'Nom du tournoi',
			'tournaments.modal.option4': '4 joueurs',
			'tournaments.modal.option8': '8 joueurs',
			'tournaments.modal.option16': '16 joueurs',
			'tournaments.modal.create': 'Créer',
			'tournament.page.title': 'Tournois',
			'tournament.page.subtitle': 'Tableau local à 4 joueurs. Crée une coupe et joue match après match.',
			'tournament.page.createButton': '＋ Créer un tournoi à 4 joueurs',

			'tournament.local.empty': 'Aucun tournoi local pour le moment.',
			'tournament.local.empty.highlight': 'Clique sur « Créer un tournoi à 4 joueurs » pour commencer.',

			'tournament.status.label': 'Statut :',
			'tournament.status.notStarted': 'Non commencé',
			'tournament.status.inProgress': 'En cours',
			'tournament.status.finished': 'Terminé',

			'tournament.bracket.title': 'Arbre',
			'tournament.bracket.semifinals': 'Demi-finales',
			'tournament.bracket.finalTitle': 'Finale',
			'tournament.bracket.semi1': 'Demi-finale 1',
			'tournament.bracket.semi2': 'Demi-finale 2',
			'tournament.bracket.final': 'Finale',
			'tournament.bracket.playMatch': 'Jouer le match',
			'tournament.bracket.winner': 'Vainqueur :',

			'tournament.winner.title': 'Vainqueur',
			'tournament.winner.championOf': 'Champion de',
			'tournament.winner.unknown': 'Inconnu',
			'tournament.winner.newTournamentButton': 'Lancer un nouveau tournoi',

			'tournament.next.title': 'Prochain match',
			'tournament.next.noMatch': 'Tous les matchs sont déjà définis.',
			'tournament.next.roundLabel': 'Manche :',
			'tournament.next.round.final': 'Finale',
			'tournament.next.round.semi': 'Demi-finale',
			'tournament.next.seed': 'Tête de série',
			'tournament.next.playButton': 'Jouer ce match',
			'tournament.next.help':
				'Cela lancera une partie de Pong locale avec ces 2 pseudos. À la fin de la partie, le score est enregistré dans le tableau et le match suivant devient disponible.',

			'tournament.userTournaments.empty': 'Aucun tournoi en cours. Crée-en un pour commencer à jouer.',
			'tournament.userTournaments.players': 'Joueurs :',

			'settings.aiDifficulty.label': 'Difficulté de l’IA',
			'settings.aiDifficulty.easy': 'Facile',
			'settings.aiDifficulty.medium': 'Moyenne',
			'settings.aiDifficulty.hard': 'Difficile',
			'settings.aiDifficulty.expert': 'Expert',


		},
		es: {
			'nav.brand': '🏓 GPOAT',
			'nav.home': 'Inicio',
			'nav.play': 'Jugar',
			'nav.tournaments': 'Torneos',
			'nav.stats': 'Estadísticas',
			'auth.login': 'Iniciar sesión',
			'auth.register': 'Registrarse',
			'auth.or': 'o',
			'auth.github': 'Continuar con GitHub',
			'auth.username': 'Usuario',
			'auth.password': 'Contraseña',
			'auth.email': 'Correo',
			'profile.edit': 'Editar perfil',
			'friendlist.title': 'Lista de amigos',
			'notifications.title': 'Notificaciones',
			'notifications.empty': 'Sin notificaciones',
			'accessibility.highContrastOn': 'Alto contraste',
			'accessibility.fontPlus': 'A+',
			'accessibility.fontMinus': 'A-',
			'home.title': '¡Bienvenido a Pong Arena!',
			'home.subtitle': '¡Desafía a tus amigos, participa en torneos y mejora tu nivel!',

			'home.pvp.title': 'Jugador vs Jugador',
			'home.pvp.description': 'Desafía a un amigo en tiempo real',
			'home.pvp.button': 'Jugar ahora',

			'home.ai.title': 'Jugador vs IA',
			'home.ai.description': 'Desafía a la inteligencia artificial',
			'home.ai.button': 'Jugar contra IA',

			'home.tournament.title': 'Torneo',
			'home.tournament.description': 'Participa en competiciones',
			'home.tournament.button': 'Ver torneos',

			'home.chat.title': 'Chat',
			'home.chat.description': 'Habla con la comunidad',
			'home.chat.button': 'Abrir chat',

			'home.stats.title': 'Estadísticas',
			'home.stats.description': 'Consulta tu rendimiento',
			'home.stats.button': 'Ver mis estadísticas',
			'game.player1': 'Usuario',
			'game.player2': 'Invitado',

			'game.paused': 'Juego en pausa',
			'game.resume': 'Reanudar (ESC)',
			'game.restart': 'Reiniciar',
			'game.exit': 'Volver al menú',

			'game.winnerText': '¡Jugador 1 gana!',
			'game.finalScore': 'Puntuación final:',
			'game.playAgain': 'Jugar otra vez',
			'game.backToMenu': 'Volver al menú',

			'game.controls': 'Jugador 1: teclas W/S | Jugador 2: flechas Arriba/Abajo',
			'game.pauseHint': 'Pulsa ESC para pausar',
			'settings.title': '⚙️ Ajustes del juego',

			'settings.presets.title': 'Preajustes',
			'settings.presets.casual': 'Casual',
			'settings.presets.balanced': 'Equilibrado',
			'settings.presets.competitive': 'Competitivo',
			'settings.presets.chaos': 'Caos',

			'settings.custom.title': 'Ajustes personalizados',
			'settings.ballSpeed.label': 'Velocidad de la pelota',
			'settings.ballSize.label': 'Tamaño de la pelota',
			'settings.playerSpeed.label': 'Velocidad del jugador',
			'settings.playerSize.label': 'Tamaño del jugador',
			'settings.winScore.label': 'Puntuación para ganar',

			'settings.play': '🎮 Empezar partida',

			'settings.preview.title': 'Vista previa',
			'settings.preview.tip1': '• Ajusta los parámetros para ver los cambios',
			'settings.preview.tip2': '• Elige un preajuste para una configuración rápida',
			'settings.preview.tip3': '• Los ajustes se guardan por usuario',
			'stats.title': '📊 Tus estadísticas',

			'stats.overview.gamesPlayed': 'Partidas jugadas',
			'stats.overview.gamesWon': 'Partidas ganadas',
			'stats.overview.winRate': 'Porcentaje de victoria',
			'stats.overview.highestScore': 'Puntuación más alta',

			'stats.recent.title': 'Partidas recientes',
			'stats.recent.example.opponent': 'vs Jugador2',
			'stats.recent.example.time': 'Hace 2 horas',
			'stats.recent.example.result': 'Victoria',
			'stats.recent.example.score': '7 - 5',
			'stats.recent.empty.title': 'Aún no hay historial de partidas',
			'stats.recent.empty.subtitle': '¡Juega algunas partidas para ver tus estadísticas!',

			'stats.achievements.title': 'Logros',
			'stats.achievements.firstVictory.title': 'Primera victoria',
			'stats.achievements.firstVictory.desc': 'Gana tu primera partida',
			'stats.achievements.streak.title': 'Racha de victorias',
			'stats.achievements.streak.desc': 'Gana 5 partidas seguidas',
			'stats.achievements.tournament.title': 'Campeón de torneo',
			'stats.achievements.tournament.desc': 'Gana un torneo',
			'tournaments.title': '🏆 Torneos',
			'tournaments.create.button': 'Crear torneo',

			'tournaments.card.sample.title': 'Campeonato 2025',
			'tournaments.card.status.active': 'Activo',
			'tournaments.card.participants.label': 'Participantes:',
			'tournaments.card.status.label': 'Estado:',
			'tournaments.card.status.registrationOpen': 'Inscripción abierta',
			'tournaments.card.join': 'Unirse al torneo',

			'tournaments.empty.title': 'No hay torneos disponibles',
			'tournaments.empty.subtitle': '¡Sé el primero en crear uno!',

			'tournaments.modal.title': 'Crear torneo',
			'tournaments.modal.namePlaceholder': 'Nombre del torneo',
			'tournaments.modal.option4': '4 jugadores',
			'tournaments.modal.option8': '8 jugadores',
			'tournaments.modal.option16': '16 jugadores',
			'tournaments.modal.create': 'Crear',
			'tournament.page.title': 'Torneos',
			'tournament.page.subtitle': 'Cuadro local de 4 jugadores. Crea una copa y juega partido a partido.',
			'tournament.page.createButton': '+ Crear torneo de 4 jugadores',

			'tournament.local.empty': 'Todavía no hay ningún torneo local.',
			'tournament.local.empty.highlight': 'Haz clic en «Crear torneo de 4 jugadores» para empezar.',

			'tournament.status.label': 'Estado:',
			'tournament.status.notStarted': 'No iniciado',
			'tournament.status.inProgress': 'En curso',
			'tournament.status.finished': 'Terminado',

			'tournament.bracket.title': 'Cuadro',
			'tournament.bracket.semifinals': 'Semifinales',
			'tournament.bracket.finalTitle': 'Final',
			'tournament.bracket.semi1': 'Semifinal 1',
			'tournament.bracket.semi2': 'Semifinal 2',
			'tournament.bracket.final': 'Final',
			'tournament.bracket.playMatch': 'Jugar partido',
			'tournament.bracket.winner': 'Ganador:',

			'tournament.winner.title': 'Ganador',
			'tournament.winner.championOf': 'Campeón de',
			'tournament.winner.unknown': 'Desconocido',
			'tournament.winner.newTournamentButton': 'Empezar un nuevo torneo',

			'tournament.next.title': 'Próximo partido',
			'tournament.next.noMatch': 'Todos los partidos ya están definidos.',
			'tournament.next.roundLabel': 'Ronda:',
			'tournament.next.round.final': 'Final',
			'tournament.next.round.semi': 'Semifinal',
			'tournament.next.seed': 'Cabeza de serie',
			'tournament.next.playButton': 'Jugar este partido',
			'tournament.next.help':
				'Esto iniciará una partida local de Pong con estos 2 apodos. Cuando termine la partida, la puntuación se guarda en el cuadro y el siguiente partido se desbloquea.',

			'tournament.userTournaments.empty': 'No hay torneos en curso. Crea uno para empezar a jugar.',
			'tournament.userTournaments.players': 'Jugadores:',

			'settings.aiDifficulty.label': 'Dificultad de la IA',
			'settings.aiDifficulty.easy': 'Fácil',
			'settings.aiDifficulty.medium': 'Media',
			'settings.aiDifficulty.hard': 'Difícil',
			'settings.aiDifficulty.expert': 'Experto',


		},
	};

	private constructor() { }

	public static getInstance(): I18nService {
		if (!I18nService.instance) {
			I18nService.instance = new I18nService();
		}
		return I18nService.instance;
	}

	public init(): void {
		const stored = localStorage.getItem(this.STORAGE_KEY) as Language | null;
		if (stored && ['en', 'fr', 'es'].includes(stored)) {
			this.currentLang = stored;
		} else {

			const navLang = navigator.language.slice(0, 2);
			if (['en', 'fr', 'es'].includes(navLang)) {
				this.currentLang = navLang as Language;
			}
		}
		document.documentElement.lang = this.currentLang;
		this.applyTranslations();
	}

	public setLanguage(lang: Language): void {
		if (this.currentLang === lang) return;
		this.currentLang = lang;
		localStorage.setItem(this.STORAGE_KEY, lang);
		document.documentElement.lang = lang;
		this.applyTranslations();
	}

	public getLanguage(): Language {
		return this.currentLang;
	}

	public applyTranslations(root: HTMLElement | Document = document): void {
		const elements = root.querySelectorAll<HTMLElement>('[data-i18n-key]');
		elements.forEach((el) => {
			const key = el.dataset.i18nKey;
			if (!key) return;
			const value = this.translations[this.currentLang][key];
			if (!value) return;

			const attr = el.dataset.i18nAttr;
			if (attr) {
				el.setAttribute(attr, value);
			} else {
				el.textContent = value;
			}
		});
	}
}
