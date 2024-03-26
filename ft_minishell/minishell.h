/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/26 14:44:32 by yusengok         ###   ########.fr       */
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
# include <signal.h> 
# include "libft.h"
# include "ft_printf.h"

# define HEREDOC "here_doc"
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

typedef struct s_env
{
	char			*key;
	char			*value;
	int				order;
	struct s_env	*next;
}	t_env;

enum e_file_type
{
	INFILE = 1,
	OUT_TRUNC = 2,
	OUT_APPEND = 3,
	HERE_DOC = 4
};

typedef struct s_file
{
	char				*filename;
	enum e_file_type	type;
	struct s_file		*next;
}				t_file;

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
	t_env	*envn;
	t_line	*lst;
}			t_base;

/*----- Execution ------------------------------------------------------------*/
/* ft_exec.c */
int		ft_exec(t_base *base);
int		execute_single_command(t_base *base);
// static void	static int	execute_external_command(t_base *base);
// static pid_t	ft_fork(int fd_in, int fd_out);

/* pipex.c & pipex_loop.c */
int		pipex(t_base *base);
void	pipe_execute_builtin(t_base *base);
// static pid_t	pipe_last_command(t_base *base, int fd_in);
int		pipe_loop(t_base *base, int *fd_in, int *fd_out);
// static int		init_pipe(int (*pipefd)[2]);
// static pid_t	ft_fork_pipex(int pipe[2]);

/* execute command */
void	execute_command(t_base *base);
// static char	*get_pathname(t_base *base);
// static char	**extract_path(t_base *base);
// static void	perror_exit(char *message, int exit_status);

/* open_file.c */
int		open_infile(t_base *base);
int		open_outfile(t_base *base);
void	ft_close(int fd1, int fd2);
void	ft_close_in_child(int fd1, int fd2);

/* redirection.c */
int		check_redirection(t_base *base, int *fd_in, int *fd_out);
// static int	check_heredoc(t_base *base);
// static int	get_heredoc_lines(char *delimiter, int fd_heredoc);

/* utils_exec.c */
void	dup_input(int fd_in);
void	dup_output(int fd_out);
void	unlink_heredoc(void);

/*----- Builtin commands -----------------------------------------------------*/
int		ft_cd(t_base *base);
int		ft_echo(t_base *base);
int		ft_pwd(t_base *base);
int		ft_env(t_base *base);
int		ft_exit(t_base *base, int exit_status);
int		ft_export(t_base *base);

/*----- Utils ----------------------------------------------------------------*/
/* error handling */
int		print_error(char *s1, char *s2, int exit_status);
int		ft_perror(const char *s, int exit_status);
/* free */
void	ft_free(void * to_free);
void	ft_free_strarr(char **arr);
void	free_base_content(t_base *base);
void	free_envlist(t_base *base);

/*----- Parsing --------------------------------------------------------------*/
int		ft_chara_split(char *s, t_base **base);
int		write_char(int i, t_line *tmp, char *str, t_base *base);
int		write_in_file(int i, t_line *tmp, char *str);
int		write_out_file(int i, t_line *tmp, char *str);
int		cnt_param(char *str, t_line *line);
int		write_double_quote(int i, t_line *tmp, char *str, t_base *base);
int		write_simple_quote(int i, t_line *tmp, char *str);
int		assign_env(t_base *base, char **env);
void	ft_display_error(int i);
void	write_nod(int i, t_line *tmp, char *str, t_base *base);
char	*assign_value(char **split);
char	*translate_dollar(char *str, t_base *base);

# define RED "\033[1;31m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

#endif
