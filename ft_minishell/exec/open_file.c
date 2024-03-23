/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:09:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/22 17:43:59 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_base *base)
{
	int	fd_in;

	fd_in = open(base->lst->file->filename, O_RDONLY);
	if (fd_in == -1)
		perror(base->lst->file->filename);
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
		perror(base->lst->file->filename);
	return (fd_out);
}

int	open_heredoc(t_base *base)
{
	int	fd_in;

	fd_in = open("here_doc", O_RDONLY);
	if (fd_in == -1)
		perror(base->lst->file->filename);
	return (fd_in);
}

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 2)
		close (fd1);
	if (fd2 > 2)
		close (fd2);
}
