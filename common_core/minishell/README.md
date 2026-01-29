# Minishell

Minishell est une implémentation minimaliste d’un shell Unix compatible POSIX. Il gère un prompt interactif, l’historique, les pipelines, les redirections, les heredocs et un sous‑ensemble de builtins.

- Entrée principale: [src/main.c](src/main.c)
- Déclarations globales et structures: [include/minishell.h](include/minishell.h)

## Compilation

Pré-requis:
- libreadline (Linux: `libreadline-dev`, macOS: `brew install readline`)

Construire:
- `make` pour compiler le projet et la libft
- `make clean / fclean / re` pour le cycle habituel

Exécution:
- `./minishell`

## Utilisation rapide

Exemples:
- Commande simple: `echo hello`
- Pipelines: `ls -l | grep Makefile | wc -l`
- Redirections:
  - Sortie: `echo hi > out.txt`, `echo hi >> out.txt`
  - Entrée: `cat < in.txt`
- Heredoc: `cat << EOF` puis taper des lignes, terminer par `EOF`
- Builtins pris en charge: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`

Remarques:
- L’historique est géré (readline).
- Limitation volontaire: trop de pipes -> message d’erreur (voir [src/utils/utils2.c](src/utils/utils2.c)).

## Comment ça marche (vue d’ensemble)

1) Boucle principale
- Affiche un prompt coloré, lit une ligne avec readline, gère EOF et Ctrl‑C/Ctrl‑\.
- Voir: [src/main.c](src/main.c), [src/utils/signals.c](src/utils/signals.c)

2) Parsing
- Découpe l’entrée en tokens (mots, opérateurs | < > << >>, quotes), vérifie la syntaxe, construit une liste chaînée de commandes (pipeline) avec leurs redirections.
- Fichiers clés:  
  - Tokenisation: [src/parser/tokenize.c](src/parser/tokenize.c)  
  - Gestion des quotes/syntaxe/extraction: [src/parser/quotes.c](src/parser/quotes.c), [src/parser/syntax.c](src/parser/syntax.c), [src/parser/extract.c](src/parser/extract.c)  
  - Construction des commandes: [src/parser/parser.c](src/parser/parser.c), [src/parser/utils_parser.c](src/parser/utils_parser.c)

3) Exécution
- Cas 1: un seul builtin sans pipe → exécution dans le processus parent (préserve l’environnement, pas de fork).
- Cas 2: commande externe ou pipeline → création des pipes, fork par commande, application des redirections, exécution (execve), attente des enfants, récupération du code de retour.
- Fichiers clés:  
  - Orchestration d’une ligne: [src/exec/src/cmd/exec_readline.c](src/exec/src/cmd/exec_readline.c)  
  - Redirections: [src/exec/src/cmd/handle_redirections.c](src/exec/src/cmd/handle_redirections.c)  
  - Heredoc: [src/exec/src/cmd/exec_here_doc.c](src/exec/src/cmd/exec_here_doc.c), [src/exec/src/cmd/here_doc_utils.c](src/exec/src/cmd/here_doc_utils.c)  
  - Pipelines et init: [src/exec/src/cmd/init.c](src/exec/src/cmd/init.c)  
  - Exécution des builtins: [src/exec/src/cmd/exec_built_in.c](src/exec/src/cmd/exec_built_in.c), [src/exec/src/built_in](src/exec/src/built_in)  
  - Recherche du binaire et PATH: [src/exec/src/cmd/find_paths.c](src/exec/src/cmd/find_paths.c)

4) Gestion des erreurs, signaux et ressources
- Messages d’erreur cohérents: [src/utils/error.c](src/utils/error.c)
- Signaux (interactive vs. enfants): [src/utils/signals.c](src/utils/signals.c)
- Nettoyage mémoire/FD: [src/utils/free.c](src/utils/free.c), [src/exec/src/cmd/close_and_free.c](src/exec/src/cmd/close_and_free.c)

## Notions apprises

- Lecture interactive et édition de ligne (readline, historique)
- Lexing/parsing simple (tokens, quotes, redirections, pipeline)
- Processus et concurrence (fork, execve, waitpid)
- Communication inter‑processus (pipe, duplication via dup/dup2)
- Redirections I/O et gestion fine des descripteurs de fichiers
- Heredoc (pipe temporaire, expansion contrôlée, gestion Ctrl‑C)
- Builtins vs. commandes externes (exécution dans le parent vs. enfant)
- Variables d’environnement (liste chaînée, export/unset/env)
- Gestion des signaux en contexte shell vs. enfants
- Gestion d’erreurs et codes de retour (126, 127, etc.)
- Organisation modulaire du code et Makefiles, libft utilitaire

## Structure du projet

- Entrée/sortie: [src/main.c](src/main.c)
- Parsing: [src/parser](src/parser)
- Exécution: [src/exec/src/cmd](src/exec/src/cmd)
- Builtins: [src/exec/src/built_in](src/exec/src/built_in)
- Utilitaires (env, erreurs, signaux, helpers): [src/utils](src/utils)
- Lib personnelle: [libft](libft)

Bon hacking !
