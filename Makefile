# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 10:30:09 by yusengok          #+#    #+#              #
#    Updated: 2024/04/15 22:18:06 by dvo              ###   ########.fr        #
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

vpath %c ./ft_minishell ./ft_minishell/parsing ./ft_minishell/builtin ./ft_minishell/exec ./ft_minishell/redirection ./ft_minishell/utils
SRCS =	main.c	\
		ft_cd.c	\
		ft_cd_concatenater.c	\
		ft_cd_canonicalizer.c	\
		ft_echo.c	\
		ft_env.c \
		ft_exit.c	\
		ft_export.c \
		ft_export_add.c	\
		ft_export_print.c	\
		ft_pwd.c \
		ft_unset.c	\
		ft_exec.c	\
		pipex.c	\
		pipex_utils.c	\
		execute_command.c	\
		utils_exec.c	\
		redirection.c	\
		open_file.c	\
		heredoc.c	\
		utils_redirection.c	\
		chara_split.c	\
		count_lst.c	\
		count_lst_utils.c	\
		create_nod.c \
		write_on_nod.c	\
		write_file.c \
		assign_env.c \
		translate_dollar.c	\
		parsing_utils.c \
		error_handling.c	\
		ft_free.c	\
		env.c \
		init.c	\
		assign_env_value.c \
		signal_handle.c

DIR_OBJ := .object/

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRCS))

all: mlibft mfprintf $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIB_DIR) $(LIBS) -o $(NAME)
	@printf "$(LIGHT_GREEN)minishell is ready to launch\n$(RESET)"

$(DIR_OBJ)%.o: %.c $(IFLAGS) Makefile
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

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