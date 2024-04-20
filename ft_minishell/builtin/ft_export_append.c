/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 18:24:21 by yusengok          #+#    #+#             */
/*   Created: 2024/04/20 18:24:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_env(t_base *base, char *arg, int *j)
{
	t_env	*to_find;

	to_find = base->envn;
	while (arg[*j] && arg[(*j) + 1])
	{
		if (arg[*j] == '+' && arg[(*j) + 1] == '=')
			break ;
		(*j)++;
	}
	while (to_find)
	{
		if (ft_strncmp(to_find->key, arg, (*j) - 1) == 0)
			return (to_find);
		to_find = to_find->next;
	}
	return (NULL);
}

int	add_env_value(t_base *base, t_line *node, int i)
{
	t_env	*target;
	char	*tmp;
	int		j;

	j = 0;
	target = get_env(base, node->arg[i], &j);
	if (target == NULL)
		return (create_nod_from_arg(base, node, i));
	tmp = target->value;
	target->value = ft_strjoin(tmp, node->arg[i] + j + 2);
	if (!target->value)
	{
		target->value = tmp;
		return (1);
	}
	return (ft_free((void *)tmp, 0));
}
