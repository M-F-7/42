NAME = Array

SRC = main.cpp 


DEPDIR = dep
DEPS = $(SRC:%.cpp=$(DEPDIR)/%.d)

OBJDIR = obj
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

INCLUDE = .

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I$(INCLUDE) -MMD -MP
FLAGS = -Wall -Wextra -Werror -std=c++98

BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[1;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[1;37m
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

all: $(NAME)

-include $(DEPS)

$(NAME): $(OBJ)
	@echo "$(BOLD)$(BRIGHT_YELLOW)Linking $(NAME) ⚡$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "$(BOLD)$(BRIGHT_CYAN)$(NAME) compiled with $(FLAGS) ⚑$(RESET)" 
	@echo "$(BOLD)$(BRIGHT_GREEN)$(NAME) compiled successfully ✅$(RESET)"

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DEPDIR)
	@echo "$(BOLD)$(BRIGHT_BLUE)Compiling $< 🔥$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@mv $(OBJDIR)/$(notdir $(basename $@)).d $(DEPDIR)/$(notdir $(basename $@)).d 2>/dev/null || true

clean:
	@echo "$(BOLD)$(BRIGHT_RED)Cleaning object files 🧹$(RESET)"
	@rm -rf $(OBJDIR)
	@rm -rf $(DEPDIR)
	@echo "$(BOLD)$(BRIGHT_GREEN)Object files cleaned ✅$(RESET)"

fclean: clean
	@echo "$(BOLD)$(BRIGHT_RED)Removing $(NAME) 🚮$(RESET)"
	@rm -f $(NAME)
	@echo "$(BOLD)$(BRIGHT_GREEN)$(NAME) removed ✅$(RESET)"

re: fclean all

.PHONY: all clean fclean re