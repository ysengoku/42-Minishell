/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:13:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 08:53:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_keyend(char *line, size_t start);

char	*get_expanded_str(size_t *i, char *line, t_base *base)
{
	size_t	j;
	char	*buf;
	char	key[NAME_MAX];
	t_env	*target;

	(*i)++;
	j = get_keyend(line, *i);
	ft_strlcpy(key, line + *i, j - *i + 1);
	target = find_env_var(base, key);
	if (target != NULL)
	{
		buf = ft_strdup(target->value);
		if (!buf)
			return (handle_malloc_failure(NULL));
	}
	else
	{
		buf = ft_strdup("");
		if (!buf)
			return (handle_malloc_failure(NULL));
	}
	*i = j;
	return (buf);
}

static size_t	get_keyend(char *line, size_t start)
{
	size_t	end;

	end = start;
	while (line[end] && line[end] != ' ' && line[end] != '\t'
		&& line[end] != '$' && line[end] != '\n')
		end++;
	return (end);
}

char	*append_buf(char *expanded_line, char *buf)
{
	char	*appended_line;

	appended_line = ft_strjoin(expanded_line, buf);
	free(expanded_line);
	free(buf);
	return (appended_line);
}

char	*get_str(size_t *i, char *line)
{
	char	*buf;
	size_t	j;

	j = *i;
	while (line[j] && line[j] != '$' && line[j] != '\n')
		j++;
	buf = ft_calloc(j - *i + 2, sizeof(char));
	if (!buf)
		return (NULL);
	ft_strlcpy(buf, line + *i, j - *i + 1);
	*i = j;
	return (buf);
}

char	*handle_malloc_failure(char	*to_free)
{
	print_err("minishell", "malloc failed", NULL, 1);
	if (to_free != NULL)
		free(to_free);
	return (NULL);
}
