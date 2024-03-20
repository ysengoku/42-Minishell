/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:56:45 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 16:05:44 by yusengok         ###   ########.fr       */
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
int		ft_exec(t_base *base);
int		open_input_file(t_base *base, int i);
int		open_output_file(t_base *base, int i);
void	check_redirection(t_base *base, int *fd_in, int *fd_out);
void	init_pipe(int (*pipefd)[2]);
void	dup_input(int fd_in);
void	dup_output(int fd_out);
pid_t	ft_fork(int pipe[2]);
void	ft_execve(t_base *base);
void	ft_write(char *st1, char *st2);
void	ft_close(int fd1, int fd2);
void	ft_free_arr(char **arr);

 // To put into libft ?
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

/*----- Builtin commands -----------------------------------------------------*/
int		ft_echo(t_base *base);
int		ft_pwd(t_base *base);

#endif