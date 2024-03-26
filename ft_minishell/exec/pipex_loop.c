/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 08:05:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/26 08:06:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		init_pipe(int (*pipefd)[2]);
static pid_t	ft_fork_pipex(int pipe[2]);
static void		pipe_child(t_base *base, int pipefd_in, int fd_in, int fd_out);

int	pipe_loop(t_base *base, int *fd_in, int *fd_out)
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
		return (1);
	}
	child_pid = ft_fork_pipex(pipe);
	if (child_pid == -1)
		return (EXIT_FAILURE);
	if (child_pid == 0)
		pipe_child(base, pipe[IN], *fd_in, *fd_out);
	close(pipe[OUT]);
	ft_close(*fd_in, *fd_out, 0);
	*fd_in = pipe[IN];
	return (0);
}

static int	init_pipe(int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
	{
		print_error(strerror(errno), "pipe", 1);
		return (EXIT_FAILURE);
	}
	return (0);
}

static pid_t	ft_fork_pipex(int pipe[2])
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

static void	pipe_child(t_base *base, int pipefd_in, int fd_in, int fd_out)
{
	close(pipefd_in);
	dup_input(fd_in);
	dup_output(fd_out);
	pipe_execute_builtin(base);
	execute_command(base);
}
