/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/02 10:20:39 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		execute_single_command(t_base *base);
static int		execute_external_command(t_base *base);
static pid_t	ft_fork(int fd_in, int fd_out);

int	ft_exec(t_base *base)
{
	base->exit_code = 0;
	if (base->lst->next == NULL)
		return (execute_single_command(base));
	return (pipex(base));
}

static int	execute_single_command(t_base *base)
{
	if (base->lst->arg[0])
	{
		if (ft_strcmp(base->lst->arg[0], CD) == 0)
			return (ft_cd(base));
		if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
			return (ft_echo(base));
		else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
			return (ft_env(base));
		else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
			ft_exit(base, 0);
		else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
			return (ft_export(base));
		else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
			return (ft_pwd(base));
		else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
			return (ft_unset(base));
	}
	return (execute_external_command(base));
}

static int	execute_external_command(t_base *base)
{
	int		fd[2];
	int		exit_status;
	pid_t	child_pid;

	exit_status = 0;
	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, &fd[IN], &fd[OUT]) == 1)
		return (1);
	if (fd[OUT] == -1)
		return (base->exit_code);
	if (base->lst->arg[0] == NULL)
		return (1);
	child_pid = ft_fork(fd[IN], fd[OUT]);
	if (child_pid == -1)
		return (EXIT_FAILURE);
	if (child_pid == 0)
	{
		dup_input(fd[IN]);
		dup_output(fd[OUT]);
		execute_command(base);
	}
	ft_close(fd[IN], fd[OUT], 0);
	waitpid(child_pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
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

// exit code
// Success -----> 0
// No such file or directory -----> 1
// command not found -----> 127
// command found but not executable -----> 126

// All builtins return an exit status of 2 to indicate incorrect usage, 
// generally invalid options or missing arguments. 
