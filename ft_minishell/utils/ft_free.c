/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:55:52 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/26 08:25:58 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void * to_free)
{
	if (to_free)
		free(to_free);
}

void	ft_free_strarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_base_content(t_base *base)
{
	t_line	*current_node;
	t_line	*next_node;

	if (base)
	{
		current_node = base->lst;
		while (current_node)
		{
			if (current_node->arg)
				ft_free_strarr(current_node->arg);
			if (current_node->file)
			{
				free(current_node->file->filename);
				free(current_node->file);
			}
			next_node = current_node->next;
			free(current_node);
			current_node = next_node;
		}
	}
}

void	free_envlist(t_base *base)
{
	t_env	*current_node;
	t_env	*next_node;

	current_node = base->envn;
	while (current_node)
	{
		if (current_node->key)
			free(current_node->key);
		if (current_node->value)
			free(current_node->value);
		next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
}
