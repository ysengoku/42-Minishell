/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:29:19 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/04 14:53:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env_var(t_base *base, char *key)
{
	t_env	*pwd_node;

	pwd_node = base->envn;
	while (pwd_node)
	{
		if (ft_strcmp(pwd_node->key, key) == 0)
			return (pwd_node);
		pwd_node = pwd_node->next;
	}
	return (NULL);
}
