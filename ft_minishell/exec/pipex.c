/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/11 16:49:33 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		pipe_loop(t_base *base, t_line *node, int *fd_in, int *fd_out);
static pid_t	pipe_last_command(t_base *base, t_line *node, int fd_in);
static void		wait_children(t_base *base, pid_t lastchild_pid, int count);

int	pipex(t_base *base)
{
	int		fd[2];
	pid_t	lastchild_pid;
	int		count;
	t_line	*current_node;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = 0;
	count = 0;
	current_node = base->lst;
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

// ls | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
// ==527926== 8 bytes in 1 blocks are definitely lost in loss record 4 of 60
// ==527926==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==527926==    by 0x10F985: ft_calloc (in /home/yusengok/Documents/CommonCore/1-GitHub/42-Minishell/minishell)
// ==527926==    by 0x10D9BF: ft_recreate_str (count_lst.c:23)
// ==527926==    by 0x10DAA8: cnt_file (count_lst.c:40)
// ==527926==    by 0x10DBCB: skip_file (count_lst.c:72)
// ==527926==    by 0x10DD95: cnt_param (count_lst.c:111)
// ==527926==    by 0x10F30D: create_nod (create_nod.c:42)
// ==527926==    by 0x10D8E0: ft_chara_split (chara_split.c:68)
// ==527926==    by 0x1095F1: ft_minishell (main.c:33)
// ==527926==    by 0x10978A: main (main.c:81)

static int	pipe_loop(t_base *base, t_line *node, int *fd_in, int *fd_out)
{
	pid_t	child_pid;
	int		pipe[2];

	if (init_pipe(&pipe) == 1)
		return (EXIT_FAILURE);
	*fd_out = pipe[OUT];
	if (check_redirection(base, node, fd_in, fd_out) == 1 || !node->arg[0]
		|| pipe[OUT] == -1)
	{
		ft_close(pipe[OUT], *fd_in, 0);
		*fd_in = STDIN_FILENO;
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
	if (check_redirection(base, node, &fd_in, &fd[OUT]) == 1 || fd[OUT] == -1)
		return (ft_close(fd_in, fd[OUT], -1));
	if (!base->lst->arg[0])
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
	waitpid(lastchild_pid, &base->exit_code, 0);
	while (count-- > 0)
		wait(NULL);
}
