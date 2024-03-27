/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/27 14:45:31 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_base *base)
{
	t_env	*current_node;
	t_env	*previous_node;

	current_node = base->envn;
	previous_node = NULL;
	while (current_node)
	{
		if (strcmp(current_node->key, base->lst->arg[1]) == 0)
			break ;
		previous_node = current_node;
		current_node = current_node->next;
	}
	if (!current_node)
	{
		ft_fprintf(2, "minishell: unset: '%s': not a valid identifier\n",
			base->lst->arg[1]);
		return (1);
	}
	if (previous_node)
		previous_node->next = current_node->next;
	free(current_node->key);
	free(current_node->value);
	free(current_node);
	return (0);
}
