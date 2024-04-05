/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/05 14:02:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_end(t_base *base)
{
	t_env	*check;

	check = base->envn;
	while (check)
	{
		if (check->order == 0)
			return (0);
		check = check->next;
	}
	return (1);
}

static void	reset_order(t_base *base)
{
	t_env	*reset;

	reset = base->envn;
	while (reset)
	{
		reset->order = 0;
		reset = reset->next;
	}
}

static int	export_null(t_base *base, int fd[2])
{
	t_env	*tmp;
	t_env	*print;

	while (check_end(base) == 0)
	{
		tmp = base->envn;
		ft_fprintf(fd[OUT], "declare -x ");
		print = tmp;
		while (print->order != 0)
			print = print->next;
		while (tmp)
		{
			if (tmp->order == 0 && strcmp(print->key, tmp->key) > 0)
				print = tmp;
			tmp = tmp->next;
		}
		ft_fprintf(fd[OUT], "%s", print->key);
		if (print->value)
			ft_fprintf(fd[OUT], "=\"%s\"\n", print->value);
		print->order = 1;
	}
	reset_order(base);
	ft_close(fd[IN], fd[OUT], 0);
	return (0);
}

static void	export_add_on_nod(t_base *base, t_env *tmp)
{
	t_env	*last;

	last = base->envn;
	if (!base->envn)
		base->envn = tmp;
	else
	{
		while (last->next)
		{
			if (ft_strcmp(last->next->key, tmp->key) == 0)
			{
				tmp->next = last->next->next;
				free(last->next->key);
				free(last->next->value);
				free(last->next);
				last->next = tmp;
				return ;
			}
			last = last->next;
		}
		last->next = tmp;
	}
	return ;
}

int	ft_export(t_base *base, int fd[2])
{
	t_env	*tmp;
	char	**split;

	if (base->lst->arg[1] == NULL)
		return (export_null(base, fd));
	if (base->lst->arg[1])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		if (!tmp)
			return (-1);
		split = ft_split(base->lst->arg[1], '=');
		tmp->key = ft_strdup(split[0]);
		tmp->value = assign_value(split);
		export_add_on_nod(base, tmp);
		return (0);
	}
	return (0);
}
