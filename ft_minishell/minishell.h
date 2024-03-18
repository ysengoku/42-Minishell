#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_fprintf/ft_printf.h"

typedef struct s_base
{
	char **env;
}			t_base;

char	**ft_chara_split(char const *s);
void	check_infile(char **line, int i);

#endif