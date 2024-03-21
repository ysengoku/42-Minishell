/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 10:26:41 by yusengok         ###   ########.fr       */
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
# include "libft.h"
// # include "ft_printf.h"
// # include "../lib/libft/libft.h"
// # include "../lib/ft_fprintf/ft_printf.h"

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

typedef struct s_line
{
	char			**read;
	char			**write;
	bool			append;
	char			**arg;
	struct s_line	*next;
}			t_line;

typedef struct s_base
{
	char	**env;
	// t_env	*env;
	t_line	*lst;
}			t_base;

/*----- Execution ------------------------------------------------------------*/
/* ft_exec.c */
int		ft_exec(t_base *base);
void	execute_builtin(t_base *base);
// static void	execute_single_command(t_base *base);

/* pipex.c */
void	pipex(t_base *base);
// static void		init_pipe(int (*pipefd)[2]);
// static void		pipe_loop(t_base *base, int *fd_in, int *fd_out);
// static pid_t	pipe_last_command(t_base *base, int fd_in);

/* execute command */
void	execute_command(t_base *base);
// static char	*get_pathname(t_base *base);
// static char	**extract_path(t_base *base);

/* open_file.c */
int		open_input_file(t_base *base, int i);
int		open_output_file(t_base *base, int i);
void	ft_close(int fd1, int fd2);

/* redirection.c */
void	check_redirection(t_base *base, int *fd_in, int *fd_out);
// static void	check_redirection_in(t_base *base, int *fd_in);
// static void	check_redirection_out(t_base *base, int *fd_in, int *fd_out);

/* utils_exec.c */
void	dup_input(int fd_in);
void	dup_output(int fd_out);
/* utils */
void	ft_write(char *st1, char *st2);
void	ft_free_arr(char **arr);

 // To put into libft ?
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

/*----- Builtin commands -----------------------------------------------------*/
void	ft_echo(t_base *base);
void	ft_pwd(t_base *base);

#endif