/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:09:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/11 09:52:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_file *infile, t_base *base, int previous_fd)
{
	int	fd_in;

	ft_close(previous_fd, 0, 0);
	if (infile->type == INFILE)
	{
		fd_in = open(infile->filename, O_RDONLY);
		if (fd_in == -1)
		{
			base->exit_code = 1;
			ft_perror(infile->filename, 1);
		}
	}
	else
	{
		fd_in = open("here_doc", O_RDONLY);
		if (fd_in == -1)
		{
			base->exit_code = 1;
			ft_perror("here_doc", 1);
		}
	}
	return (fd_in);
}

int	open_outfile(t_file *outfile, t_base *base, int previous_fd)
{
	int	fd_out;

	ft_close(previous_fd, 0, 0);
	if (outfile->type == OUT_TRUNC)
		fd_out = open(outfile->filename,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(outfile->filename,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		if (errno != EACCES)
		{
			base->exit_code = 1;
			return (print_err(outfile->filename, strerror(errno), NULL, -2));
		}
	}
	return (fd_out);
}

int	ft_close(int fd1, int fd2, int exit_code)
{
	if (fd1 > 2)
		close (fd1);
	if (fd2 > 2)
		close (fd2);
	return (exit_code);
}

void	ft_close_in_child(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
