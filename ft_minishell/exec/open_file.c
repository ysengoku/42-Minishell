/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:09:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/19 15:45:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(t_base *base)
{
	int	fd_in;
	
	fd_in = open(base->lst->read, O_RDONLY);
	if (fd_in == -1)
	{
		ft_write(strerror(errno), base->lst->read);
		// check if there is something free
		exit(1);
	}
	return (fd_in);
}

int	open_output_file(t_base *base)
{
	int	fd_out;
	
	fd_out = open(base->lst->write, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_write(strerror(errno), base->lst->write);
		// check if there is something free
		exit(1);
	}
	return (fd_out);
}
