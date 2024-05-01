/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/30 23:04:06 by dvo              ###   ########.fr       */
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
# include <dirent.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"

extern int	g_received_signal;

# define COMMANDLINE_USAGE "\n./minishell for interactive mode\n\
./minishell -c \"[commande lines]\" for command-line mode"
# define NULL_DELIM "here-document delimited by end-of-file (wanted `"

# define HEREDOC ".here_doc"

# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"
# define EXITSTATUS "$?"

# define HOME "HOME"
# define OLDPWD "OLDPWD"

# define IN 0
# define OUT 1

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef NAME_MAX
#  define NAME_MAX 255
# endif

typedef struct s_env
{
	char			*key;
	char			*value;
	int				order;
	int				unset;
	struct s_env	*next;
}	t_env;

enum e_file_type
{
	INFILE = 1,
	OUT_TRUNC = 2,
	OUT_APPEND = 3,
	HERE_DOC = 4,
	HERE_DOC_NO = 5
};

enum e_type_char
{
	STANDARD = 1,
	QUOTE = 2,
	DOUBLE_Q = 3,
	DOC = 4,
	DOC_DOUBLE_Q = 5,
	DOC_QUOTE = 6
};

typedef struct s_file
{
	char				*filename;
	enum e_file_type	type;
	struct s_file		*next;
}				t_file;

typedef struct s_line
{
	t_file				*file;
	char				**arg;
	int					nb_arg;
	enum e_type_char	char_type;
	int					error_syntax;
	int					typ_write_chr;
	char				heredoc[NAME_MAX];
	int					index;
	struct s_line		*next;
}				t_line;

typedef struct s_base
{
	char	**env;
	t_env	*envn;
	t_line	*lst;
	int		exit_code;
	char	*error_msg;
	int		null_env;
	int		max_arg_export;
	char	pwd_log[PATH_MAX];
	char	oldpwd_log[PATH_MAX];
}			t_base;

typedef struct s_norm
{
	int		i;
	int		j;
	char	*str;
	t_line	*tmp;
	t_base	*base;
}				t_norm;

/*----- Parsing --------------------------------------------------------------*/
/* assign env */
int			assign_env(t_base *base);
char		*assign_value(char **split);
void		set_pwdlog(t_base *base);
/* chara_split */
int			ft_chara_split(char *s, t_base **base);
/* count lst */
int			cnt_param(char **str, t_line *line);
int			cnt_quote(char *str, t_line *line, int i);
int			skip_file(char **str, int i);
/* create node */
int			create_nod(char *str, t_base *base);
/*  translate_dollar */
char		*translate_dollar(char *str, t_base *base, char *before, \
t_line *tmp);
char		*translate_tilde(char *str, t_base *base, char *before);
/* wite file */
int			write_in_file(int i, t_line *tmp, char *str, t_base *base);
int			write_out_file(int i, t_line *tmp, char *str, t_base *base);
/* write on node */
char		*write_char(int *i, t_line *tmp, char *str, t_base *base);
/* parsing utils */
int			enter_quote_mode(char *str, int i, t_line *tmp);
int			index_dollars(t_norm *norm, int *ptr_i, char *res);
int			index_tilde(t_norm *norm, int *ptr_i, char *res);
int			count_last_len_dollars(char *str, int i, t_line *tmp);

/*----- Execution ------------------------------------------------------------*/
/* ft_exec.c */
int			ft_exec(t_base *base);
/* pipex.c & pipex_utils.c */
int			exec_pipe(t_base *base);
int			init_pipe(int (*pipefd)[2]);
pid_t		ft_fork_pipe(int pipe[2]);
void		pipe_child(t_base *base, t_line *node, int fd_in, int fd_out);
void		pipe_execute_builtin(t_base *base, t_line *node, int fd[2]);
void		free_all_in_child(t_base *base);
/* execute command */
void		execute_command(t_base *base, t_line *node);
/* utils_exec.c */
void		dup_input(int fd_in);
void		dup_output(int fd_out);
int			is_directory(t_base *base, char *name);
int			error_in_child(t_base *base, int exit_code, char *s1, char *s2);

/*----- Redirection ----------------------------------------------------------*/
/* open_file.c */
int			open_infile(t_base *base, t_line *node, t_file *infile, int old_fd);
int			open_outfile(t_file *outfile, t_base *base, int old_fd);
int			ft_close(int fd1, int fd2, int exit_code);
void		ft_close_in_child(int fd1, int fd2, int fd3);
/* redirection.c */
int			check_redir_syntax(t_base *base, t_line *node);
int			check_redir(t_base *base, t_line *node, int *fd_in, int *fd_out);
int			check_heredoc(t_base *base, t_line *node);
int			check_redir_p(t_base *base, t_line *node, int *fd_in, int *fd_out);
int			check_heredoc_p(t_base *base);
void		reset_heredoc(void);
int			get_heredoc_lines(t_base *base, t_file *file, int fd_heredoc);
char		*get_expanded_str(size_t *i, char *line, t_base *base);
char		*append_buf(char *expanded_line, char *buf);
char		*get_str(size_t *i, char *line);
char		*handle_malloc_failure(char	*to_free);
void		unlink_heredoc(t_base *base);
int			free_heredoc(char *line, int fd, int status);

/*----- Builtin commands -----------------------------------------------------*/
/* ft_cd */
int			ft_cd(t_base *base, t_line *node, int fd[2]);
char		*expand_path(t_base *base, char *arg);
char		*concatenate_path(t_base *base, char *curpath, int *missing_pwd);
void		canonicalize_path(char *curpath, t_line *node);
/* ft_echo */
int			ft_echo(t_line *node, int fd[2]);
/* ft_pwd */
int			ft_pwd(t_base *base, int fd[2]);
/* ft_env */
int			ft_env(t_base *base, t_line *node, int fd[2]);
/* ft_exit */
int			ft_exit(t_base *base, t_line *node, int fd[2], bool is_pipe);
long long	convert_exitcode(char *s);
/* ft_export */
int			ft_export(t_base *base, t_line *node, int fd[2]);
int			export_null(t_base *base, int fd[2]);
void		export_add_on_nod(t_base *base, t_env *tmp);
char		**split_export_arg(char *arg);
int			add_env_value(t_base *base, t_line *node, int i);
int			create_nod_from_arg(t_base *base, t_line *node, int i);
/* ft_unset */
int			ft_unset(t_base *base, t_line *node, int fd[2]);

/*----- Utils ----------------------------------------------------------------*/
/* error handling */
int			print_err(char *s1, char *s2, char *s3, int exit_status);
int			print_warning(char *s1, char *s2, char *s3, int exit_status);
int			print_err_malloc(void);
void		ft_display_error(int i, t_base *base);
int			ft_perror(const char *s, int exit_status);
/* free */
int			ft_free(void *to_free, int exit_status);
void		ft_free_strarr(char **arr);
void		free_base_content(t_base *base);
void		free_envlist(t_base *base);
int			clear_before_exit(t_base *base, int exit_code);
/* envp */
t_env		*find_env_var(t_base *base, char *key);
/* init */
t_base		*init_base(char **env);
void		check_shell_level(char **env);
/* signal */
void		handle_sigint(int sig);
void		exec_sigint(int sig);
void		exec_sigquit(int sig);
//void		set_exec_signal(void);////////////////////////////To DELETE if we don't use it
void		set_heredoc_signal(void);

# define RED "\033[1;31m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define CYAN "\001\033[1;36m\002"
# define YELLOW "\033[1;33m"
# define RESET "\001\033[0m\002"

#endif
