/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/02 14:34:28 by yusengok         ###   ########.fr       */
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
# include "libft.h"
# include "ft_printf.h"

# define COMMANDLINE_USAGE "\n./minishell for interactive mode\n\
./minishell -c \"[commande lines]\" for command-line mode"

# define HEREDOC "here_doc"
# define PWD_SIZE 1024

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
	HERE_DOC = 4
};

enum e_type_char
{
	STANDARD,
	QUOTE,
	DOUBLE_Q,
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
	char				**out;
	char				**in;
	char				**arg;
	int					nb_arg;
	enum e_type_char	char_type;
	struct s_line		*next;
}				t_line;

typedef struct s_base
{
	char	**env;
	t_env	*envn;
	t_line	*lst;
	int		exit_code;
}			t_base;

/*----- Execution ------------------------------------------------------------*/
/* ft_exec.c */
int		ft_exec(t_base *base);

/* pipex.c & pipex_loop.c */
int		pipex(t_base *base);
void	pipe_execute_builtin(t_base *base);

int		pipe_loop(t_base *base, int *fd_in, int *fd_out);

/* execute command */
void	execute_command(t_base *base);

/* open_file.c */
int		open_infile(t_file *infile);
// int		open_outfile(t_file *outfile);
int		open_outfile(t_file *outfile, t_base *base);
int		ft_close(int fd1, int fd2, int exit_code);
void	ft_close_in_child(int fd1, int fd2);

/* redirection.c */
int		check_redirection(t_base *base, int *fd_in, int *fd_out);

/* utils_exec.c */
void	dup_input(int fd_in);
void	dup_output(int fd_out);
void	unlink_heredoc(void);

/*----- Builtin commands -----------------------------------------------------*/
int		ft_cd(t_base *base);
char	*get_path(t_base *base, char *destination);
t_env	*find_env_var(t_base *base, char *key);
char	*get_path_to_parentdir(t_base *base);
char	*get_pwd(void);
int		ft_echo(t_base *base);
int		ft_pwd(t_base *base);
int		ft_env(t_base *base);
void	ft_exit(t_base *base, int exit_status);
int		ft_export(t_base *base);
int		ft_unset(t_base *base);

/*----- Utils ----------------------------------------------------------------*/
/* error handling */
int		print_error(char *s1, char *s2, int exit_status);
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
int		write_char(int i, t_line *tmp, char *str, t_base *base);
int		write_in_file(int i, t_line *tmp, char *str);
int		write_out_file(int i, t_line *tmp, char *str);
int		cnt_param(char *str, t_line *line);
int		enter_quote_mode(char *str, int i, t_line *tmp);
int		assign_env(t_base *base, char **env);
void	ft_display_error(int i);
void	write_nod(int i, t_line *tmp, char *str, t_base *base);
char	*assign_value(char **split);
char	*translate_dollar(char *str, t_base *base, t_line *tmp, char *before);

# define RED "\033[1;31m"
# define MAGENTA "\033[1;35m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

#endif
