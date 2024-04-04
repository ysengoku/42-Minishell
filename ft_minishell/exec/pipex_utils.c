/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:05:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/04 15:15:43 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
	{
		print_error(strerror(errno), "pipe", 1);
		return (EXIT_FAILURE);
	}
	return (0);
}

pid_t	ft_fork_pipex(int pipe[2])
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

void	pipe_child(t_base *base, int pipefd_in, int fd_in, int fd_out)
{
	close(pipefd_in);
	dup_input(fd_in);
	dup_output(fd_out);
	pipe_execute_builtin(base);
	execute_command(base);
}

void	pipe_execute_builtin(t_base *base)
{
	int	exit_code;

	exit_code = 0;
	if (!base->lst->arg[0])
		return ;
	if (ft_strcmp(base->lst->arg[0], CD) == 0)
		exit_code = ft_cd(base);
	else if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		exit_code = ft_echo(base);
	else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
		exit_code = ft_env(base);
	else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		ft_exit(base, 0);
	else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		exit_code = ft_export(base);
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		exit_code = ft_pwd(base);
	else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
		exit_code = ft_unset(base);
	else
		return ;
	free_all_in_child(base);
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	exit(exit_code);
}

void	free_all_in_child(t_base *base)
{
	free_base_content(base);
	free_envlist(base);
	free(base);
}
