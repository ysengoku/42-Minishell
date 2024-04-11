/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:09:34 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 00:37:08 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_mall(char *s1, char *s2, int last_len);

char	*write_signal(char *str, t_base *base, char *before)
{
	char	*res;
	char	*nbr;
	int		i;

	i = 0;
	nbr = ft_itoa(base->exit_code);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 9)
		i++;
	res = ft_strjoin_mall(before, nbr, i);
	free(str);
	return (free(nbr), res);
}

char	*ft_search(char *str, t_base *base, int last_len, char *before)
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
	return (before);
}

char	*ft_strjoin_mall(char *s1, char *s2, int last_len)
{
	char			*res;
	unsigned int	res_len;
	unsigned int	i;
	unsigned int	j;

	res_len = ft_strlen(s1) + ft_strlen(s2) + last_len;
	res = ft_calloc(res_len + 1, sizeof(char));
	if (!res)
		return (NULL);
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

char	*translate_dollar(char *str, t_base *base, char *before)
{
	char	*to_find;
	int		i;
	int		last_len;

	i = 0;
	last_len = 0;
	to_find = ft_calloc(strlen(str) + 1, sizeof(char));
	while (str[i] && str[i] != ' ' && str[i] != 9 && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 47 && \
	str[i] != 34 && str[i] != 39 && str[i] != '$' && str[i] != '.')
	{
		to_find[i] = str[i];
		i++;
	}
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
	return (ft_search(to_find, base, last_len, before));
}
