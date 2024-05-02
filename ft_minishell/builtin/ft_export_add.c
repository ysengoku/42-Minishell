/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:46:58 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 23:24:24 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_new(t_base *base, t_env *last, t_env *tmp);
static int	get_length(int *len1, char *arg);

void	export_add_on_nod(t_base *base, t_env *tmp)
{
	t_env	*last;

	last = base->envn;
	if (!base->envn)
		base->envn = tmp;
	else
		add_new(base, last, tmp);
}

char	**split_export_arg(t_base *base, char *arg, t_env *tmp)
{
	char	**split;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = get_length(&len1, arg);
	split = ft_calloc(3, sizeof(char *));
	if (!split)
		exit_after_malloc_fail(base, tmp, NULL);
	split[0] = ft_substr(arg, 0, len1);
	if (!split[0])
		exit_after_malloc_fail(base, tmp, split);
	if (arg[len1] == '+')
		len1 += 2;
	split[1] = ft_substr(arg, len1 + 1, len2);
	if (!split[1])
		exit_after_malloc_fail(base, tmp, split);
	return (split);
}

static void	add_new_loop(t_env *last, t_env *tmp)
{
	while (last->next)
	{
		if (ft_strcmp(last->next->key, tmp->key) == 0)
		{
			if (tmp->value)
			{
				tmp->next = last->next->next;
				free(last->next->key);
				free(last->next->value);
				free(last->next);
				last->next = tmp;
			}
			else
			{
				free(tmp->key);
				free(tmp->value);
				free(tmp);
			}
			return ;
		}
		last = last->next;
	}
	last->next = tmp;
}

static void	add_new(t_base *base, t_env *last, t_env *tmp)
{
	if (ft_strcmp(last->key, tmp->key) == 0)
	{
		if (tmp->value)
		{
			tmp->next = last->next;
			free(last->key);
			free(last->value);
			free(last);
			base->envn = tmp;
		}
		else
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		return ;
	}
	add_new_loop(last, tmp);
}

static int	get_length(int *len1, char *arg)
{
	int	len;

	while (arg[*len1])
	{
		if (arg[*len1] == '=')
			break ;
		if (arg[*len1] == '+' && arg[(*len1) + 1] == '=')
			break ;
		(*len1)++;
	}
	len = *len1;
	while (arg[len])
		len++;
	return (len - *len1);
}
