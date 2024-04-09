/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/09 17:06:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unset_arg(t_base *base, t_line *node);
static void	delete_node(t_env *node);

int	ft_unset(t_base *base, t_line *node, int fd[2])
{
	t_env	*target_node;
	t_env	*previous_node;

	ft_close(fd[IN], fd[OUT], 0);
	target_node = base->envn;
	previous_node = NULL;
	if (check_unset_arg(base, node) == 1)
		return (base->exit_code);
	while (target_node)
	{
		if (strcmp(target_node->key, node->arg[1]) == 0)
			break ;
		previous_node = target_node;
		target_node = target_node->next;
	}
	if (!target_node)
		return (0);
	if (previous_node)
		previous_node->next = target_node->next;
	else
		base->envn = target_node->next;
	delete_node(target_node);
	return (0);
}

static int	check_unset_arg(t_base *base, t_line *node)
{
	int		i;

	i = 0;
	if (node->arg[1][i] == '-')
	{
		base->exit_code = 2;
		print_err(UNSET, node->arg[1], "invalid option", 1);
		return (1);
	}
	if (!node->arg[1][i] || !ft_isalpha(node->arg[1][i]))
	{
		base->exit_code = 1;
		print_err(UNSET, node->arg[1], "not a valid identifier", 1);
		return (1);
	}
	while (node->arg[1][++i])
	{
		if (!ft_isalnum(node->arg[1][i]) && node->arg[1][i] != '_')
		{
			base->exit_code = 1;
			print_err(UNSET, node->arg[1], "not a valid identifier", 1);
			return (1);
		}
	}
	return (0);
}

static void	delete_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}
