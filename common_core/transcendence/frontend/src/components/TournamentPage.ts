
import {
	TournamentService,
	type LocalTournamentState,
	type LocalTournamentMatch,
} from '../services/TournamentService';

export class TournamentPage {
	private root: HTMLElement | null = null;
	private tournamentService = TournamentService.getInstance();

	mount(): void {
		const main = document.getElementById('main-content');
		if (!main) return;

		main.innerHTML = `
      <section class="max-w-5xl mx-auto px-4 py-8" id="tournament-root">
        <div class="flex items-center justify-between mb-6">
          <div>
            <h1
              class="text-3xl font-bold mb-1"
              data-i18n-key="tournament.page.title"
            >
              Tournaments
            </h1>
            <p
              class="text-sm text-gray-400"
              data-i18n-key="tournament.page.subtitle"
            >
              Local 4-player bracket. Create a cup and play match by match.
            </p>
          </div>
          <button
            data-action="create-tournament"
            class="bg-yellow-500 hover:bg-yellow-400 text-black font-semibold px-4 py-2 rounded-lg shadow transition-colors"
            data-i18n-key="tournament.page.createButton"
          >
            + Create 4-player tournament
          </button>
        </div>

        <!-- 🔥 Liste des tournois en DB -->
        <div id="user-tournaments-list" class="mb-8"></div>

        <!-- 🔥 Contenu du tournoi local -->
        <div id="tournament-content"></div>
      </section>
    `;

		this.root = document.getElementById('tournament-root');
		this.refreshFromService();
	}

	/** Re-rend la page à partir du TournamentService */
	refreshFromService(): void {
		const container = document.getElementById('tournament-content');
		if (!container) return;

		const t = this.tournamentService.getLocalTournament();

		if (!t) {
			container.innerHTML = `
        <div class="border border-dashed border-gray-700 rounded-xl p-8 text-center text-gray-400">
          <p data-i18n-key="tournament.local.empty">
            No local tournament yet.
          </p>
          <p class="mt-2">
            <span
              class="text-yellow-400 font-semibold"
              data-i18n-key="tournament.local.empty.highlight"
            >
              Click on "Create 4-player tournament" to start.
            </span>
          </p>
        </div>
      `;
			return;
		}

		const currentMatch = this.tournamentService.getCurrentLocalMatch();
		const finalMatch = t.matches.find((m) => m.round === 'final') || null;

		container.innerHTML = `
      <div class="bg-black/30 border border-white/10 rounded-2xl p-6 mb-6">
        <div class="flex items-center justify-between mb-2">
          <h2 class="text-2xl font-semibold">${this.escapeHtml(t.name)}</h2>
          <span
            class="text-xs px-2 py-1 rounded-full bg-gray-800 text-gray-300"
          >
            <span
              class="mr-1"
              data-i18n-key="tournament.status.label"
            >
              Status:
            </span>
            ${this.renderStatusBadge(t)}
          </span>
        </div>
        <div class="flex gap-2 flex-wrap text-sm text-gray-400">
          ${t.players
				.map(
					(p) => `
            <span class="px-2 py-1 bg-gray-800 rounded-full">
              #${p.seed} ${this.escapeHtml(p.name)}
            </span>
          `
				)
				.join('')}
        </div>
      </div>

      <div class="grid md:grid-cols-[1.2fr,0.8fr] gap-6 items-start">
        ${this.renderBracket(t)}
        ${this.renderRightPanel(currentMatch, finalMatch, t)}
      </div>
    `;
	}

	private renderStatusBadge(t: LocalTournamentState): string {
		if (t.status === 'not_started') {
			return `
        <span
          class="text-yellow-400"
          data-i18n-key="tournament.status.notStarted"
        >
          Not started
        </span>
      `;
		}
		if (t.status === 'in_progress') {
			return `
        <span
          class="text-pong-green"
          data-i18n-key="tournament.status.inProgress"
        >
          In progress
        </span>
      `;
		}
		return `
      <span
        class="text-blue-400"
        data-i18n-key="tournament.status.finished"
      >
        Finished
      </span>
    `;
	}

