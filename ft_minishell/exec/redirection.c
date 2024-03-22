/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/22 15:54:17 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(t_base *base, int *fd_in, int *fd_out)
{
	while (base->lst->file)
	{
		if (base->lst->file->type == INFILE
			|| base->lst->file->type == HERE_DOC)
		{
			ft_close(*fd_in, 0);
			*fd_in = open_infile(base);
		}
		else
		{
			ft_close(*fd_out, 0);
			*fd_out = open_outfile(base);
		}
		if (*fd_in == -1 || *fd_out == -1)
		{
			ft_close(*fd_in, *fd_out);
			return (EXIT_FAILURE);
		}
		base->lst->file = base->lst->file->next;
	}
	return (0);
}
