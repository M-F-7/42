NAME = pipex
NAME_BONUS = pipex_bonus

SRC = mandatory/pipex.c \
    mandatory/process.c \
    mandatory/handle_errors.c \
    mandatory/find_paths.c \
    libft/ft_split.c \
    libft/ft_strjoin.c \
    libft/ft_strlen.c \
    libft/ft_strncmp.c \
    libft/ft_strdup.c \
    libft/ft_strchr.c \
    libft/ft_putstr_fd.c \
    libft/ft_putchar_fd.c \
    libft/printf/ft_printf.c \
    libft/printf/ft_putptr.c \
    libft/printf/ft_putnbr.c \
    libft/printf/ft_putnbr_us.c \
    libft/printf/ft_putnbr_base.c \
    libft/printf/ft_putstr.c \
    libft/printf/ft_putchar.c \
    libft/ft_putendl_fd.c 
    

OBJ = $(SRC:.c=.o)

SRC_BONUS = bonus/pipex_bonus.c \
    bonus/handle_errors_bonus.c \
    bonus/here_doc_bonus.c \
    bonus/utils_bonus.c \
    bonus/exec_bonus.c \
    mandatory/find_paths.c \
    mandatory/process.c \
    mandatory/handle_errors.c \
    libft/ft_split.c \
    libft/ft_strjoin.c \
    libft/ft_strlen.c \
    libft/ft_strncmp.c \
    libft/ft_strdup.c \
    libft/ft_strchr.c \
    libft/ft_putstr_fd.c \
    libft/ft_putchar_fd.c \
    libft/gnl/get_next_line.c \
    libft/gnl/get_next_line_utils.c \
    libft/ft_putendl_fd.c 

OBJ_BONUS = $(SRC_BONUS:.c=.o)

INC = -Imandatory -Ilibft -Ibonus -Ilibft/gnl

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean re all bonus
