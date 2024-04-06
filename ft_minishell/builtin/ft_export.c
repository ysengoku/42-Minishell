/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/06 19:00:26 by dvo              ###   ########.fr       */
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
			ft_fprintf(fd[OUT], "=\"%s\"", print->value);
		ft_fprintf(fd[OUT], "\n");
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
		if (ft_strcmp(last->key, tmp->key) == 0)
		{
			tmp->next = last->next;
			free(last->key);
			free(last->value);
			free(last);
			base->envn = tmp;
			return ;
		}
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
int	check_error_export(char *str, t_base *base)
{
	int	i;

	i = 0;
	if (str[0] == '=' || str[0] == ' ' \
	|| (str[0] >= '0' && str[0] <= '9'))
		{
			base->error_msg = str;
			ft_display_error(2, base);
			return (-1);
		}
	while (str[i] && str[i] != '=')
	{
		if (str[i] < '0' || (str[i] > '9' && str[i] < 'A') || \
		(str[i] > 'Z' && str[i] < '_') || str[i] == 96 || \
		str[i] > 'z')
		{
			base->error_msg = str;
			ft_display_error(2, base);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_base *base, int fd[2])
{
	t_env	*tmp;
	char	**split;
	int		i;

	i = 1;
	if (base->lst->arg[1] == NULL)
		return (export_null(base, fd));
	while (base->lst->arg[i])
	{
		if (check_error_export(base->lst->arg[i], base) == -1)
			return (1);
		if (base->lst->arg[i][0] == '=' || base->lst->arg[i][0] == ' ')
		{
			ft_display_error(2, base);
			return (1);
		}
		tmp = ft_calloc(1, sizeof(t_env));
		if (!tmp)
			return (-1);
		if (ft_strchr(base->lst->arg[i], '=') == NULL)
		{
			tmp->key = ft_strdup(base->lst->arg[i]);
			tmp->value = NULL;
		}
		else
		{
			split = ft_split(base->lst->arg[i], '=');
			tmp->key = ft_strdup(split[0]);
			if (split[1] == NULL)
				tmp->value = ft_calloc(1, sizeof(char));
			else
				tmp->value = assign_value(split);
		}
		export_add_on_nod(base, tmp);
		i++;
	}
	return (0);
}
