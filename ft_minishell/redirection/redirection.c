/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/26 14:19:37 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(t_line *node);

int	check_redir(t_base *base, t_line *node, int *fd_in, int *fd_out)
{
	t_file	*current_file;

	if (check_heredoc(base, node) == 1)
		return (1);
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

int	check_redir_syntax(t_base *base, t_line *node)
{
	if (node->error_syntax == 1)
	{
		base->exit_code = 2;
		return (1);
	}
	return (0);
}

int	check_heredoc(t_base *base, t_line *node)
{
	int		fd_heredoc;
	t_file	*current;

	current = node->file;
	while (current)
	{
		if ((current->type == HERE_DOC || current->type == HERE_DOC_NO)
			&& current->filename[0])
		{
			fd_heredoc = open_heredoc(node);
			if (fd_heredoc == -1)
			{
				perror("heredoc");
				base->exit_code = 1;
				return (1);
			}
			base->exit_code = get_heredoc_lines(base, current, fd_heredoc);
			if (base->exit_code != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

static int	open_heredoc(t_line *node)
{
	char	*id;
	int		fd;

	id = ft_itoa(node->index);
	if (node->index != 0 && !id)
		return (-1);
	ft_strcpy(node->heredoc, HEREDOC);
	ft_strcat(node->heredoc, id);
	fd = open(node->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(id);
	return (fd);
}
