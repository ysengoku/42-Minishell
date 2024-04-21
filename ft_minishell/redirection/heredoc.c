/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:31:12 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 18:13:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	stock_line_on_heredoc(t_base *base, char *line, int fd_heredoc,
				t_file *file);
static int	get_heredoc_lines(t_base *base, t_file *file, int fd_heredoc);
static char	*ft_expand_heredoc(t_base *base, char *line);

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
			fd_heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd_heredoc == -1)
			{
				perror("heredoc");
				base->exit_code = 1;
				return (1);
			}
			if (get_heredoc_lines(base, current, fd_heredoc) == 1)
			{
				base->exit_code = 1;
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

static int	get_heredoc_lines(t_base *base, t_file *file, int fd_heredoc)
{
	char				*line;
	char				*delimiter_checker;

	set_heredoc_signal();
	while (1)
	{
		// write(1, "> ", 2); ///// commented for tester
		line = get_next_line(STDIN_FILENO);
		delimiter_checker = ft_strtrim(line, "\n");
		if (g_received_signal != 0)
			break ;
		if (!delimiter_checker)
			return (print_err(NULL_DELIM, file->filename, "')", 1));
		if (ft_strcmp(delimiter_checker, file->filename) == 0)
			break ;
		if (stock_line_on_heredoc(base, line, fd_heredoc, file) == 1)
			return (ft_free((void *)delimiter_checker, 1));
		free(delimiter_checker);
		delimiter_checker = NULL;
	}
	close(fd_heredoc);
	ft_free((void *)line, 0);
	ft_free((void *)delimiter_checker, 0);
	return (0);
}

static int	stock_line_on_heredoc(t_base *base, char *line, int fd_heredoc,
	t_file *file)
{
	char	*tmp;

	if (file->type == 4 && ft_strchr(line, '$') != NULL)
	{
		tmp = line;
		line = ft_expand_heredoc(base, line);
		free(tmp);
		if (line == NULL)
			return (1);
		ft_putendl_fd(line, fd_heredoc);
	}
	else
		ft_putstr_fd(line, fd_heredoc);
	free(line);
	return (0);
}

static char	*ft_expand_heredoc(t_base *base, char *line)
{
	size_t	i;
	char	*expanded_line;
	char	*buf;

	i = 0;
	expanded_line = ft_strdup("");
	if (!expanded_line)
		return (handle_malloc_failure(NULL));
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] == '$')
			buf = get_expanded_str(&i, line, base);
		else
			buf = get_str(&i, line);
		if (!buf)
			return (handle_malloc_failure(expanded_line));
		expanded_line = append_buf(expanded_line, buf);
		if (!expanded_line)
			return (handle_malloc_failure(NULL));
	}
	return (expanded_line);
}
