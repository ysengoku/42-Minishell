/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/18 16:29:46 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(t_base *base, t_line *node);

int	check_redirection(t_base *base, t_line *node, int *fd_in, int *fd_out)
{
	t_file	*current_file;

	if (check_heredoc(base, node) == 1)
		return (1);
	current_file = node->file;
	if (check_syntax(base, node) == 1)
		return (ft_close(*fd_in, *fd_out, 1));
	while (current_file && current_file->filename[0])
	{
		if (current_file->type == INFILE || current_file->type == HERE_DOC)
		{
			*fd_in = open_infile(current_file, base, *fd_in);
			if (*fd_in == -1)
				return (ft_close(*fd_in, *fd_out, 1));
		}
		else
		{
			*fd_out = open_outfile(current_file, base, *fd_out);
			if (*fd_out == -2)
				return (ft_close(*fd_in, *fd_out, 1));
		}
		current_file = current_file->next;
	}
	return (0);
}

static int	check_syntax(t_base *base, t_line *node)
{
	if (node->error_syntax == 1)
	{
		base->exit_code = 2;
		return (1);
	}
	return (0);
}
