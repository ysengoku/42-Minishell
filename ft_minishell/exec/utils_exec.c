/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:14:23 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 09:27:20 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipe(int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
	{
		ft_write(strerror(errno), "pipe");
		exit(EXIT_FAILURE);
	}
}

void	dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		ft_write(strerror(errno), "dup2");
		exit(EXIT_FAILURE);
	}
	ft_close(fd_in);
}

void	dup_output(int fd_out)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		ft_close(fd_out);
		ft_write(strerror(errno), "dup2");
		exit(EXIT_FAILURE);
	}
	ft_close(fd_out);
}

pid_t	ft_fork(int pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipe[READ_END]);
		close(pipe[WRITE_END]);
		ft_write(strerror(errno), "fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}
