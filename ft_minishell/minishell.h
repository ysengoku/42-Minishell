#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_fprintf/ft_printf.h"

typedef struct s_cnt
{
	int		nb_arg;
	int		nb_out;
	int		nb_in;
}				t_cnt;

typedef struct s_open_file
{
	char	*file;
	bool	out;
	bool	append;
	bool	here_doc;
}				t_open_file;

typedef struct s_line
{
	t_open_file		*files;
	int				nb_arg;
	char			**arg;
	t_cnt			*count;
	struct s_line	*next;
}				t_line;

typedef struct s_base
{
	char **env;
	t_line	*lst;
}			t_base;

char	**ft_chara_split(char *s);
int	write_char(int i, t_line *tmp, char *str);
int	write_in_file(int i, t_line *tmp, char *str);
int	write_out_file(int i, t_line *tmp, char *str);
int	cnt_param(char *str, t_line *line);
int write_double_quote(int i, t_line *tmp, char *str);
int	write_simple_quote(int i, t_line *tmp, char *str);

#endif