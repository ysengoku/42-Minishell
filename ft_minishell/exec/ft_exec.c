/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 11:58:45 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_pipe_commands(t_base *base);
static void	execute_single_command(t_base *base);

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
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	pid_t	child_pid;

	fd_in = 0;
/*pipe--------------------------------------------*/
	while (base->lst->next)
	{
		init_pipe(&pipe);
		// if (base->lst->read[0] != NULL)
		// 	fd_in = open_input_file(base);
		// if (base->lst->write[0] != NULL)
		// 	fd_out = open_output_file(base);
		// else
		fd_out = pipe[WRITE_END];
		check_redirection(base, &fd_in, &fd_out);

		child_pid = ft_fork(pipe);
		if (child_pid == 0)
		{
			close(pipe[READ_END]);
			dup_input(fd_in);
			dup_output(fd_out);
			if (execve(base->lst->arg[0], base->lst->arg, base->env) == -1)
			{
				ft_write(strerror(errno), "execve");
				// free all here
				exit(EXIT_FAILURE);
			}
		}
		close(pipe[WRITE_END]);
		ft_close(fd_in);
		fd_in = pipe[READ_END];
		base->lst = base->lst->next;
	}
	
/*last pipe----------------------------------------*/
	pid_t	lastchild_pid;

	init_pipe(&pipe);
	fd_out = 1;
	check_redirection(base, &fd_in, &fd_out);
		
	lastchild_pid = ft_fork(pipe);
	if (lastchild_pid == 0)
	{
		close(pipe[READ_END]);
		dup_input(fd_in);
		dup_output(fd_out);
		if (execve(base->lst->arg[0], base->lst->arg, base->env) == -1)
		{
			ft_write(strerror(errno), "execve");
			// free all here
			exit(EXIT_FAILURE);
		}
	}
	close(pipe[WRITE_END]);
	close(pipe[READ_END]);
	ft_close(fd_in);
	
	/*--- wait children ---*/
	int	exit_status;
	exit_status = 0;
	waitpid(lastchild_pid, &exit_status, 0);
	// loop 'wait' for the number of pipe times 
	exit(WEXITSTATUS(exit_status));
}

static void	execute_single_command(t_base *base)
{
	int		fd_in;
	int		fd_out;
	int		exit_status;
	pid_t	child_pid;
	
	exit_status = 0;
	fd_in = 0;
	fd_out = 1;
	check_redirection(base, &fd_in, &fd_out);
	child_pid = fork();
	if (child_pid == -1)
	{
		ft_write(strerror(errno), NULL);
		// free all here
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		dup_input(fd_in);
		dup_output(fd_out);
		if (execve(base->lst->arg[0], base->lst->arg, base->env) == -1)
		{
			ft_write(strerror(errno), "execve");
			// free all here
			exit(EXIT_FAILURE);
		}
	}
	waitpid(child_pid, &exit_status, 0);
	// free something ?
	exit(WEXITSTATUS(exit_status));
}
