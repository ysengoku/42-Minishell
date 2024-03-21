/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 10:25:31 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_redirection_in(t_base *base, int *fd_in);
static void	check_redirection_out(t_base *base, int *fd_in, int *fd_out);

void	check_redirection(t_base *base, int *fd_in, int *fd_out)
{
	check_redirection_in(base, fd_in);
	check_redirection_out(base, fd_in, fd_out);
}

static void	check_redirection_in(t_base *base, int *fd_in)
{
	int	i;

	i = 0;
	if (base->lst->read[0] != NULL)
	{
		while (base->lst->read[i])
		{
			*fd_in = open_input_file(base, i++);
			if (base->lst->read[i])
				ft_close(*fd_in, 0);
		}
		if (*fd_in == -1)
		{
			// free
			exit(1);
		}
	}
}

static void	check_redirection_out(t_base *base, int *fd_in, int *fd_out)
{
	int	i;
	
	i = 0;
	if (base->lst->write[0] != NULL)
	{
		while (base->lst->write[i])
		{
			*fd_out = open_output_file(base, i++);
			if (base->lst->write[i])
				ft_close(*fd_out, 0);
		}
		if (*fd_out == -1)
		{
			// free
			ft_close(*fd_in, 0);
			exit(1);
		}
	}
}

// Once a file is opened, it keeps open-flag(trunc or append) even for next pipes
// example:
// < in cat | grep Hello >> out | wc -l > out
// < in cat | grep Hello > out | wc -l >> out