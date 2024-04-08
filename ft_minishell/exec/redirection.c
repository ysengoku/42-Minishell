/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/08 16:42:15 by yusengok         ###   ########.fr       */
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
		}
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
	char	*expanded;
	char	*tmp1;
	char	*tmp2;
			
	i = 0;
	expanded = ft_strdup("");
	tmp1 = ft_strdup(line);
	// malloc protection
	while (tmp1[i])
	{
		size_t	j;
		char	*res;
		char	*key;
		t_env	*target;

		i = 0;
		while (tmp1[i] != '$')
			i++;
		if (i > 0)
		{
			res = ft_calloc(i + 1, sizeof(char));
			ft_strlcpy(res, tmp1, i + 1);
		}
		else
			res = ft_strdup("");
			///// malloc protection
		j = ++i;
		while (tmp1[j] >= 'A' && tmp1[j] <= 'Z')
			j++;
		key = ft_calloc(j - i + 1, sizeof(char));
		///// malloc protection
		ft_strlcpy(key, tmp1 + i, j - i + 1);;
		target = find_env_var(base, key);
		tmp2 = res;
		if (target)
		{
			res = ft_strjoin(tmp2, target->value);
			free(tmp2);
			/// malloc protection
		}
		else
		{
			res = ft_calloc(ft_strlen(res) + ft_strlen(key) + 2, sizeof(char));
			/// malloc protection
			ft_strcpy(res, tmp2);
			ft_strcat(res, "$");
			ft_strcat(res, key);
			free(tmp2);
		}
		free(key);
		tmp2 = expanded;
		expanded = ft_strjoin(tmp2, res);
		free(tmp2);
		free(res);
		//malloc protection
		ft_strcpy(tmp1, tmp1 + j);
	}
	tmp2 = expanded;
	expanded = ft_strjoin(tmp2, "\n");
	free(tmp2);
	free(tmp1);
	// malloc protection
	return (expanded);
}
