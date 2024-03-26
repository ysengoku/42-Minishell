/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/03/26 15:01:01 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_base *base)
{
	t_env	*tmp;
	int		fd[2];

	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, &fd[IN], &fd[OUT]) == 1)
		return (EXIT_FAILURE);
	tmp = base->envn;
	while (tmp)
	{
		printf("%s", tmp->key);
		if (tmp->value)
			printf("=%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
