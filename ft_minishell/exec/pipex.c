/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/04 11:24:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		pipe_loop(t_base *base, int *fd_in, int *fd_out);
static pid_t	pipe_last_command(t_base *base, int fd_in);
static void		wait_children(t_base *base, pid_t lastchild_pid, int count);

int	pipex(t_base *base)
{
	int		fd[2];
	pid_t	lastchild_pid;
	int		count;
	t_line	*head;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = 0;
	count = 0;
	head = base->lst;
	while (base->lst->next)
	{
		if (pipe_loop(base, &fd[IN], &fd[OUT]) != -1)
			count++;
		base->lst = base->lst->next;
	}
	lastchild_pid = pipe_last_command(base, fd[IN]);
	if (lastchild_pid == -1)
		return (1);
	if (lastchild_pid == -2)
		return (0);
	count++;
	wait_children(base, lastchild_pid, count);
	base->lst = head;
	return (WEXITSTATUS(base->exit_code));
}

static int	pipe_loop(t_base *base, int *fd_in, int *fd_out)
{
	pid_t	child_pid;
	int		pipe[2];

	if (init_pipe(&pipe) == 1)
		return (EXIT_FAILURE);
	*fd_out = pipe[OUT];
	if (check_redirection(base, fd_in, fd_out) == 1 || !base->lst->arg[0])
	{
		ft_close(pipe[OUT], *fd_in, 0);
		*fd_in = STDIN_FILENO;
		return (-1);
	}
	child_pid = ft_fork_pipex(pipe);
	if (child_pid == -1)
		return (-1);
	if (child_pid == 0)
		pipe_child(base, pipe[IN], *fd_in, *fd_out);
	close(pipe[OUT]);
	ft_close(*fd_in, *fd_out, 0);
	*fd_in = pipe[IN];
	return (0);
}

static pid_t	pipe_last_command(t_base *base, int fd_in)
{
	pid_t	lastchild_pid;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (check_redirection(base, &fd_in, &fd_out) == 1)
		return (ft_close(fd_in, fd_out, -1));
	if (!base->lst->arg[0])
		return (ft_close(fd_in, fd_out, -2));
	lastchild_pid = fork();
	if (lastchild_pid == -1)
	{
		ft_close(fd_in, fd_out, 1);
		return (ft_perror("fork", -1));
	}
	if (lastchild_pid == 0)
	{
		dup_input(fd_in);
		dup_output(fd_out);
		pipe_execute_builtin(base);
		execute_command(base);
	}
	return (ft_close(fd_in, fd_out, lastchild_pid));
}

static void	wait_children(t_base *base, pid_t lastchild_pid, int count)
{
	waitpid(lastchild_pid, &base->exit_code, 0);
	while (count-- > 0)
		wait(NULL);
}
