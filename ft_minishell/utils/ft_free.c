/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:55:52 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 20:08:04 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free(void *to_free, int exit_status)
{
	if (to_free)
		free(to_free);
	to_free = NULL;
	return (exit_status);
}

void	ft_free_strarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_base_content(t_base *base)
{
	t_line	*current_node;
	t_line	*next_node;
	t_file	*next_file;

	if (base)
	{
		current_node = base->lst;
		while (current_node)
		{
			if (current_node->arg)
				ft_free_strarr(current_node->arg);
			while (current_node->file)
			{
				free(current_node->file->filename);
				next_file = current_node->file->next;
				free(current_node->file);
				current_node->file = next_file;
			}
			next_node = current_node->next;
			free(current_node);
			current_node = next_node;
		}
		base->lst = NULL;
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
	if (base->null_env == 1)
		ft_free_strarr(base->env);
}

int	clear_before_exit(t_base *base, int exit_code)
{
	unlink_heredoc(base);
	rl_clear_history();
	free_base_content(base);
	free_envlist(base);
	free(base);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (exit_code);
}
