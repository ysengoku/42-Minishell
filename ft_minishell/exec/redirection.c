/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/09 11:57:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_heredoc(t_base *base, t_line *node);
static int	get_heredoc_lines(t_base *base, char *delimiter, int fd_heredoc);
char		*expand_heredoc_line(t_base *base, char *line);

int	check_redirection(t_base *base, t_line *node, int *fd_in, int *fd_out)
{
	t_file	*current_file;

	if (check_heredoc(base, node) == 1)
		return (print_err("heredoc", "A problem occured", NULL, 1));
	current_file = node->file;
	while (current_file)
	{
		if (current_file->type == INFILE || current_file->type == HERE_DOC)
		{
			ft_close(*fd_in, 0, 0);
			*fd_in = open_infile(current_file, base);
			if (*fd_in == -1)
				return (ft_close(*fd_in, *fd_out, 1));
		}
		else
		{
			ft_close(*fd_out, 0, 0);
			*fd_out = open_outfile(current_file, base);
			if (*fd_out == -2)
				return (ft_close(*fd_in, *fd_out, 1));
		}
		current_file = current_file->next;
	}
	return (0);
}

static int	check_heredoc(t_base *base, t_line *node)
{
	int		fd_heredoc;
	t_file	*current_file;

	current_file = node->file;
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
			if (get_heredoc_lines(base, current_file->filename, fd_heredoc) == 1)
			{
				base->exit_code = 1;
				return (1);
			}
		}
		current_file = current_file->next;
	}
	return (0);
}

static int	get_heredoc_lines(t_base *base, char *delimiter, int fd_heredoc)
{
	char	*line;
	char	*delimiter_check;
	char	*tmp;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		delimiter_check = ft_strtrim(line, "\n");
		if (!delimiter_check)
			return (print_err("minishell", "malloc failed", NULL, 1));
		if (ft_strcmp(delimiter_check, delimiter) == 0)
			break ;
		if (ft_strchr(line, '$') != NULL)
		{
			tmp = line;
			line = expand_heredoc_line(base, line);
			free(tmp);
			// malloc protection
			ft_putendl_fd(line, fd_heredoc);
		}
		else
			ft_putstr_fd(line, fd_heredoc);
		free(line);
		free(delimiter_check);
	}
	close(fd_heredoc);
	ft_free((void *)line, 0);
	free(delimiter_check);
	return (0);
}

char	*expand_heredoc_line(t_base *base, char *line)
{
	size_t	i;
	size_t	j;
	char	*expanded;
	char	*buf;
	char	*tmp;
	char	*key;
	t_env	*target;

	i = 0;
	expanded = ft_strdup(""); ///malloc
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		// case: $
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[j] && line[j] != ' ' && line[j] != '\t'&& line[j] != '$' && line[j] != '\n')
				j++;
			key = ft_calloc(j - i + 2, sizeof(char)); ///malloc
			ft_strlcpy(key, line + i, j - i + 1);
			target = find_env_var(base, key);
			if (target != NULL)
			{
				tmp = expanded;
				expanded = ft_strjoin(expanded, target->value); ///malloc
				free(tmp);
			}
			else
			{
				buf = ft_calloc(1 + ft_strlen(key) + 1, sizeof(char)); ///malloc
				ft_strcpy(buf, "$");
				ft_strcat(buf, key);
				tmp = expanded;
				expanded = ft_strjoin(expanded, buf); ///malloc
				free(tmp);
				free(buf);
			}
			free(key);
		}
		// case: non $
		else
		{
			j = i;
			while (line[j] && line[j] != '$' && line[j] != '\n')
				j++;
			buf = ft_calloc(j - i + 2, sizeof(char)); ///malloc
			ft_strlcpy(buf, line + i, j - i + 1);
			tmp = expanded;
			expanded = ft_strjoin(expanded, buf); ///malloc
			free(tmp);
			free(buf);
		}
		i = j;
	}
	return (expanded);
}
