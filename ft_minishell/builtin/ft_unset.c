/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/14 15:12:06 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unset_arg(t_base *base, char *str);
static void	ghost_unset(t_base *base, char *str);
static void	delete_env(t_base *base, t_line *node, int i);
static void	delete_node(t_env *node);

int	ft_unset(t_base *base, t_line *node, int fd[2])
{
	int		i;

	i = 1;
	ft_close(fd[IN], fd[OUT], 0);
	while (node->arg[i])
	{
		if (check_unset_arg(base, node->arg[i]) == 1)
			return (base->exit_code);
		if (ft_strcmp(node->arg[i], "PWD") == 0 || \
		ft_strcmp(node->arg[i], "USER") == 0)
			ghost_unset(base, node->arg[i]);
		else
			delete_env(base, node, i);
		i++;
	}
	return (0);
}

static int	check_unset_arg(t_base *base, char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
	{
		base->exit_code = 2;
		return (print_err(UNSET, str, "invalid option", 1));
	}
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
	{
		base->exit_code = 1;
		return (print_err(UNSET, str, "not a valid identifier", 1));
	}
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			base->exit_code = 1;
			return (print_err(UNSET, str, "not a valid identifier", 1));
		}
	}
	return (0);
}

static void	ghost_unset(t_base *base, char *str)
{
	t_env	*target_node;

	target_node = base->envn;
	while (target_node)
	{
		if (strcmp(target_node->key, str) == 0)
			break ;
		target_node = target_node->next;
	}
	target_node->unset = 1;
}

void	delete_env(t_base *base, t_line *node, int i)
{
	t_env	*target_node;
	t_env	*previous_node;

	target_node = base->envn;
	previous_node = NULL;
	while (target_node)
	{
		if (strcmp(target_node->key, node->arg[i]) == 0)
			break ;
		previous_node = target_node;
		target_node = target_node->next;
	}
	if (!target_node)
		return ;
	if (previous_node)
		previous_node->next = target_node->next;
	else
		base->envn = target_node->next;
	delete_node(target_node);
}

static void	delete_node(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}
