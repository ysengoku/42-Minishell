/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:09:34 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 18:10:59 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_mall(char *s1, char *s2, int last_len)
{
	char			*res;
	unsigned int	res_len;
	unsigned int	i;
	unsigned int	j;

	res_len = ft_strlen(s1) + ft_strlen(s2) + last_len;
	res = ft_calloc(res_len + 1, sizeof(char)); ///-----> Fixed
	if (!res)
	{
		free(s1);
		return (NULL);
	}
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

static char	*write_signal(char *str, t_base *base, char *before)
{
	char	*res;
	char	*nbr;
	int		i;

	i = 0;
	if (g_received_signal == SIGINT || g_received_signal == SIGQUIT)
	{
		base->exit_code = 128 + g_received_signal;
		g_received_signal = 0;
	}
	nbr = ft_itoa(base->exit_code); //ok
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 9)
		i++;
	res = ft_strjoin_mall(before, nbr, i);
	free(str);
	return (free(nbr), res);
}

static char	*ft_search(char *str, t_base *base, int last_len, char *before)
{
	t_env	*find;

	if (str[0] == '?')
		return (write_signal(str, base, before));
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

char	*translate_dollar(char *str, t_base *base, char *before, t_line *tmp)
{
	char	*to_find;
	int		i;
	int		last_len;

	i = 0;
	last_len = 0;
	to_find = ft_calloc(ft_strlen(str) + 1, sizeof(char)); // FIXED
	if (!to_find)
	{
		free (before);
		return (NULL);
	}
	while (str[i] && str[i] != ' ' && str[i] != 9 && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 47 && str[i] != '=' && \
	str[i] != 34 && str[i] != 39 && str[i] != '$' && str[i] != '.')
	{
		to_find[i] = str[i];
		i++;
	}
	if (str[i] == 39 || str[i] == 34 || str[i] == '/' || str[i] == '$' \
	|| tmp->char_type != STANDARD)
		last_len = count_last_len_dollars(str, i, tmp);
	to_find[i] = '\0';
	return (ft_search(to_find, base, last_len, before));
}

char	*translate_tilde(char *str, t_base *base, char *before)
{
	int		i;
	int		last_len;
	char	*res;

	(void) base;
	i = 1;
	last_len = 0;
	if (str[i] == '\0')
		res = ft_strjoin_mall(before, getenv(HOME), last_len);
	else if (str[i] == '/')
	{
		i++;
		last_len++;
		while (str[i++])
			last_len++;
		res = ft_strjoin_mall(before, getenv(HOME), last_len);
	}
	else
		res = ft_strdup(str); //ok
	return (res);
}
