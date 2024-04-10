/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/10 11:30:33 by yusengok         ###   ########.fr       */
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
# include <dirent.h>
# include <limits.h>
# include <linux/limits.h>
# include "libft.h"
# include "ft_printf.h"

# define COMMANDLINE_USAGE "\n./minishell for interactive mode\n\
./minishell -c \"[commande lines]\" for command-line mode"
# define DELETED_CWD "error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or director"

# define HEREDOC "here_doc"

# define CD "cd"
# define ECHO "echo"
# define ENV "env"
# define EXIT "exit"
# define EXPORT "export"
# define PWD "pwd"
# define UNSET "unset"
# define EXITSTATUS "$?"

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
	HERE_DOC = 4,
	OUT_ERR = 5
};

enum e_type_char
{
	STANDARD,
	QUOTE,
	DOUBLE_Q,
	DOC,
	DOC_DOUBLE_Q,
	DOC_QUOTE,
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
}			t_base;

/*----- Execution ------------------------------------------------------------*/
/* ft_exec.c */
int		ft_exec(t_base *base);

/* pipex.c & pipex_utils.c */
int		pipex(t_base *base);
int		init_pipe(int (*pipefd)[2]);
pid_t	ft_fork_pipex(int pipe[2]);
void	pipe_child(t_base *base, t_line *node, int fd_in, int fd_out);
void	pipe_execute_builtin(t_base *base, t_line *node, int fd[2]);
void	free_all_in_child(t_base *base);

/* execute command */
void	execute_command(t_base *base, t_line *node);

/* open_file.c */
int		open_infile(t_file *infile, t_base *base);
int		open_outfile(t_file *outfile, t_base *base);
int		ft_close(int fd1, int fd2, int exit_code);
void	ft_close_in_child(int fd1, int fd2);

/* redirection.c */
int		check_redirection(t_base *base, t_line *node, int *fd_in, int *fd_out);
char	*get_expanded_str(size_t *i, char *line, t_base *base);
char	*append_buf(char *expanded_line, char *buf);
char	*get_str(size_t *i, char *line);
char	*handle_malloc_failure(char	*to_free);

/* utils_exec.c */
void	dup_input(int fd_in);
void	dup_output(int fd_out);
void	unlink_heredoc(void);
int		check_dir(char *name, t_base *base);
int		error_in_child(t_base *base, int exit_code, char *s1, char *s2);

/*----- Builtin commands -----------------------------------------------------*/
/* ft_cd */
int		ft_cd(t_base *base, t_line *node, int fd[2]);
char	*get_path(t_base *base, char *destination);
char	*get_pwd(void);
char	*concatenate_path(t_base *base, char *curpath);
void	canonicalize_path(char *curpath);
/* ft_echo */
int		ft_echo(t_line *node, int fd[2]);
/* ft_pwd */
int		ft_pwd(t_base *base, int fd[2]);
/* ft_env */
int		ft_env(t_base *base, t_line *node, int fd[2]);
/* ft_exit */
int		ft_exit(t_base *base, t_line *node, int fd[2]);
/* ft_export */
int		ft_export(t_base *base, int fd[2]);
int		check_error_export(char *str, t_base *base);
int		export_null(t_base *base, int fd[2]);
void	export_add_on_nod(t_base *base, t_env *tmp);
/* ft_unset */
int		ft_unset(t_base *base, t_line *node, int fd[2]);

/*----- Utils ----------------------------------------------------------------*/
/* error handling */
int		print_err(char *s1, char *s2, char *s3, int exit_status);
void	ft_display_error(int i, t_base *base);
int		ft_perror(const char *s, int exit_status);
/* free */
int		ft_free(void *to_free, int exit_status);
void	ft_free_strarr(char **arr);
void	free_base_content(t_base *base);
void	free_envlist(t_base *base);
/* envp */
t_env	*find_env_var(t_base *base, char *key);

/*----- Parsing --------------------------------------------------------------*/
int		ft_chara_split(char *s, t_base **base);
int		write_in_file(int i, t_line *tmp, char *str, t_base *base);
int		write_out_file(int i, t_line *tmp, char *str, t_base *base);
int		cnt_param(char *str, t_line *line);
int		enter_quote_mode(char *str, int i, t_line *tmp);
int		assign_env(t_base *base, char **env);
void	write_nod(int i, t_line *tmp, char *str, t_base *base);
char	*assign_value(char **split);
char	*translate_dollar(char *str, t_base *base, char *before);
char	*write_char(int *i, t_line *tmp, char *str, t_base *base);

# define RED "\033[1;31m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define CYAN "\001\033[1;36m\002"
# define YELLOW "\033[1;33m"
# define RESET "\001\033[0m\002"

#endif
