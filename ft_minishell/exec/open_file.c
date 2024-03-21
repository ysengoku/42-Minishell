/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:09:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 11:06:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(t_base *base, int i)
{
	int	fd_in;

	fd_in = open(base->lst->read[i], O_RDONLY);
	if (fd_in == -1)
		print_error(strerror(errno), base->lst->read[i]);
	return (fd_in);
}

int	open_output_file(t_base *base, int i)
{
	int	fd_out;

	if (base->lst->append)
		fd_out = open(base->lst->write[i], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(base->lst->write[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		print_error(strerror(errno), base->lst->write[i]);
	return (fd_out);
}

void	ft_close(int fd1, int fd2)
{
	if (fd1 > 2)
		close (fd1);
	if (fd2 > 2)
		close (fd2);
}
