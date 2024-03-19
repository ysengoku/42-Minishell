/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:14:23 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/19 14:17:31 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write(char *st1, char *st2)
{
	write(2, st1, ft_strlen(st1));
	if (st2)
	{
		write(2, ": ", 2);
		write(2, st2, ft_strlen(st2));
	}
	write(2, "\n", 1);
}

void	init_pipe(int (*pipefd)[2])
{
	if (pipe((*pipefd)) == -1)
		ft_perror("pipe");
}

void	dup_input(int fd_in)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
		ft_perror("dup2");
	close(fd_in);
}

void	dup_output(int fd_out)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		ft_close_and_perror(fd_out, "dup2", EXIT_FAILURE);
	close(fd_out);
}

pid_t	ft_fork(int pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close(pipe[READ_END]);
		close(pipe[WRITE_END]);
		ft_write(strerror(errno), NULL);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
