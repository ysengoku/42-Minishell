/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/25 14:16:24 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_execve(t_base *base);
static pid_t	ft_fork(int fd_in, int fd_out);

int	ft_exec(t_base *base)
{
/*------ if no pipe -----*/
	if (base->lst->next == NULL)
		return (execute_single_command(base));
/*------ if pipe -----*/
	return (pipex(base));
	// free_base(base);
	// return (0);
}

int	execute_single_command(t_base *base)
{
	// if (ft_strcmp(base->lst->arg[0], CD) == 0)
	// 	ft_cd(); // to code
	if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		return (ft_echo(base)); // not complete yet
	// else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
	// 	return (ft_env()); // to code
	else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		return (ft_exit(base, EXIT_SUCCESS)); //-----> This func is coded for temporary use for now
	// else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
	// 	return (ft_export()); // to code
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		return (ft_pwd(base)); // not complete yet
	// else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
	// 	return (ft_unset()); // to code
	else
		return (ft_execve(base));
	return (0);
}

static int	ft_execve(t_base *base)
{
	int		fd[2];
	int		exit_status;
	pid_t	child_pid;

	exit_status = 0;
	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, &fd[IN], &fd[OUT]) == 1)
		return (EXIT_FAILURE);
	child_pid = ft_fork(fd[IN], fd[OUT]);
	if (child_pid == -1)
		return (EXIT_FAILURE);
	if (child_pid == 0)
	{
		dup_input(fd[IN]);
		dup_output(fd[OUT]);
		execute_command(base);
	}
	ft_close(fd[IN], fd[OUT]);
	waitpid(child_pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

static pid_t	ft_fork(int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error(strerror(errno), "fork", 1);
		ft_close(fd_in, fd_out);
	}
	return (pid);
}
