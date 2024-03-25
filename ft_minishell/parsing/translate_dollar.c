/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:09:34 by dvo               #+#    #+#             */
/*   Updated: 2024/03/25 03:03:18 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search(char *str, t_base *base)
{
	t_env *find;

	find = base->envn;
	while (find && ft_strncmp(find->key, str, ft_strlen(str)))
		find = find->next;
	if (find)
		return(find->value);
	return(NULL);
}

char	*translate_dollar(char *str, t_base *base)
{
	int	i;
	char	*to_find;
	char	*res;

	i = 0;
	while (str[i] != '$')
		i++;
	to_find = search(str + i, base);
	res = ft_calloc(ft_strlen(to_find) + i + 1, sizeof(char));
	
	return (res);
}