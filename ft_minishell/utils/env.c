/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:19 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/16 13:56:34 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_base *base, char *key)
{
	t_env	*current_node;

	current_node = base->envn;
	while (current_node)
	{
		if (ft_strcmp(current_node->key, key) == 0)
			return (current_node);
		current_node = current_node->next;
	}
	return (NULL);
}
