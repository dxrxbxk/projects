SRCS        = main.c mandelbrot.c julia.c utils.c ft_atof.c

CC          = cc

CFLAGS      = -Wall -Wextra -Werror -O3 -g3

LIB         = mlx/libmlx_Linux.a

NAME        = fractol

OBJS        = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lXext -lX11 -lm -lz -o $(NAME)

all: $(NAME)

clean:
	make -C mlx clean
	rm -rf $(OBJS)

fclean:	clean
	rm -rf $(LIB)
	rm -rf $(NAME)

re:         fclean all

.PHONY:     all clean fclean re
