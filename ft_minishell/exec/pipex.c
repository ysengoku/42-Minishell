/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 10:18:03 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_pipe(int (*pipefd)[2]);
static pid_t	ft_fork_pipex(int pipe[2]);
static void		pipe_loop(t_base *base, int *fd_in, int *fd_out);
static pid_t	pipe_last_command(t_base *base, int fd_in);

void	pipex(t_base *base)
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
		pipe_loop(base, &fd[IN], &fd[OUT]);
		base->lst = base->lst->next;
		count++;
	}
	lastchild_pid = pipe_last_command(base, fd[IN]);
	count++;
	waitpid(lastchild_pid, &exit_status, 0);
	while (count-- > 0)
		wait(NULL);
	exit(WEXITSTATUS(exit_status));
}

static void	pipe_loop(t_base *base, int *fd_in, int *fd_out)
{
	pid_t	child_pid;
	int		pipe[2];

	init_pipe(&pipe);
	*fd_out = pipe[OUT];
	check_redirection(base, fd_in, fd_out);
	child_pid = ft_fork_pipex(pipe);
	if (child_pid == 0)
	{
		close(pipe[IN]);
		dup_input(*fd_in);
		dup_output(*fd_out);
		execute_command(base);
	}
	close(pipe[OUT]);
	ft_close(*fd_in, *fd_out);
	*fd_in = pipe[IN];
}

static pid_t	pipe_last_command(t_base *base, int fd_in)
{
	pid_t	lastchild_pid;
	int		pipe[2];
	int		fd_out;

	init_pipe(&pipe);
	fd_out = STDOUT_FILENO;
	check_redirection(base, &fd_in, &fd_out);
	lastchild_pid = ft_fork_pipex(pipe);
	if (lastchild_pid == 0)
	{
		close(pipe[IN]);
		dup_input(fd_in);
		dup_output(fd_out);
		execute_command(base);
	}
	ft_close(pipe[OUT], pipe[IN]);
	ft_close(fd_in, fd_out);
	return (lastchild_pid);
}

static void	init_pipe(int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
	{
		ft_write(strerror(errno), "pipe");
		exit(EXIT_FAILURE);
	}
}

static pid_t	ft_fork_pipex(int pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipe[IN]);
		close(pipe[OUT]);
		ft_write(strerror(errno), "fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
