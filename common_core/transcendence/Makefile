DOCKER_NAME = transceandance__42

BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[1;37m
GRAY    = \033[0;37m
GOLD    = \033[0;93m
BRIGHT_BLACK   = \033[1;90m
BRIGHT_RED     = \033[1;91m
BRIGHT_GREEN   = \033[1;92m
BRIGHT_YELLOW  = \033[1;93m
BRIGHT_BLUE    = \033[1;94m
BRIGHT_MAGENTA = \033[1;95m
BRIGHT_CYAN    = \033[1;96m
BRIGHT_WHITE   = \033[1;97m
BRIGHT_GRAY    = \033[0;97m
BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
RESET = \033[0m


all:
	@echo "$(BOLD)$(BRIGHT_BLUE)Building $(DOCKER_NAME) 🐋$(RESET)"
	@./infrastructure/docker-network/init_network.sh
	@docker compose build && docker compose up -d

db-shell:
	@echo "$(BOLD)$(BRIGHT_CYAN)SQLite Shell 🗄️$(RESET)"
	@docker exec -it $(shell docker ps -qf name=backend) sqlite3 /app/data/transcendence.db

go:
	@code --folder-uri "vscode-remote://attached-container+$(shell docker ps -qf name=$(DOCKER_NAME))/workspace"

ps:
	@docker compose ps
stop:
	@echo "$(BOLD)$(BRIGHT_RED)STOP ✋🛑$(RESET)"
	@docker compose down

clean:
	@echo "$(BOLD)$(BRIGHT_GREEN)Cleaning some Shits 💩$(RESET)"
	@docker system prune -a --volumes
