/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:46:58 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/10 09:55:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new(t_base *base, t_env *last, t_env *tmp);

void	export_add_on_nod(t_base *base, t_env *tmp)
{
	t_env	*last;

	last = base->envn;
	if (!base->envn)
		base->envn = tmp;
	else
		add_new(base, last, tmp);
}

static void	add_new(t_base *base, t_env *last, t_env *tmp)
{
	if (ft_strcmp(last->key, tmp->key) == 0)
	{
		tmp->next = last->next;
		free(last->key);
		free(last->value);
		free(last);
		base->envn = tmp;
		return ;
	}
	while (last->next)
	{
		if (ft_strcmp(last->next->key, tmp->key) == 0)
		{
			tmp->next = last->next->next;
			free(last->next->key);
			free(last->next->value);
			free(last->next);
			last->next = tmp;
			return ;
		}
		last = last->next;
	}
	last->next = tmp;
}
