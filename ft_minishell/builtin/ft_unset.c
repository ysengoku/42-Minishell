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
	char	*unset_arg;

	unset_arg = node->arg[1];
	if (!unset_arg || !unset_arg[0] || !strcmp("_", unset_arg)
		|| !strcmp("env", unset_arg) || !strncmp("=", unset_arg, 1)
		|| !strcmp("?", unset_arg) || !strcmp("$", unset_arg))
	{
		base->exit_code = 0;
		return (1);
	}
	else if (unset_arg[0] == '-')
	{
		base->exit_code = 2;
		print_err(UNSET, unset_arg, "invalid option", 1);
		return (1);
	}
	return (0);
}

static void	delete_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

//Error case & return 1
//bash: : No such file or directory
// 518 unset ""
// 519 
// 520 unset =
// 521 
// 522 unset "="
// 523 
// 524 unset ""=
// 525 
// 526 unset =""
// 527 
// 528 unset ==
// 529 
// 530 unset ?
// 531 
// 532 unset "?"
// 533 
// 534 unset $
// 535 
// 536 unset "$"
// 537 
// 538 unset $""
