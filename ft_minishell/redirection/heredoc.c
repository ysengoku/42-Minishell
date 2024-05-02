/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:31:12 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 15:03:26 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_delimiter(char *line, char *delimiter);
static int	stock_hdoc(t_base *base, char *line, int fd_heredoc, t_file *file);
static char	*ft_expand_heredoc(t_base *base, char *line);

int	get_heredoc_lines(t_base *base, t_file *file, int fd_heredoc)
{
	char	*line;
	int		check;

	set_heredoc_signal();
	while (1)
	{
		reset_heredoc();
		line = get_next_line(STDIN_FILENO);
		if (g_received_signal == SIGINT)
			return (free_heredoc(line, fd_heredoc, 2));
		if (!line && g_received_signal == 0)
		{
			print_warning(NULL_DELIM, file->filename, "')", 1);
			break ;
		}
		check = check_delimiter(line, file->filename);
		if (check == 0)
			break ;
		else if (check == -1)
			return (1);
		if (stock_hdoc(base, line, fd_heredoc, file) == 1)
			return (1);
	}
	return (free_heredoc(line, fd_heredoc, 0));
}

static int	check_delimiter(char *line, char *delimiter)
{
	char	*delimiter_checker;

	if (line[0] == '\n')
		return (1);
	delimiter_checker = ft_strtrim(line, "\n"); //ok
	if (!delimiter_checker)
	{
		print_err_malloc();
		return (ft_free((void *)line, -1));
	}
	if (ft_strcmp(delimiter_checker, delimiter) == 0)
		return (ft_free((void *)delimiter_checker, 0));
	return (ft_free((void *)delimiter_checker, 1));
}

static int	stock_hdoc(t_base *base, char *line, int fd_heredoc, t_file *file)
{
	char	*tmp;

	if (file->type == HERE_DOC && ft_strchr(line, '$') != NULL)
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
	expanded_line = ft_strdup(""); //ok
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
