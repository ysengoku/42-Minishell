/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/23 19:51:10 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
#include<stdio.h> 
#include<signal.h> 
# include "libft.h"
# include "ft_printf.h"

# define PWD_SIZE 1024

# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"

# define IN 0
# define OUT 1

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;

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

/*----- Execution ------------------------------------------------------------*/
/* ft_exec.c */
int		ft_exec(t_base *base);
int		execute_builtin(t_base *base);
// static void	execute_single_command(t_base *base);

/* pipex.c */
int		pipex(t_base *base);
// static void		init_pipe(int (*pipefd)[2]);
// static void		pipe_loop(t_base *base, int *fd_in, int *fd_out);
// static pid_t	pipe_last_command(t_base *base, int fd_in);

/* execute command */
void	execute_command(t_base *base);
// static char	*get_pathname(t_base *base);
// static char	**extract_path(t_base *base);

/* open_file.c */
int		open_infile(t_base *base);
int		open_outfile_trunc(t_base *base);
int		open_outfile_append(t_base *base);
void	ft_close(int fd1, int fd2);

/* redirection.c */
int	check_redirection(t_base *base, int *fd_in, int *fd_out);
// static void	check_redirection_in(t_base *base, int *fd_in);
// static void	check_redirection_out(t_base *base, int *fd_in, int *fd_out);

/* utils_exec.c */
void	dup_input(int fd_in);
void	dup_output(int fd_out);

/*----- Builtin commands -----------------------------------------------------*/
int		ft_echo(t_base *base);
int		ft_pwd(t_base *base);
void	ft_exit(t_base *base, int exit_status);

/*----- Utils ----------------------------------------------------------------*/
/* error handling */
void	print_error(char *st1, char *st2);
/* free */
void	ft_free_strarr(char **arr);
void 	free_base(t_base *base);

 // To put into libft ?
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

int		ft_chara_split(char *s, t_base **base);
int		write_in_file(int i, t_line *tmp, char *str);
int		write_out_file(int i, t_line *tmp, char *str);
int		cnt_param(char *str, t_line *line);
void	write_nod(int i, t_line *tmp, char *str);
void	ft_display_error(int i);

# define RED "\033[1;31m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

#endif
