# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 13:02:22 by dvo               #+#    #+#              #
#    Updated: 2024/02/24 15:27:32 by dvo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

IFLAGS = libft.h

MY_SOURCES = ft_putnbr_fd.c ft_putchar_fd.c ft_putstr_fd.c ft_calloc.c ft_putendl_fd.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c ft_atoi.c ft_strjoin.c ft_isalpha.c ft_memchr.c ft_memset.c ft_strlcpy.c ft_strrchr.c ft_bzero.c ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlen.c ft_substr.c ft_isdigit.c ft_memcpy.c ft_strdup.c ft_strncmp.c ft_tolower.c ft_isalnum.c ft_isprint.c ft_memmove.c ft_strlcat.c ft_strnstr.c ft_toupper.c ft_strtrim.c

BONUS = ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c

DIR_OBJ := .object/

MY_OBJECTS = $(patsubst %.c, ${DIR_OBJ}%.o, ${MY_SOURCES})

all: $(NAME)

$(NAME) : $(MY_OBJECTS) 
	ar -r $@ $^

${DIR_OBJ}%.o: %.c ${IFLAGS} Makefile
	mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@

clean:
	rm -f $(MY_OB) $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)

bonus: 
	@make MY_SOURCES="$(MY_SOURCES) $(BONUS)"

re : fclean all
