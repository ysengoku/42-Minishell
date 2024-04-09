/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:13:43 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/09 14:38:03 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(t_base *base, char *line);

int	stock_line_on_heredoc(t_base *base, char *line, int fd_heredoc)
{
	char	*tmp;

	if (ft_strchr(line, '$') != NULL)
	{
		tmp = line;
		line = expand_heredoc_line(base, line);
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

static char	*expand_heredoc_line(t_base *base, char *line)
{
	size_t	i;
	size_t	j;
	char	*expanded;
	char	*buf;
	char	*tmp;
	char	key[NAME_MAX];
	t_env	*target;

	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
	{
		print_err("minishell", "malloc failed", NULL, 1);
		return (NULL);
	}
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] == '$')
		{
			i++;
			j = i;
			while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '$' && line[j] != '\n')
				j++;
			ft_strlcpy(key, line + i, j - i + 1);
			target = find_env_var(base, key);
			if (target != NULL)
			{
				tmp = expanded;
				expanded = ft_strjoin(expanded, target->value);
				free(tmp);
				if (!expanded)
				{
					print_err("minishell", "malloc failed", NULL, 1);
					return (NULL);
				}
			}
			else
			{
				buf = ft_calloc(1 + ft_strlen(key) + 1, sizeof(char));
				if (!buf)
				{
					ft_free((void *)expanded, 1);
					print_err("minishell", "malloc failed", NULL, 1);
					return (NULL);
				}
				ft_strcpy(buf, "$");
				ft_strcat(buf, key);
				tmp = expanded;
				expanded = ft_strjoin(expanded, buf);
				free(tmp);
				free(buf);
				if (!expanded)
				{
					ft_free((void *)key, 1);
					print_err("minishell", "malloc failed", NULL, 1);
					return (NULL);
				}
			}
		}
		else
		{
			j = i;
			while (line[j] && line[j] != '$' && line[j] != '\n')
				j++;
			buf = ft_calloc(j - i + 2, sizeof(char));
			if (!buf)
			{
				ft_free((void *)expanded, 1);
				print_err("minishell", "malloc failed", NULL, 1);
				return (NULL);
			}
			ft_strlcpy(buf, line + i, j - i + 1);
			tmp = expanded;
			expanded = ft_strjoin(expanded, buf);
			free(tmp);
			free(buf);
			if (!expanded)
			{
				print_err("minishell", "malloc failed", NULL, 1);
				return (NULL);
			}
		}
		i = j;
	}
	return (expanded);
}
