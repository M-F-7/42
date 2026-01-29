NAME = so_long

SRC = mandatory/src/so_long.c \
      mandatory/src/map.c \
      mandatory/src/sprites.c \
      mandatory/src/player.c \
      mandatory/src/handle_errors.c \
      mandatory/src/collectible.c \
      mandatory/src/utils.c \
      mandatory/src/map_info.c \
      mandatory/src/create_map.c \
      mandatory/src/put_player.c \
      mandatory/src/put_wall.c \
      mandatory/src/put_utils.c \
      mandatory/src/handle_errors_2.c \
      mandatory/src/destroy.c \
      libft/ft_strdup.c \
      libft/ft_split.c \
      libft/ft_putstr_fd.c \
      libft/ft_strlen.c \
      libft/ft_putchar_fd.c \
      libft/gnl/get_next_line.c \
      libft/gnl/get_next_line_utils.c \
      libft/printf/ft_printf.c \
      libft/printf/ft_putchar.c \
      libft/printf/ft_putstr.c \
      libft/printf/ft_putptr.c \
      libft/printf/ft_putnbr.c \
      libft/printf/ft_putnbr_us.c \
      libft/printf/ft_putnbr_base.c \
      libft/ft_lstclear.c \
      libft/ft_lstdelone.c \
      libft/ft_strchr.c \
      libft/ft_strncmp.c \
      libft/ft_itoa.c \
      libft/ft_strlcpy.c \

OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g3

INC = mandatory/so_long.h \
    libft/libft.h \
    libft/printf/ft_printf.h \
    libft/gnl/get_next_line.h 

CC = cc

CFLAGS = -Wall -Wextra -Werror -Imlx -g

all: $(MLX) $(NAME)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: clean fclean re all
