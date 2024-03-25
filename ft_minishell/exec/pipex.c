/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/25 13:22:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		init_pipe(t_base *base, int (*pipefd)[2]);
static pid_t	ft_fork_pipex(t_base *base, int pipe[2]);
static int		pipe_loop(t_base *base, int *fd_in, int *fd_out);
static pid_t	pipe_last_command(t_base *base, int fd_in);

int	pipex(t_base *base)
{
	int		fd[2];
	pid_t	lastchild_pid;
	int		exit_status;
	int		count;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = 0;
	count = 0;
	exit_status = 0;
	while (base->lst->next)
	{
		if (pipe_loop(base, &fd[IN], &fd[OUT]) == 0)
			count++;
		base->lst = base->lst->next;
	}
	lastchild_pid = pipe_last_command(base, fd[IN]);
	if (lastchild_pid == -1)
		return (EXIT_FAILURE);
	count++;
	waitpid(lastchild_pid, &exit_status, 0);
	while (count-- > 0)
		wait(NULL);
	return (WEXITSTATUS(exit_status));
}

static int	init_pipe(t_base *base, int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
	{
		print_error(strerror(errno), "pipe", 1);
		if (base->lst->next)
			free_base(base);
		return (EXIT_FAILURE);
	}
	return (0);
}

static pid_t	ft_fork_pipex(t_base *base, int pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipe[IN]);
		close(pipe[OUT]);
		print_error(strerror(errno), "fork", 1);
		if (base->lst->next)
			free_base(base);
	}
	return (pid);
}

static int	pipe_loop(t_base *base, int *fd_in, int *fd_out)
{
	pid_t	child_pid;
	int		pipe[2];

	if (init_pipe(base, &pipe) == 1)
		return (EXIT_FAILURE);
	*fd_out = pipe[OUT];
	if (check_redirection(base, fd_in, fd_out) == 1)
	{
		ft_close(pipe[OUT], *fd_in);
		*fd_in = STDIN_FILENO;
		return (1);
	}
	child_pid = ft_fork_pipex(base, pipe);
	if (child_pid == -1)
		return (EXIT_FAILURE);
	if (child_pid == 0)
	{
		close(pipe[IN]);
		dup_input(*fd_in);
		dup_output(*fd_out);
		// if builtin --> execute builtin_pipex
		execute_command(base);
	}
	close(pipe[OUT]);
	ft_close(*fd_in, *fd_out);
	*fd_in = pipe[IN];
	return (0);
}

static pid_t	pipe_last_command(t_base *base, int fd_in)
{
	pid_t	lastchild_pid;
	int		pipe[2];
	int		fd_out;

	if (init_pipe(base, &pipe) == 1)
		return (EXIT_FAILURE);
	fd_out = STDOUT_FILENO;
	check_redirection(base, &fd_in, &fd_out);
	lastchild_pid = ft_fork_pipex(base, pipe);
	if (lastchild_pid == -1)
		return (EXIT_FAILURE);
	if (lastchild_pid == 0)
	{
		close(pipe[IN]);
		dup_input(fd_in);
		dup_output(fd_out);
		// if builtin --> execute builtin_pipex
		execute_command(base);
	}
	ft_close(pipe[OUT], pipe[IN]);
	ft_close(fd_in, fd_out);
	return (lastchild_pid);
}
