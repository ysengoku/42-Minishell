/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:16:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 15:29:34 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_base *base) 
{
	int	i;
	int	newline;
	int	fd_out;

	// Need to check all files (in/out) in order
	// If there is an open error, stop & return (1)
	if (base->lst->write[0] == NULL)
		fd_out = 1;
	else
	{
		i = 0;
		while (base->lst->write[i])
		{
			fd_out = open_output_file(base, i);
			i++;
			if (base->lst->write[i])
				ft_close(fd_out, 0);
		}
	}
	i = 1;
	newline = ft_strncmp(base->lst->arg[i], "-n", 2);
	if (newline == 0)
		i++;
	while (base->lst->arg[i])
	{
		write(fd_out, base->lst->arg[i], ft_strlen(base->lst->arg[i]));
		if (base->lst->arg[++i])
			write (fd_out, " ", 1);
	}
	if (newline)
		write (fd_out, "\n", 1);
	ft_close(fd_out, 0);
	if (base->lst->next)
		free_base(base);
	return (0);
}
