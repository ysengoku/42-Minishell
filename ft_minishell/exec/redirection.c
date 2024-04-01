/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/27 09:15:16 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_heredoc(t_base *base);
static int	get_heredoc_lines(char *delimiter, int fd_heredoc);

int	check_redirection(t_base *base, int *fd_in, int *fd_out)
{
	t_file	*current_file;

	if (check_heredoc(base) == 1)
		return (print_error("heredoc", "A problem occured", 1));
	current_file = base->lst->file;
	while (current_file)
	{
		if (current_file->type == INFILE || current_file->type == HERE_DOC)
		{
			ft_close(*fd_in, 0, 0);
			*fd_in = open_infile(base);
		}
		else
		{
			ft_close(*fd_out, 0, 0);
			*fd_out = open_outfile(base);
		}
		if (*fd_in == -1 || *fd_out == -1)
		{
			base->exit_code = 1;
			return (ft_close(*fd_in, *fd_out, 1));
		}
		current_file = current_file->next;
	}
	return (0);
}

static int	check_heredoc(t_base *base)
{
	int		fd_heredoc;
	t_file	*current_file;

	current_file = base->lst->file;
	while (current_file)
	{
		if (current_file->type == HERE_DOC)
		{
			fd_heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd_heredoc == -1)
			{
				perror("heredoc");
				base->exit_code = 1;
				return (1);
			}
			if (get_heredoc_lines(current_file->filename, fd_heredoc) == 1)
			{
				base->exit_code = 1;
				return (1);
			}
		}
		current_file = current_file->next;
	}
	return (0);
}

static int	get_heredoc_lines(char *delimiter, int fd_heredoc)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strtrim(line, "\n");
		if (!tmp)
			return (print_error("minishell", "malloc failed", 1));
		if (ft_strcmp(tmp, delimiter) == 0)
			break ;
		ft_putstr_fd(line, fd_heredoc);
		free(line);
		free(tmp);
	}
	close(fd_heredoc);
	if (line)
		free(line);
	free(tmp);
	return (0);
}