	private renderBracket(t: LocalTournamentState): string {
		const semi1 = t.matches.find((m) => m.round === 'semi_final_1')!;
		const semi2 = t.matches.find((m) => m.round === 'semi_final_2')!;
		const final = t.matches.find((m) => m.round === 'final')!;

		const matchCard = (m: LocalTournamentMatch, titleKey: string): string => {
			const p1 = m.player1 ? this.escapeHtml(m.player1.name) : 'TBD';
			const p2 = m.player2 ? this.escapeHtml(m.player2.name) : 'TBD';
			const s1 = m.score1 ?? '-';
			const s2 = m.score2 ?? '-';

			const canPlay = !!m.player1 && !!m.player2 && !m.winnerId;

			let winnerLabel = '';
			if (m.winnerId && m.player1 && m.player2) {
				const winnerName =
					m.winnerId === m.player1.id ? m.player1.name : m.player2.name;
				winnerLabel = `
          <span
            class="text-xs text-pong-green"
            data-i18n-key="tournament.bracket.winner"
          >
            Winner:
          </span>
          <span class="text-xs text-pong-green">
            ${this.escapeHtml(winnerName)}
          </span>
        `;
			}

			return `
        <div class="bg-gray-900/70 border border-gray-700 rounded-xl p-3 mb-3 relative">
          <div class="flex items-center justify-between mb-1">
            <span
              class="text-xs uppercase tracking-wide text-gray-400"
              data-i18n-key="${titleKey}"
            >
              ${titleKey === 'tournament.bracket.semi1'
					? 'Semi-final 1'
					: titleKey === 'tournament.bracket.semi2'
						? 'Semi-final 2'
						: 'Final'}
            </span>
            ${winnerLabel}
          </div>
          <div class="flex items-center justify-between text-sm">
            <div class="flex-1">
              <div class="flex justify-between">
                <span>${p1}</span>
                <span class="font-semibold">${s1}</span>
              </div>
              <div class="flex justify-between">
                <span>${p2}</span>
                <span class="font-semibold">${s2}</span>
              </div>
            </div>
          </div>
          ${canPlay
					? `<button
                  data-action="start-tournament-match"
                  data-match-id="${m.id}"
                  class="mt-2 w-full text-xs bg-pong-blue hover:bg-blue-700 text-white py-1 rounded transition-colors"
                  data-i18n-key="tournament.bracket.playMatch"
                >
                  Play match
                </button>`
					: ''
				}
        </div>
      `;
		};

		return `
      <div class="bg-black/30 border border-white/10 rounded-2xl p-4">
        <h3
          class="text-lg font-semibold mb-3"
          data-i18n-key="tournament.bracket.title"
        >
          Bracket
        </h3>
        <div class="grid md:grid-cols-[1fr,1fr] gap-4">
          <div>
            <h4
              class="text-sm text-gray-400 mb-2"
              data-i18n-key="tournament.bracket.semifinals"
            >
              Semi-finals
            </h4>
            ${matchCard(semi1, 'tournament.bracket.semi1')}
            ${matchCard(semi2, 'tournament.bracket.semi2')}
          </div>
          <div>
            <h4
              class="text-sm text-gray-400 mb-2"
              data-i18n-key="tournament.bracket.finalTitle"
            >
              Final
            </h4>
            ${matchCard(final, 'tournament.bracket.final')}
          </div>
        </div>
      </div>
    `;
	}

