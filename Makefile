# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 10:30:09 by yusengok          #+#    #+#              #
#    Updated: 2024/03/20 11:39:11 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = ./ft_minishell/minishell.h
INCLUDE = -I./ft_minishell -I$(LIBFT_DIR)
#INCLUDE = -I./ft_minishell -I$(LIBFT_DIR) -I$(PRINTF_DIR)

LIBFT_DIR	= ./lib/libft
LIBFT_H		= ./lib/libf/libft.h
LIBFT       = ./lib/libft/libft.a

#PRINTF_DIR	= ./lib/libft_fprintf
#PRINTF_H	= ./lib/ft_libfprintf/ft_printf.h
#PRINTF		= ./lib/libft_fprintf/libftprintf.a

#SRCS = ./ft_minishell/ft_pipex/pipe_utils.c \
		 ./ft_minishell/ft_pipex/ft_create_ar.c \
		 			 ./ft_minishell/ft_pipex/main.c \
			 ./ft_minishell/ft_pipex/search_env.c \
			 ./ft_minishell/ft_pipex/child_exec.c \
			 ./ft_minishell/ft_pipex/fd_open_file.c	\
			 ./ft_minishell/builtin/ft_echo.c

vpath %c ./ft_minishell/builtin ./ft_minishell/exec
SRCS =	test_main.c	\
		ft_echo.c	\
		ft_pwd.c \
		ft_exec.c	\
		open_file.c	\
		ft_execve.c	\
		utils_exec.c	\
		utils.c

DIR_OBJ := .object/

OBJS = $(patsubst %.c, ${DIR_OBJ}%.o, ${SRCS})

all: mlibft $(NAME)
#all: mlibft mfprintf $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
#	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -L$(PRINTF_DIR) -lft -lftprintf -o $(NAME)

${DIR_OBJ}%.o: %.c $(IFLAGS) Makefile
	mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

mlibft:
	make -C $(LIBFT_DIR)

#mfprintf:
#	make -C $(PRINTF_DIR)
	
clean:
	@make -C $(LIBFT_DIR) fclean
#	@make -C $(PRINTF_DIR) fclean
	rm -rf $(DIR_OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
#	@make -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re mlibft 
#mfprintf