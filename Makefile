# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 10:30:09 by yusengok          #+#    #+#              #
#    Updated: 2024/03/21 14:48:27 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
#RDFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
IFLAGS = ./ft_minishell/minishell.h
INC_DIR = -I./ft_minishell -I$(LIBFT_DIR) -I/usr/local/include
LIB_DIR = -L/usr/local/lib -L./lib/libft
INC_DIR_MAC = -I./ft_minishell -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I/usr/local/opt/readline/include
LIB_DIR_MAC = -L/usr/local/opt/readline/lib -L./lib/libft
LIBS = -lreadline -lft

LIBFT_DIR	= ./lib/libft
LIBFT_H		= $(LIBFT_DIR)/libft.h
LIBFT       = $(LIBFT_DIR)/libft.a

PRINTF_DIR	= ./lib/ft_fprintf
PRINTF_H	= $(PRINTF_DIR)/ft_printf.h
PRINTF		= $(PRINTF_DIR)/libftprintf.a

vpath %c ./ft_minishell ./ft_minishell/parsing ./ft_minishell/builtin ./ft_minishell/exec ./ft_minishell/utils
SRCS =	main.c	\
		ft_echo.c	\
		ft_pwd.c \
		ft_exit.c	\
		ft_exec.c	\
		pipex.c	\
		execute_command.c	\
		open_file.c	\
		redirection.c	\
		utils_exec.c	\
		utils.c	\
		chara_split.c	\
		count_lst.c	\
		write_on_nod.c	\
		error_handling.c	\
		ft_free.c	

DIR_OBJ := .object/

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRCS))

all: mlibft mfprintf $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(INC_DIR) $(LIB_DIR) $(LIBS) -o $(NAME) $(OBJS)
#	$(CC) $(CFLAGS) $(INC_DIR_MAC) $(LIB_DIR_MAC) $(LIBS) -o $(NAME) $(OBJS)
#	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(RDFLAGS) -o $(NAME)

$(DIR_OBJ)%.o: %.c $(IFLAGS) Makefile
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR) 
#	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR_MAC) 
#$(RDFLAGS)

mlibft:
	make -C $(LIBFT_DIR)

mfprintf:
	make -C $(PRINTF_DIR)
	
clean:
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	rm -rf $(DIR_OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re mlibft mfprintf