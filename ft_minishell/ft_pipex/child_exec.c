/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:48:59 by dvo               #+#    #+#             */
/*   Updated: 2024/02/28 19:54:16 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_pipex_child(char *str, t_base *base)
{
	char	**ar;

	ar = NULL;
	if (ft_strchr(str, '/') == 1)
		attribute_folder(base, str);
	ar = create_ar(str, base);
	if (!ar)
		exit(ft_free_all(ar, base, 127));
	execve(base->ag1, ar, base->env);
	ft_putnbr_fd(errno, 2);
	ft_write(strerror(errno), ar[0]);
	exit(ft_free_all(ar, base, 126));
}

void	first_child(t_base *base)
{
	pid_t	child;

	child = fork();
	if (child == -1)
	{
		ft_fprintf(2, "%s\n", strerror(errno));
		exit(ft_free_all(NULL, base, 1));
	}
	if (child == 0)
	{
		close(base->fd_return[0]);
		open_first_file(base);
		if (dup2(base->fd_one, 0) == -1 || dup2(base->fd_return[1], 1) == -1)
		{
			close((close(base->fd_one), base->fd_return[1]));
			exit(ft_free_all(NULL, base, 1));
		}
		close((close(base->fd_one), base->fd_return[1]));
		ft_pipex_child(base->av[2], base);
	}
	else
	{
		close(base->fd_return[1]);
		///waitpid(child, &base->status, 0);
	}
}

void	nxt_child_loop(t_base *base, int fd2[2], int fd[2], int i)
{
	close(fd2[0]);
	if (dup2(fd[0], 0) == -1 || dup2(fd2[1], 1) == -1)
		exit(ft_free_all(NULL, base, 1));
	close((close(fd[0]), fd2[1]));
	ft_pipex_child(base->av[i], base);
}

void	child_loop(t_base *base, int fd[2], int i)
{
	int		fd2[2];
	pid_t	child;

	if (pipe(fd2) == -1)
	{
		ft_fprintf(2, "%s\n", strerror(errno));
		exit(ft_free_all(NULL, base, 1));
	}
	child = fork();
	if (child == -1)
	{
		ft_fprintf(2, "%s\n", strerror(errno));
		exit(ft_free_all(NULL, base, 1));
	}
	if (child == 0)
		nxt_child_loop(base, fd2, fd, i);
	else
	{
		close((close(fd2[1]), fd[0]));
		//waitpid(child, &(base->status), 0);
		*(base->fd_return) = *fd2;
	}
}

void	last_child(t_base *base)
{
	int	child;

	child = fork();
	if (child == -1)
	{
		ft_fprintf(2, "%s\n", strerror(errno));
		exit(ft_free_all(NULL, base, 1));
	}
	if (child == 0)
	{
		open_last_file(base);
		if (dup2(base->fd_two, 1) == -1 || dup2(base->fd_return[0], 0) == -1)
			exit(ft_free_all(NULL, base, 1));
		close((close(base->fd_two), base->fd_return[0]));
		ft_pipex_child(base->av[base->ac - 2], base);
	}
	else
	{
		close(base->fd_return[0]);
		//waitpid(child, &base->status, 0);
	}
}