	private renderRightPanel(
		currentMatch: LocalTournamentMatch | null,
		finalMatch: LocalTournamentMatch | null,
		t: LocalTournamentState
	): string {
		if (!currentMatch && t.status === 'finished') {
			const winnerId = finalMatch?.winnerId;
			const winner =
				winnerId && t.players.find((p) => p.id === winnerId)?.name;

			return `
        <div class="bg-black/30 border border-yellow-500/40 rounded-2xl p-4">
          <h3
            class="text-lg font-semibold mb-2"
            data-i18n-key="tournament.winner.title"
          >
            Winner
          </h3>
          <p class="text-gray-300 mb-3">
            <span data-i18n-key="tournament.winner.championOf">
              Champion of
            </span>
            <span class="font-semibold">
              ${this.escapeHtml(t.name)}
            </span>
          </p>
          <div class="text-2xl font-bold text-yellow-400 mb-4">
            ${winner
					? this.escapeHtml(winner)
					: `<span data-i18n-key="tournament.winner.unknown">Unknown</span>`
				}
          </div>
          <button
            data-action="create-tournament"
            class="w-full text-sm bg-yellow-500 hover:bg-yellow-400 text-black py-2 rounded-lg font-semibold transition-colors"
            data-i18n-key="tournament.winner.newTournamentButton"
          >
            Start a new tournament
          </button>
        </div>
      `;
		}

		if (!currentMatch) {
			return `
        <div class="bg-black/30 border border-white/10 rounded-2xl p-4">
          <h3
            class="text-lg font-semibold mb-2"
            data-i18n-key="tournament.next.title"
          >
            Next match
          </h3>
          <p
            class="text-gray-400 text-sm"
            data-i18n-key="tournament.next.noMatch"
          >
            All matches are already set.
          </p>
        </div>
      `;
		}

		const p1 = currentMatch.player1!;
		const p2 = currentMatch.player2!;

		return `
      <div class="bg-black/30 border border-pong-green/40 rounded-2xl p-4">
        <h3
          class="text-lg font-semibold mb-2"
          data-i18n-key="tournament.next.title"
        >
          Next match
        </h3>
        <p class="text-sm text-gray-400 mb-3">
          <span data-i18n-key="tournament.next.roundLabel">Round:</span>
          ${currentMatch.round === 'final'
				? `<span data-i18n-key="tournament.next.round.final">Final</span>`
				: `<span data-i18n-key="tournament.next.round.semi">Semi-final</span>`
			}
        </p>
        <div class="mb-4">
          <div class="flex items-center justify-between mb-1">
            <span class="text-gray-300">${this.escapeHtml(p1.name)}</span>
            <span class="text-xs text-gray-500">
              <span data-i18n-key="tournament.next.seed">Seed</span>
              #${p1.seed}
            </span>
          </div>
          <div class="flex items-center justify-between mb-3">
            <span class="text-gray-300">${this.escapeHtml(p2.name)}</span>
            <span class="text-xs text-gray-500">
              <span data-i18n-key="tournament.next.seed">Seed</span>
              #${p2.seed}
            </span>
          </div>
        </div>
        <button
          data-action="start-tournament-match"
          data-match-id="${currentMatch.id}"
          class="w-full bg-pong-green hover:bg-green-700 text-black font-semibold py-2 rounded-lg transition-colors"
          data-i18n-key="tournament.next.playButton"
        >
          Play this match
        </button>
        <p
          class="mt-3 text-xs text-gray-500"
          data-i18n-key="tournament.next.help"
        >
          This will launch a local Pong game with these 2 nicknames. When the game ends,
          the score is stored in the bracket and the next match becomes available.
        </p>
      </div>
    `;
	}

	private escapeHtml(text: string): string {
		const div = document.createElement('div');
		div.textContent = text;
		return div.innerHTML;
	}

	/** Render des tournois persistés en DB pour le user courant */
	renderUserTournaments(tournaments: any[], selectedId?: string | null): void {
		const container = document.getElementById('user-tournaments-list');
		if (!container) return;


		const inProgress = tournaments.filter((t) => t.status === 'in-progress');

		if (!inProgress.length) {
			container.innerHTML = `
        <div class="bg-black/20 border border-dashed border-gray-700 rounded-xl p-4 text-sm text-gray-400">
          <p data-i18n-key="tournament.userTournaments.empty">
            No ongoing tournaments. Create one to start playing.
          </p>
        </div>
      `;
			return;
		}

		const items = inProgress
			.map((t) => {
				let players: string[] = [];
				if (Array.isArray(t.players)) {
					players = t.players;
				} else if (typeof t.players === 'string') {
					try {
						const parsed = JSON.parse(t.players);
						if (Array.isArray(parsed)) players = parsed;
					} catch {

					}
				}

				const createdAtRaw = t.created_at || t.createdAt;
				let createdAtLabel = '';
				if (createdAtRaw) {
					const d = new Date(String(createdAtRaw).replace(' ', 'T'));
					createdAtLabel = isNaN(d.getTime())
						? String(createdAtRaw)
						: d.toLocaleString();
				}

				const isSelected = selectedId && t.id === selectedId;

				return `
          <button
            class="w-full flex items-center justify-between text-sm bg-gray-900/70 border ${isSelected ? 'border-pong-green' : 'border-gray-700'
					} rounded-xl px-3 py-2 text-left hover:border-pong-green transition-colors"
            data-action="load-tournament"
            data-tournament-id="${t.id}"
          >
            <div>
              <div class="font-medium">
                ${this.escapeHtml(String(t.name ?? 'Unnamed tournament'))}
              </div>
              <div class="text-xs text-gray-400">
                <span data-i18n-key="tournament.userTournaments.players">
                  Players:
                </span>
                ${players.length}
                ${createdAtLabel
						? `· ${this.escapeHtml(createdAtLabel)}`
						: ''
					}
              </div>
            </div>
          </button>
        `;
			})
			.join('');

		container.innerHTML = `
      <div class="space-y-2">
        ${items}
      </div>
    `;
	}
}
