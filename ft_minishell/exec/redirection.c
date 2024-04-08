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
	char	*tmp;
	char	*tmp2;
	int		i;

	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strtrim(line, "\n");
		if (!tmp)
			return (print_err("minishell", "malloc failed", NULL, 1));
		if (ft_strcmp(tmp, delimiter) == 0)
			break ;
		if (ft_strchr(line, '$') != NULL)
		{
			i = 0;
			while (line[i])
			{
				while (line[i] != '$')
					i++;
				tmp2 = ft_calloc(ft_strlen(line) - (ft_strlen(line) - i) + 1, sizeof(char));
				ft_strlcpy(tmp2, line, i + 1);
				// find value
				printf("tmp2 = %s\n", tmp2);
				line = translate_dollar(line + i, base, tmp2);
				printf("line = %s\n", line);
			}
		}
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

// Standard Error (stderr) redirection (2>): Redirects error messages from a command to a file or another command
// i.e. 2>/dev/null

// Outfile in non-existing dir
// i.e. >./outfiles/outfile01 --> "./outfiles/outfile01: No such file or directory'""