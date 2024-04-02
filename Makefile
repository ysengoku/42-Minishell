# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 10:30:09 by yusengok          #+#    #+#              #
#    Updated: 2024/04/02 13:29:42 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET = \033[0m
LIGHT_GREEN = \033[1;32m
MAGENTA = \033[1;95m
CYAN = \033[1;36m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR	= ./lib/libft
LIBFT       = $(LIBFT_DIR)/libft.a

PRINTF_DIR	= ./lib/ft_fprintf
PRINTF		= $(PRINTF_DIR)/libftprintf.a

IFLAGS = ./ft_minishell/minishell.h
INCLUDE = -I./ft_minishell -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I/usr/local/include
LIB_DIR = -L$(LIBFT_DIR) -L$(PRINTF_DIR) -L/usr/local/lib
LIBS = -lreadline -lft -lftprintf

INC_DIR_MAC = -I./ft_minishell -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I/usr/local/opt/readline/include
LIB_DIR_MAC = -L/usr/local/opt/readline/lib -L./lib/libft

vpath %c ./ft_minishell ./ft_minishell/parsing ./ft_minishell/builtin ./ft_minishell/exec ./ft_minishell/utils
SRCS =	main.c	\
		ft_cd.c	\
		ft_cd_utils.c	\
		ft_echo.c	\
		ft_env.c \
		ft_exit.c	\
		ft_export.c \
		ft_pwd.c \
		ft_unset.c	\
		ft_exec.c	\
		pipex.c	\
		pipex_loop.c	\
		execute_command.c	\
		open_file.c	\
		redirection.c	\
		utils_exec.c	\
		chara_split.c	\
		count_lst.c	\
		write_on_nod.c	\
		write_file.c \
		error.c \
		assign_env.c \
		translate_dollar.c	\
		error_handling.c	\
		ft_free.c	\
		env.c

DIR_OBJ := .object/

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRCS))

all: mlibft mfprintf $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIB_DIR) $(LIBS) -o $(NAME)
	@printf "$(LIGHT_GREEN)minishell is ready to launch\n$(RESET)"
#	$(CC) $(CFLAGS) $(OBJS) $(INC_DIR_MAC) $(LIB_DIR_MAC) $(LIBS) -o $(NAME)

$(DIR_OBJ)%.o: %.c $(IFLAGS) Makefile
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)
#	$(CC) $(CFLAGS) -c $< -o $@ $(INC_DIR_MAC) 

mlibft:
	@make -C $(LIBFT_DIR)

mfprintf:
	@make -C $(PRINTF_DIR)
	
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