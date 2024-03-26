/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:09:34 by dvo               #+#    #+#             */
/*   Updated: 2024/03/25 16:50:59 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search(char *str, t_base *base)
{
	t_env *find;

	find = base->envn;
	while (find && ft_strncmp(find->key, str, ft_strlen(str)) != 0)
		find = find->next;
	if (find)
		return(find->value);
	return(NULL);
}

char	*translate_dollar(char *str, t_base *base)
{
	int	i;
	char	*to_find;
	char	*before;
	char	*res;
	int		j;

	i = 0;
	while (str[i] != '$')
		i++;
	to_find = search(str + i + 1, base);
	if (!to_find)
		return (NULL);
	before = ft_calloc(i + 1, sizeof(char));
	j = 0;
	while (j < i)
	{
		before[j] = str[j];
		j++;
	}
	res = ft_strjoin(before, to_find);
	free(before);
	free(str);
	return (res);
}