/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 08:11:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/03 14:19:47 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static pid_t	pipe_last_command(t_base *base, int fd_in);
static void		wait_children(t_base *base, pid_t lastchild_pid, int count);

int	pipex(t_base *base)
{
	int		fd[2];
	pid_t	lastchild_pid;
	int		count;
	t_line	*head;

	fd[IN] = STDIN_FILENO;
	fd[OUT] = 0;
	count = 0;
	head = base->lst;
	while (base->lst->next)
	{
		if (pipe_loop(base, &fd[IN], &fd[OUT]) != -1)
			count++;
		base->lst = base->lst->next;
	}
	lastchild_pid = pipe_last_command(base, fd[IN]);
	if (lastchild_pid == -1)
		return (1);
	if (lastchild_pid == -2)
		return (0);
	count++;
	wait_children(base, lastchild_pid, count);
	base->lst = head;
	return (WEXITSTATUS(base->exit_code));
}

static pid_t	pipe_last_command(t_base *base, int fd_in)
{
	pid_t	lastchild_pid;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (check_redirection(base, &fd_in, &fd_out) == 1)
		return (ft_close(fd_in, fd_out, -1));
	if (!base->lst->arg[0])
		return (ft_close(fd_in, fd_out, -2));
	lastchild_pid = fork();
	if (lastchild_pid == -1)
	{
		ft_close(fd_in, fd_out, 1);
		return (ft_perror("fork", -1));
	}
	if (lastchild_pid == 0)
	{
		dup_input(fd_in);
		dup_output(fd_out);
		pipe_execute_builtin(base);
		execute_command(base);
	}
	return (ft_close(fd_in, fd_out, lastchild_pid));
}

static void	wait_children(t_base *base, pid_t lastchild_pid, int count)
{
	waitpid(lastchild_pid, &base->exit_code, 0);
	while (count-- > 0)
		wait(NULL);
}

void	pipe_execute_builtin(t_base *base)
{
	int	exit_code;

	exit_code = 0;
	if (!base->lst->arg[0])
		return ;
	if (ft_strcmp(base->lst->arg[0], CD) == 0)
		exit_code = ft_cd(base);
	else if (ft_strcmp(base->lst->arg[0], ECHO) == 0)
		exit_code = ft_echo(base);
	else if (ft_strcmp(base->lst->arg[0], ENV) == 0)
		exit_code = ft_env(base);
	else if (ft_strcmp(base->lst->arg[0], EXIT) == 0)
		ft_exit(base, 0);
	else if (ft_strcmp(base->lst->arg[0], EXPORT) == 0)
		exit_code = ft_export(base);
	else if (ft_strcmp(base->lst->arg[0], PWD) == 0)
		exit_code = ft_pwd(base);
	else if (ft_strcmp(base->lst->arg[0], UNSET) == 0)
		exit_code = ft_unset(base);
	else
		return ;
	ft_close_in_child(STDIN_FILENO, STDOUT_FILENO);
	free_base_content(base);
	free_envlist(base);
	free(base);
	exit(exit_code);
}
