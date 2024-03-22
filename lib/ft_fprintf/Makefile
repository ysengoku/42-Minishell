NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

INC = ft_printf.h

MY_SOURCES = ft_direction.c	\
			ft_printf.c \
			itoa_UL_16.c \
			ft_putnbr_fd.c \
			ft_hexa_ptr.c \
			ft_write_var.c \

DIR_OBJ := .object/

MY_OBJECTS = $(patsubst %.c, ${DIR_OBJ}%.o, ${MY_SOURCES})

all: $(NAME)

$(NAME) : $(MY_OBJECTS) 
	ar -r $@ $^

${DIR_OBJ}%.o: %.c ${INC} Makefile
	@mkdir -p $(shell dirname $@)
	$(CC) ${CFLAGS} -c $< -o $@

clean:
	$(RM) -r $(DIR_OBJ)
#	rm -f $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: clean fclean re all
