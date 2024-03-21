/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:24:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 11:41:28 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		execute_single_command(t_base *base);
static pid_t	ft_fork(t_base *base);

int	ft_exec(t_base *base)
{
/*------ if no pipe -----*/
	if (base->lst->next == NULL)
	{
		execute_builtin(base);
		execute_single_command(base);
	}
/*------ if pipe -----*/
	pipex(base);
	return (0);
}

void	execute_builtin(t_base *base)
{
	// if (ft_strcmp(base->lst->arg[0], CD) == 0)
	// 	ft_cd(); // to code
	if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		ft_echo(base); // not complete yet
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
	child_pid = ft_fork(base);
	if (child_pid == 0)
	{
		dup_input(fd[IN]);
		dup_output(fd[OUT]);
		execute_command(base);
	}
	waitpid(child_pid, &exit_status, 0);
	exit(WEXITSTATUS(exit_status));
}

static pid_t	ft_fork(t_base *base)
{
	pid_t	pid;

	(void)base; //----->temporary
	pid = fork();
	if (pid == -1)
	{
		print_error(strerror(errno), "fork");
		// free base
		exit(EXIT_FAILURE);
	}
	return (pid);
}
