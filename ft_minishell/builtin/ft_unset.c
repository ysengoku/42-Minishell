/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:03:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/30 18:49:56 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unset_arg(char *str);
static void	delete_env(t_base *base, t_line *node, int i);
static void	delete_node(t_env *node, t_base *base);

int	ft_unset(t_base *base, t_line *node, int fd[2])
{
	int		i;

	i = 1;
	ft_close(fd[IN], fd[OUT], 0);
	while (node->arg[i])
	{
		if (node->arg[i][0] == '-')
		{
			base->exit_code = 2;
			return (print_err(UNSET, node->arg[i], "invalid option", 2));
		}
		if (check_unset_arg(node->arg[i]) == 1)
			i++;
		else
		{
			delete_env(base, node, i);
			i++;
		}
	}
	return (0);
}

static int	check_unset_arg(char *str)
{
	int		i;

	i = 0;
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (1);
	while (str[++i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
	}
	return (0);
}

void	delete_env(t_base *base, t_line *node, int i)
{
	t_env	*target_node;
	t_env	*previous_node;

	target_node = base->envn;
	previous_node = NULL;
	while (target_node)
	{
		if (ft_strcmp(target_node->key, node->arg[i]) == 0)
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
	delete_node(target_node, base);
}

static void	delete_node(t_env *node, t_base *base)
{
	if (ft_strcmp(node->key, OLDPWD) == 0)
		base->oldpwd_log[0] = '\0';
	free(node->key);
	free(node->value);
	free(node);
}
