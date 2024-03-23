/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/23 19:51:06 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		execute_single_command(t_base *base);
static pid_t	ft_fork(t_base *base);

int	ft_exec(t_base *base)
{
/*------ if no pipe -----*/
	if (base->lst->next == NULL)
	{
		// if built in
		return (execute_builtin(base));
		//else
		return (execute_single_command(base));
	}
/*------ if pipe -----*/
	return (pipex(base));
	free_base(base);
	return (0);
}

int	execute_builtin(t_base *base)
{
	// if (ft_strcmp(base->lst->arg[0], CD) == 0)
	// 	ft_cd(); // to code
	if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		return (ft_echo(base)); // not complete yet
	// else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
	// 	return (ft_env()); // to code
	else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		ft_exit(base, 0); // to code
	// else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
	// 	return (ft_export()); // to code
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		return (ft_pwd(base)); // not complete yet
	// else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
	// 	return (ft_unset()); // to code
	else
		return (execute_single_command(base));
	// return (0);
	return (0);
}

static int	execute_single_command(t_base *base)
{
	int		fd[2];
	int		exit_status;
	pid_t	child_pid;

	exit_status = 0;
	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, &fd[IN], &fd[OUT]) == 1)
		return (EXIT_FAILURE);
	// printf("in: %d\n", fd[IN]);
	// printf("out: %d\n", fd[OUT]);
	child_pid = ft_fork(base);
	if (child_pid == -1)
		return (EXIT_FAILURE);
	if (child_pid == 0)
	{
		// issue with stdin & stdout ??
		dup_input(fd[IN]);
		dup_output(fd[OUT]);
		execute_command(base);
	}
	waitpid(child_pid, &exit_status, 0);
	return (WEXITSTATUS(exit_status));
}

static pid_t	ft_fork(t_base *base)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error(strerror(errno), "fork");
		if (base->lst->next == NULL)
			free_base(base);
	}
	return (pid);
}
