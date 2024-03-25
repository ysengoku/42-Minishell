/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:09:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/25 13:15:03 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_base *base)
{
	int	fd_in;

	if (base->lst->file->type == INFILE)
	{
		fd_in = open(base->lst->file->filename, O_RDONLY);
		if (fd_in == -1)
			ft_perror(base->lst->file->filename, 1);
	}
	else
	{
		fd_in = open("here_doc", O_RDONLY);
		if (fd_in == -1)
			ft_perror("here_doc", 1);
	}
	return (fd_in);
}

int	open_outfile(t_base *base)
{
	int	fd_out;

	if (base->lst->file->type == OUT_TRUNC)
		fd_out = open(base->lst->file->filename,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(base->lst->file->filename,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		ft_perror(base->lst->file->filename, 1);
	return (fd_out);
}

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 2)
		close (fd1);
	if (fd2 > 2)
		close (fd2);
}

void	ft_close_in_child(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}
