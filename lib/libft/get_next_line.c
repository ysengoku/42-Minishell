/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:07:28 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/06 08:24:00 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_line(int fd, char *buf);
static char	*ft_append_buf(char *stash, char *buf);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			line_len;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_read_line(fd, buf);
	if (!line)
		return (NULL);
	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		line_len = newline - line + 1;
		ft_strlcpy(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		line_len = ft_strlen(line);
		ft_strlcpy(buf, "", BUFFER_SIZE + 1);
	}
	line[line_len] = '\0';
	return (line);
}

static char	*ft_read_line(int fd, char *buf)
{
	ssize_t	read_size;
	char	*line;

	line = ft_strdup(buf);
	if (!line)
		return (NULL);
	read_size = 1;
	while (read_size > 0 && !ft_strchr(buf, '\n'))
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		buf[read_size] = '\0';
		if (read_size == 0 || read_size == -1)
			return (free(line), NULL);
		line = ft_append_buf(line, buf);
		if (!line)
			break ;
	}
	return (line);
}

static char	*ft_append_buf(char *line, char *buf)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(tmp, buf);
	free(tmp);
	tmp = NULL;
	if (!line)
		return (NULL);
	return (line);
}
