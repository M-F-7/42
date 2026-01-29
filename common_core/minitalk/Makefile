SERVER = server
CLIENT = client

SRCS_SERVER = src/server.c
SRCS_CLIENT = src/client.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

INCLUDE = include

LIBFT = libft/libft.a
LIBFT_PATH = libft/
LIBFT_INCLUDE = libft/include
PRINTF = libft/printf/libft_printf.a
PRINTF_PATH = libft/printf/

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(LIBFT) $(PRINTF) $(CLIENT) $(SERVER)

$(CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT_PATH) -lft -L$(PRINTF_PATH) -lft_printf -o $(CLIENT)

$(SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT_PATH) -lft -L$(PRINTF_PATH) -lft_printf -o $(SERVER)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(PRINTF):
	$(MAKE) -C $(PRINTF_PATH)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFT_INCLUDE) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(PRINTF_PATH) clean
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	rm -f $(CLIENT) $(SERVER) $(LIBFT) $(PRINTF)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
