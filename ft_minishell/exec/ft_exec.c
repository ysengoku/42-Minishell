/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/22 15:06:16 by yusengok         ###   ########.fr       */
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
	if (check_redir(base, node, &fd[IN], &fd[OUT]) == 1 || fd[OUT] == -1)
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
		return (ft_exit(base, node, fd, false));
	else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		return (ft_export(base, node, fd));
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		return (ft_pwd(base, fd));
	else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
		return (ft_unset(base, node, fd));
	return (execute_external_command(base, fd));
}

static int	execute_external_command(t_base *base, int fd[2])
{
	pid_t	child_pid;

	signal(SIGINT, handle_sigint_inexec);
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
	waitpid(child_pid, &base->exit_code, 0);
	if (WIFSIGNALED(base->exit_code))
	{
		g_received_signal = base->exit_code;
		write(1, "\n", 1);
	}
	else
		g_received_signal = 0;
	return (WEXITSTATUS(base->exit_code));
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
