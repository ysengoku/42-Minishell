/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:13:52 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/26 14:19:44 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc_p(t_base *base)
{
	t_line	*current;

	current = base->lst;
	while (current)
	{
		if (check_heredoc(base, current) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}

int	check_redir_p(t_base *base, t_line *node, int *fd_in, int *fd_out)
{
	t_file	*current_file;

	current_file = node->file;
	if (check_redir_syntax(base, node) == 1)
		return (ft_close(*fd_in, *fd_out, 1));
	while (current_file && current_file->filename[0])
	{
		if (current_file->type == INFILE || current_file->type == HERE_DOC
			|| current_file->type == HERE_DOC_NO)
		{
			*fd_in = open_infile(base, node, current_file, *fd_in);
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
