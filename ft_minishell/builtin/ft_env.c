/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/03/24 19:59:01 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_base *base) 
{
	t_env	*tmp;

	tmp = base->envn;
	while (tmp)
	{
		printf("%s", tmp->key);
		if (tmp->value)
			printf("=%s\n", tmp->value);
		tmp = tmp->next;
	}
	return(0);
}
