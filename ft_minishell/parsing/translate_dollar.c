/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:09:34 by dvo               #+#    #+#             */
/*   Updated: 2024/04/18 14:25:08 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_mall(char *s1, char *s2, int last_len)
{
	char			*res;
	unsigned int	res_len;
	unsigned int	i;
	unsigned int	j;

	res_len = ft_strlen(s1) + ft_strlen(s2) + last_len;
	res = ft_calloc(res_len + 1, sizeof(char));
	if (!res)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	free(s1);
	return (res);
}

char	*write_signal(char *str, t_base *base, char *before)
{
	char	*res;
	char	*nbr;
	int		i;

	i = 0;
	if (g_received_signal != 0)
	{
		base->exit_code = 128 + g_received_signal;
		g_received_signal = 0;
	}
	nbr = ft_itoa(base->exit_code);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 9)
		i++;
	res = ft_strjoin_mall(before, nbr, i);
	free(str);
	return (free(nbr), res);
}

char	*write_tilde(char *str, char *before)
{
	char	*res;
	char	*path;
	int		i;

	i = 0;
	path = ft_strdup(getenv(HOME));
	if (!path)
	{
		ft_free(str, 1);
		ft_free(path, 1);
		ft_free(before, 1);
		return (NULL);
	}
	if (str[++i] == '/')
	{
		printf("i = %d\n", i);
		i++;
		while (str[i] && str[i] != ' ' && str[i] != '<' \
		&& str[i] != '|' && str[i] != '>' && str[i] != 9)
			i++;
	}
	printf("i = %d\n", i);
	res = ft_strjoin_mall(before, path, i);
	free(str);
	free(path);
	return (res);
}

char	*ft_search(char *str, t_base *base, int last_len, char *before)
{
	t_env	*find;

	if (str[0] == '?')
		return (write_signal(str, base, before));
	if (!ft_strcmp(str, HOME))
	{
	// if (str[0] == '~')
		// return (write_tilde(str, before));
		free(str);
		return (ft_strjoin_mall(before, getenv(HOME), last_len));
	}
	find = base->envn;
	while (find && ft_strcmp(find->key, str) != 0)
		find = find->next;
	free(str);
	if (find)
		return (ft_strjoin_mall(before, find->value, last_len));
	if (last_len != 0)
		return (ft_strjoin_mall(before, NULL, last_len));
	if (before[0] == '\0')
		return (free(before), NULL);
	return (before);
}

char	*translate_dollar(char *str, t_base *base, char *before)
{
	char	*to_find;
	int		i;
	int		last_len;

	i = 0;
	last_len = 0;
	to_find = ft_calloc(strlen(str) + 1, sizeof(char));
	while (str[i] && str[i] != ' ' && str[i] != 9 && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 47 && str[i] != '=' && \
	str[i] != 34 && str[i] != 39 && str[i] != '$' && str[i] != '.' && str[i] != '/')
	{
		to_find[i] = str[i];
		i++;
	}
	i--;
	if (str[i] == 39 || str[i] == 34 || str[i] == '/' || str[i] == '$')
	{
		while (str[i] && str[i] != ' ' && str[i] != 9 && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>')
		{
			i++;
			last_len++;
		}
	}
	to_find[i] = '\0';
	printf("last len = %d\n", last_len);
	return (ft_search(to_find, base, last_len, before));
}
