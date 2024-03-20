/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 16:31:18 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_pipe_commands(t_base *base);
static void		pipe_loop(t_base *base, int *fd_in, int *fd_out);
static pid_t	pipe_last_command(t_base *base, int fd_in);
static void		execute_single_command(t_base *base);

int	ft_exec(t_base *base)
{
/*------ if no pipe -----*/
	if (base->lst->next == NULL)
	{
		// if (ft_strcmp(base->lst->arg[0], CD) == 0)
		// 	ft_cd(); // to code
		if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
			ft_echo(base->lst->arg, base->lst->write[0], base->lst->append); // not complete yet
		// else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
		// 	ft_env(); // to code
		// else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		// 	ft_exit(); // to code
		// else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		// 	ft_export(); // to code
		else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
			ft_pwd(base); // not complete yet
		// else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
		// 	ft_unset(); // to code
		else
			execute_single_command(base);
	}
/*------ if pipe -----*/
	execute_pipe_commands(base);
	return (0);
}

static void	execute_pipe_commands(t_base *base)
{
	int		fd[2];
	pid_t	lastchild_pid;
	int		exit_status;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = 0;
	while (base->lst->next)
	{
		pipe_loop(base, &fd[IN], &fd[OUT]);
		base->lst = base->lst->next;
	}
	lastchild_pid = pipe_last_command(base, fd[IN]);
/*wait children -----------------------------------*/
	exit_status = 0;
	waitpid(lastchild_pid, &exit_status, 0);
	// loop 'wait' for the number of pipe times 
	exit(WEXITSTATUS(exit_status));
}

static void	pipe_loop(t_base *base, int *fd_in, int *fd_out)
{
	pid_t	child_pid;
	int		pipe[2];

	init_pipe(&pipe);
	*fd_out = pipe[OUT];
	check_redirection(base, fd_in, fd_out);
	child_pid = ft_fork(pipe);
	if (child_pid == 0)
	{
		close(pipe[IN]);
		dup_input(*fd_in);
		dup_output(*fd_out);
		ft_execve(base);
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
	lastchild_pid = ft_fork(pipe);
	if (lastchild_pid == 0)
	{
		close(pipe[IN]);
		dup_input(fd_in);
		dup_output(fd_out);
		ft_execve(base);
	}
	ft_close(pipe[OUT], pipe[IN]);
	ft_close(fd_in, fd_out);
	return (lastchild_pid);
}

static void	execute_single_command(t_base *base)
{
	int		fd[2];
	int		exit_status;
	pid_t	child_pid;

	exit_status = 0;
	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	check_redirection(base, &fd[IN], &fd[OUT]);
	child_pid = fork();
	if (child_pid == -1)
	{
		ft_write(strerror(errno), NULL);
		// free all here
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		dup_input(fd[IN]);
		dup_output(fd[OUT]);
		ft_execve(base);
	}
	waitpid(child_pid, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}
