/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/04 16:36:13 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_base *base, t_line *node)
{
	t_env	*tmp;
	int		fd[2];

	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, node, &fd[IN], &fd[OUT]) == 1)
		return (1);
	tmp = base->envn;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, fd[OUT]);
		if (tmp->value)
		{
			write(fd[OUT], "=", 1);
			ft_putendl_fd(tmp->value, fd[OUT]);
		}
		tmp = tmp->next;
	}
	ft_close(fd[IN], fd[OUT], 0);
	return (0);
}
