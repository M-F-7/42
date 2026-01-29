NAME = ircserv

# SRC = $(shell find src -name "*.cpp")
SRC = $(addprefix src/, \
	\
	application/exceptions/NotConnected.cpp \
	application/exceptions/AlreadyRegisteredException.cpp \
	application/exceptions/NickException.cpp \
	application/exceptions/JoinException.cpp \
	application/exceptions/NeedMoreParamsException.cpp \
	application/exceptions/NoSuchChannelException.cpp \
	application/exceptions/NotOnChannelException.cpp \
	application/exceptions/ChanOperatorNeededException.cpp \
	application/exceptions/UserNotInChannelException.cpp \
	application/exceptions/NoSuchNickException.cpp \
	application/exceptions/CannotSendToChanException.cpp \
	\
	application/adapters/FunnyPublisher.cpp \
	\
	application/commands/CommandPing.cpp \
	application/commands/CommandBot.cpp \
	application/commands/CommandBus.cpp \
	application/commands/CommandCap.cpp \
	application/commands/CommandInvite.cpp \
	application/commands/CommandJoin.cpp \
	application/commands/CommandKick.cpp \
	application/commands/CommandMode.cpp \
	application/commands/CommandNick.cpp \
	application/commands/CommandNotice.cpp \
	application/commands/CommandPart.cpp \
	application/commands/CommandPass.cpp \
	application/commands/CommandPrivMsg.cpp \
	application/commands/CommandQuit.cpp \
	application/commands/CommandTopic.cpp \
	application/commands/CommandUser.cpp \
	\
	application/use_cases/InformChannel.cpp \
	application/use_cases/InformSenderError.cpp \
	application/use_cases/InformUser.cpp \
	application/use_cases/SendResponse.cpp \
	application/use_cases/DisconnectUser.cpp \
	\
	di/Adapters.cpp \
	di/Commands.cpp \
	di/Container.cpp \
	di/Infrastructures.cpp \
	di/Networks.cpp \
	di/UseCases.cpp \
	\
	domain/model/Channel.cpp \
	domain/model/Client.cpp \
	domain/model/Response.cpp \
	domain/model/ServerConfig.cpp \
	domain/model/User.cpp \
	domain/exceptions/Exceptions.cpp \
	domain/exceptions/StatusException.cpp \
	\
	infrastructure/network/ClientHandler.cpp \
	infrastructure/network/NetworkException.cpp \
	infrastructure/network/Sender.cpp \
	infrastructure/network/PollReactor.cpp \
	infrastructure/network/ServerHandler.cpp \
	infrastructure/network/SocketAcceptor.cpp \
	infrastructure/network/TCPServer.cpp \
	\
	infrastructure/persistence/ChannelStore.cpp \
	infrastructure/persistence/ClientStore.cpp \
	infrastructure/persistence/UserStore.cpp \
	\
	parsing/Parser.cpp\
	parsing/ParserCommands.cpp\
	parsing/ParserUtils.cpp\
	parsing/ParserValidation.cpp\
	parsing/ParserParameters.cpp\
	main.cpp\
)

TESTS = $(addprefix tests/, \
	test_pass.cpp \
	test_nick.cpp \
	test_user.cpp \
	test_runner.cpp \
	test_quit.cpp \
)

OBJDIR = obj
DEPDIR = dep

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEPS = $(SRC:%.cpp=$(DEPDIR)/%.d)

INCLUDE = . src inc \
	src/domain/model \
	src/domain/ports \
	src/domain/exceptions \
	src/di \
	src/application \
	src/application/commands \
	src/application/ports \
	src/application/adapters \
	src/application/exceptions \
	src/application/use_cases \
	src/infrastructure/network \
	src/infrastructure/persistence

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 $(addprefix -I,$(INCLUDE)) -MMD -MP -g
FLAGS = -Wall -Wextra -Werror -std=c++98


BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[1;37m
PINK = \033[0;35m
BRIGHT_BLACK   = \033[1;90m
BRIGHT_RED     = \033[1;91m
BRIGHT_GREEN   = \033[1;92m
BRIGHT_YELLOW  = \033[1;93m
BRIGHT_BLUE    = \033[1;94m
BRIGHT_MAGENTA = \033[1;95m
BRIGHT_CYAN    = \033[1;96m
BRIGHT_WHITE   = \033[1;97m
BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
RESET = \033[0m

all: $(NAME) banner

-include $(DEPS)

banner:
	@echo ""
	@printf "$(PINK)$(BOLD)██╗ ██████╗  ██████╗\n"
	@printf "$(PINK)$(BOLD)██║ ██╔══██╗██╔════╝\n"
	@printf "$(PINK)$(BOLD)██║ ██████╔╝██║     \n"
	@printf "$(PINK)$(BOLD)██║ ██╔══██╗██║     \n"
	@printf "$(PINK)$(BOLD)██║ ██║  ██║╚██████╗\n"
	@printf "$(PINK)$(BOLD)╚═╝ ╚═╝  ╚═╝ ╚═════╝\n"
	@printf "$(RED)$(ITALIC)M$(GREEN)$(ITALIC)o$(BLUE)$(ITALIC)s$(YELLOW)$(ITALIC)s $(WHITE)$(ITALIC)M$(CYAN)$(ITALIC)i$(BRIGHT_GREEN)$(ITALIC)n$(BRIGHT_MAGENTA)$(ITALIC)e$(BRIGHT_WHITE)$(ITALIC)u$(BRIGHT_RED)$(ITALIC)r $(BRIGHT_CYAN)$(ITALIC)B$(YELLOW)$(ITALIC)o$(BLUE)$(ITALIC)s$(GREEN)$(ITALIC)s$(PINK)$(ITALIC)'s $(BRIGHT_WHITE)$(ITALIC)s$(BRIGHT_MAGENTA)$(ITALIC)e$(BRIGHT_CYAN)$(ITALIC)r$(BRIGHT_YELLOW)$(ITALIC)v$(BRIGHT_BLUE)$(ITALIC)e$(BRIGHT_RED)$(ITALIC)r      $(RESET)\n"

$(NAME): $(OBJ)
	@echo "$(BOLD)$(BRIGHT_YELLOW)Linking $(NAME) ⚡$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(BOLD)$(BRIGHT_CYAN)$(NAME) compiled with $(FLAGS) ⚑$(RESET)"
	@echo "$(BOLD)$(BRIGHT_GREEN)$(NAME) compiled successfully ✅$(RESET)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@) $(DEPDIR)/$(dir $*)   # création des sous-dossiers nécessaires
	@echo "$(BOLD)$(BRIGHT_BLUE)Compiling $< 🔥$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@mv $(basename $@).d $(DEPDIR)/$*.d

tests: $(OBJ) $(TESTS)
	$(CXX) $(CXXFLAGS) -o tests.out $^
# 	./tests.out

bonus:
	@c++ -Wall -Wextra -Werror -std=c++98 src/domain/bot/bot.cpp -o bot

clean:
	@echo "$(BOLD)$(BRIGHT_RED)Cleaning object files 🧹$(RESET)"
	@rm -rf $(OBJDIR) bot
	@rm -rf $(DEPDIR) bot
	@echo "$(BOLD)$(BRIGHT_GREEN)Object files cleaned ✅$(RESET)"

fclean: clean
	@echo "$(BOLD)$(BRIGHT_RED)Removing $(NAME) 🚮$(RESET)"
	@rm -f $(NAME) bot
	@echo "$(BOLD)$(BRIGHT_GREEN)$(NAME) removed ✅$(RESET)"

re: fclean all

.PHONY: all clean fclean re
