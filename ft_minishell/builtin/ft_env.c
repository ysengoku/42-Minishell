/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/23 08:20:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_base *base, t_line *node, int fd[2])
{
	t_env	*tmp;

	if (node->arg[1])
	{
		ft_fprintf(2, "env: '%s': No such file or directory\n", node->arg[1]);
		return (127);
	}
	tmp = base->envn;
	while (tmp)
	{
		if (tmp->value)
		{
			if (tmp->unset == 0)
			{
				ft_putstr_fd(tmp->key, fd[OUT]);
				write(fd[OUT], "=", 1);
				ft_putendl_fd(tmp->value, fd[OUT]);
			}
		}
		tmp = tmp->next;
	}
	ft_close(fd[IN], fd[OUT], 0);
	return (0);
}
