/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:09:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 11:57:03 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(t_base *base, int i)
{
	int	fd_in;
	
	fd_in = open(base->lst->read[i], O_RDONLY);
	if (fd_in == -1)
	{
		ft_write(strerror(errno), base->lst->read[i]);
		// check if there is something free & close
		exit(EXIT_FAILURE);
	}
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
	{
		ft_write(strerror(errno), base->lst->write[i]);
		// check if there is something free & close
		exit(EXIT_FAILURE);
	}
	return (fd_out);
}

void	check_redirection(t_base *base, int *fd_in, int *fd_out)
{
	int	i;

	i = 0;
	if (base->lst->read[0] != NULL)
	{
		while (base->lst->read[i])
		{
			*fd_in = open_input_file(base, i);
			i++;
		}
	}
	i = 0;
	if (base->lst->write[0] != NULL)
	{
		while (base->lst->write[i])
		{
			*fd_out = open_output_file(base, i);
			i++;
		}
	}
}

void	ft_close(int fd)
{
	if (fd > 2)
		close (fd);
}
