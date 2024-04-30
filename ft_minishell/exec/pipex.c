/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/30 20:23:46 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		init_value(int *fd_in, int *fd_out, int *count);
static int		pipe_loop(t_base *base, t_line *node, int *fd_in, int *fd_out);
static pid_t	pipe_last_command(t_base *base, t_line *node, int fd_in);
static void		wait_children(t_base *base, pid_t lastchild_pid, int count);

int	ft_pipex(t_base *base)
{
	int		fd[2];
	pid_t	lastchild_pid;
	int		count;
	t_line	*current_node;

	init_value(&fd[IN], &fd[OUT], &count);
	current_node = base->lst;
	set_exec_signal();
	printf("|%i|", g_received_signal);
	if (check_heredoc_p(base) == 1)
		return (base->exit_code);
	while (current_node->next && current_node->error_syntax == 0)
	{
		if (pipe_loop(base, current_node, &fd[IN], &fd[OUT]) != -1)
			count++;
		current_node = current_node->next;
	}
	lastchild_pid = pipe_last_command(base, current_node, fd[IN]);
	if (lastchild_pid == -1)
		return (base->exit_code);
	if (lastchild_pid == -2)
		return (0);
	count++;
	wait_children(base, lastchild_pid, count);
	return (WEXITSTATUS(base->exit_code));
}

static void	init_value(int *fd_in, int *fd_out, int *count)
{
	*fd_in = STDIN_FILENO;
	*fd_out = 0;
	*count = 0;
}

static int	pipe_loop(t_base *base, t_line *node, int *fd_in, int *fd_out)
{
	pid_t	child_pid;
	int		pipe[2];

	if (init_pipe(&pipe) == 1)
		return (EXIT_FAILURE);
	*fd_out = pipe[OUT];
	if (check_redir_p(base, node, fd_in, fd_out) == 1 || !node->arg[0]
		|| pipe[OUT] == -1)
	{
		ft_close(pipe[OUT], *fd_in, 0);
		*fd_in = pipe[IN];
		return (-1);
	}
	child_pid = ft_fork_pipex(pipe);
	if (child_pid == -1)
		return (-1);
	if (child_pid == 0)
	{
		close(pipe[IN]);
		pipe_child(base, node, *fd_in, *fd_out);
	}
	close(pipe[OUT]);
	ft_close(*fd_in, *fd_out, 0);
	*fd_in = pipe[IN];
	return (0);
}

static pid_t	pipe_last_command(t_base *base, t_line *node, int fd_in)
{
	pid_t	lastchild_pid;
	int		fd[2];

	fd[OUT] = STDOUT_FILENO;
	if (check_redir_p(base, node, &fd_in, &fd[OUT]) == 1 || fd[OUT] == -1)
		return (ft_close(fd_in, fd[OUT], -1));
	if (!node->arg[0])
		return (ft_close(fd_in, fd[OUT], -2));
	fd[IN] = fd_in;
	lastchild_pid = fork();
	if (lastchild_pid == -1)
	{
		ft_close(fd_in, fd[OUT], 1);
		return (ft_perror("fork", -1));
	}
	if (lastchild_pid == 0)
	{
		pipe_execute_builtin(base, node, fd);
		dup_input(fd_in);
		dup_output(fd[OUT]);
		execute_command(base, node);
	}
	return (ft_close(fd_in, fd[OUT], lastchild_pid));
}

static void	wait_children(t_base *base, pid_t lastchild_pid, int count)
{
	int	status;

	status = 0;
	waitpid(lastchild_pid, &base->exit_code, 0);
	while (count-- > 0)
		wait(&status);
	if (WIFSIGNALED(base->exit_code))
		g_received_signal = base->exit_code;
	else if (WIFSIGNALED(status))
		g_received_signal = status;
	else
		g_received_signal = 0;
		
	if (g_received_signal == SIGINT)
		write(1, "\n", 1);
}
