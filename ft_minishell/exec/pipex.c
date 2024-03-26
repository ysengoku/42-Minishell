/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/26 08:05:50 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	pipe_last_command(t_base *base, int fd_in);

int	pipex(t_base *base)
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
		if (pipe_loop(base, &fd[IN], &fd[OUT]) == 0)
			count++;
		base->lst = base->lst->next;
	}
	lastchild_pid = pipe_last_command(base, fd[IN]);
	if (lastchild_pid == -1)
		return (EXIT_FAILURE);
	count++;
	waitpid(lastchild_pid, &exit_status, 0);
	while (count-- > 0)
		wait(NULL);
	return (WEXITSTATUS(exit_status));
}

static pid_t	pipe_last_command(t_base *base, int fd_in)
{
	pid_t	lastchild_pid;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	check_redirection(base, &fd_in, &fd_out);
	lastchild_pid = fork();
	if (lastchild_pid == -1)
		return (ft_perror("fork", EXIT_FAILURE));
	if (lastchild_pid == 0)
	{
		dup_input(fd_in);
		dup_output(fd_out);
		pipe_execute_builtin(base);
		execute_command(base);
	}
	ft_close(fd_in, fd_out);
	return (lastchild_pid);
}

void	pipe_execute_builtin(t_base *base)
{
	int	exit_code;

	exit_code = 0;
	// if (ft_strcmp(base->lst->arg[0], CD) == 0)
	// 	ft_cd(); // to code
	if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		exit_code = ft_echo(base); // not complete yet
	else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
		exit_code = ft_env(base); // to code
	else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		ft_exit(base, 0); // to code
	else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		exit_code = ft_export(base); // to code
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		exit_code = ft_pwd(base); // not complete yet
	// else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
	// 	exit (ft_unset()); // to code
	else
		return ;
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	exit(exit_code);
}
