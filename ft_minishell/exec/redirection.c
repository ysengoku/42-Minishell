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
	if (base->lst->file != NULL)
	{
		while (base->lst->file)
		{
			if (base->lst->file->type == INFILE || base->lst->file->type == HERE_DOC)
			{
				ft_close(*fd_in, 0);
				*fd_in = open_infile(base);
			}
			else
			{
				ft_close(*fd_out, 0);
				if (base->lst->file->type == OUT_TRUNC)
					*fd_out = open_outfile_trunc(base);
				else
					*fd_out = open_outfile_append(base);
			}
			if (*fd_in == -1 || *fd_out == -1)
			{
				ft_close(*fd_in, *fd_out);
				return (1);
			}
			base->lst->file = base->lst->file->next;
		}
	}
	return (0);
}

// int	check_redirection(t_base *base, int *fd_in, int *fd_out)
// {
// 	int	i;

// 	i = 0;
// 	if (base->lst->read[0] != NULL)
// 	{
// 		while (base->lst->read[i])
// 		{
// 			*fd_in = open_infile(base, i++);
// 			if (*fd_in == -1)
// 			{
// 				if (base->lst->next == NULL)
// 					free_base(base);
// 				return (EXIT_FAILURE);
// 			}
// 			if (base->lst->read[i])
// 				ft_close(*fd_in, 0);
// 		}
// 	}
// 	i = 0;
// 	if (base->lst->write[0] != NULL)
// 	{
// 		while (base->lst->write[i])
// 		{
// 			*fd_out = open_outfile_trunc(base, i++);
// 			if (*fd_out == -1)
// 			{
// 				ft_close(*fd_in, 0);
// 				if (base->lst->next == NULL)
// 					free_base(base);
// 				return (EXIT_FAILURE);
// 			}
// 			if (base->lst->write[i])
// 				ft_close(*fd_out, 0);
// 		}
// 	}
// 	return (0);
// }
