/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/08 10:22:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		execute_single_command(t_base *base, t_line *node);
static int		execute_external_command(t_base *base, int fd[2]);
static pid_t	ft_fork(int fd_in, int fd_out);

int	ft_exec(t_base *base)
{
	if (base->lst->arg[0])
	{
		if (ft_strcmp(base->lst->arg[0], EXIT) != 0)
			base->exit_code = 0;
	}
	if (base->lst->next == NULL)
		return (execute_single_command(base, base->lst));
	return (pipex(base));
}

static int	execute_single_command(t_base *base, t_line *node)
{
	int		fd[2];

	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, node, &fd[IN], &fd[OUT]) == 1 || fd[OUT] == -1)
		return (base->exit_code);
	if (!base->lst->arg[0])
		return (0);
	if (ft_strcmp(base->lst->arg[0], CD) == 0)
		return (ft_cd(base, node, fd));
	else if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		return (ft_echo(base->lst, fd));
	else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
		return (ft_env(base, node, fd));
	else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		return (ft_exit(base, node, fd));
	else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		return (ft_export(base, fd));
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		return (ft_pwd(base, fd));
	else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
		return (ft_unset(base, node, fd));
	return (execute_external_command(base, fd));
}

static int	execute_external_command(t_base *base, int fd[2])
{
	int		exit_status;
	pid_t	child_pid;

	exit_status = 0;
	child_pid = ft_fork(fd[IN], fd[OUT]);
	if (child_pid == -1)
		return (EXIT_FAILURE);
	if (child_pid == 0)
	{
		dup_input(fd[IN]);
		dup_output(fd[OUT]);
		execute_command(base, base->lst);
	}
	ft_close(fd[IN], fd[OUT], 0);
	waitpid(child_pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

static pid_t	ft_fork(int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_perror("fork", EXIT_FAILURE);
		ft_close(fd_in, fd_out, 1);
	}
	return (pid);
}
