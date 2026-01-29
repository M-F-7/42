NAME = push_swap
NAME_BONUS = checker

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = src/main.c \
		src/little_sort_utils.c \
		src/little_sort.c \
		src/utils_sort.c \
		src/swap.c \
		src/push.c \
		src/rotate.c \
		src/rev_rotate.c \
		src/stack_utils.c \
		src/errors.c \
		src/sort_stack.c \
		src/stack_init.c \
		libft/printf/ft_printf.c \
		libft/printf/ft_putchar.c \
		libft/printf/ft_putstr.c \
		libft/printf/ft_putnbr.c \
		libft/printf/ft_putnbr_base.c \
		libft/printf/ft_putptr.c \
		libft/printf/ft_putnbr_us.c \
		libft/ft_split.c \
		libft/ft_strlen.c \
		libft/ft_atoi.c \
		libft/ft_isdigit.c \
		libft/ft_putstr_fd.c \
		libft/ft_putchar_fd.c

SRC_BONUS = bonus/main.c \
			bonus/errors_bonus.c \
			bonus/utils_bonus.c \
			bonus/utils2_bonus.c \
			src/swap.c \
			src/push.c \
			src/rotate.c \
			src/rev_rotate.c \
			libft/printf/ft_printf.c \
			libft/ft_strncmp.c \
			libft/gnl/get_next_line.c \
			libft/gnl/get_next_line_utils.c \
			libft/printf/ft_putchar.c \
			libft/printf/ft_putstr.c \
			libft/printf/ft_putnbr.c \
			libft/printf/ft_putnbr_base.c \
			libft/printf/ft_putptr.c \
			libft/printf/ft_putnbr_us.c \
			libft/ft_split.c \
			libft/ft_strlen.c \
			libft/ft_atoi.c \
			libft/ft_isdigit.c \
			libft/ft_putstr_fd.c \
			libft/ft_putchar_fd.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

INC = push_swap.h \
	  libft/libft.h \
	  libft/printf/ft_printf.h

INC_BONUS = bonus/push_swap_bonus.h \
			libft/libft.h \
			libft/printf/ft_printf.h

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o: %.c $(INC) $(INC_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean re all bonus
