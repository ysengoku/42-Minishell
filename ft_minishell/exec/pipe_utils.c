/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:05:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/25 09:22:42 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
		return (print_err(strerror(errno), "pipe", NULL, 1));
	return (0);
}

pid_t	ft_fork_pipe(int pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipe[IN]);
		close(pipe[OUT]);
		ft_perror("fork", 1);
	}
	return (pid);
}

void	pipe_child(t_base *base, t_line *node, int fd_in, int fd_out)
{
	int	fd[2];

	fd[IN] = fd_in;
	fd[OUT] = fd_out;
	pipe_execute_builtin(base, node, fd);
	dup_input(fd_in);
	dup_output(fd_out);
	execute_command(base, node);
}

void	pipe_execute_builtin(t_base *base, t_line *node, int fd[2])
{
	int	exit_code;

	exit_code = 0;
	if (!base->lst->arg[0])
		return ;
	if (ft_strcmp(node->arg[0], CD) == 0)
		exit_code = ft_cd(base, node, fd);
	else if (ft_strcmp(node->arg[0], ECHO) == 0)
		exit_code = ft_echo(node, fd);
	else if (ft_strcmp(node->arg[0], ENV) == 0)
		exit_code = ft_env(base, node, fd);
	else if (ft_strcmp(node->arg[0], EXIT) == 0)
		ft_exit(base, node, fd, true);
	else if (ft_strcmp(node->arg[0], EXPORT) == 0)
		exit_code = ft_export(base, node, fd);
	else if (ft_strcmp(node->arg[0], PWD) == 0)
		exit_code = ft_pwd(base, fd);
	else if (ft_strcmp(node->arg[0], UNSET) == 0)
		exit_code = ft_unset(base, node, fd);
	else
		return ;
	free_all_in_child(base);
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
	exit(exit_code);
}

void	free_all_in_child(t_base *base)
{
	free_base_content(base);
	free_envlist(base);
	free(base);
}
