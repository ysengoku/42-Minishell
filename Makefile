NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = ./ft_minishell/minishell.h


LIBFT_H        = ./lib/libf/libft.h
LIBFT        = ./lib/libft/libft.a
PRINTF_H	= ./lib/ft_fprintf/ft_printf.h
PRINTF		= ./lib/ft_fprintf/libftprintf.a

SRCS = ./ft_minishell/parcing/test.c

DIR_OBJ := .object/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})

all: mlibft mfprintf $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)

${DIR_OBJ}%.o: %.c $(IFLAGS) Makefile
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@

mlibft:
	make -C ./lib/libft

mfprintf:
	make -C ./lib/ft_fprintf
	
clean:
	@make -C ./lib/libft fclean
	@make -C ./lib/ft_fprintf fclean
	rm -f $(MY_OBJECTS)

fclean: clean
	@make -C ./lib/libft fclean
	@make -C ./lib/ft_fprintf clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re mlibft mfprintf