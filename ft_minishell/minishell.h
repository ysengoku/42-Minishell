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


typedef enum
{
    INFILE = 1,
    OUT_TRUNC = 2,
    OUT_APPEND = 3,
    HERE_DOC = 4
}    e_file_type;

typedef struct s_file
{
    char				*filename;
    e_file_type			type;
    struct s_file		*next;
}                t_file;


typedef struct s_open_file
{
	char	*file;
	bool	out;
	bool	append;
	bool	here_doc;
}				t_open_file;

typedef struct s_line
{
	t_file			*file;
	char			**arg;
	int				nb_arg;
	struct s_line	*next;
}				t_line;

typedef struct s_base
{
	char	**env;
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
