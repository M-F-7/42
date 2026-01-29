NAME = philo

SRCDIR = src
SRC = main.c \
		errors.c \
		utils.c \
		init_args.c \
		handle_mutex.c \
		handle_thread.c \
		routine.c \
		safe_printf.c \
		monitoring.c \


OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)


INCLUDE = include

CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
