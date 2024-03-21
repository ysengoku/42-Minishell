/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 22:56:58 by dvo               #+#    #+#             */
/*   Updated: 2024/03/21 11:06:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_first_file(t_base *base)
{
	base->fd_one = open(base->av[1], O_RDONLY);
	if (base->fd_one == -1)
	{
		print_error(strerror(errno), base->av[1]);
		close((close(base->fd_one), base->fd_return[1]));
		exit(ft_free_all(NULL, base, 1));
	}
}

void	open_last_file(t_base *base)
{
	base->fd_two = open(base->av[base->ac - 1] \
	, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (base->fd_two == -1)
	{
		print_error(strerror(errno), base->av[base->ac - 1]);
		close((close(base->fd_two), base->fd_return[0]));
		exit(ft_free_all(NULL, base, 1));
	}
}
