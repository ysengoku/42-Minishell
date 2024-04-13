/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/13 01:25:59 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_export(char *str, t_base *base)
{
	int	i;

	i = 0;
	if (str[0] == '=' || str[0] == ' ' || (str[0] >= '0' && str[0] <= '9'))
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

int	check_max_arg(char *str, t_base *base)
{
	int	nbr;
	int	i;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			nbr++;
		i++;
	}
	if (base->max_arg_export > nbr)
		return (base->max_arg_export);
	return (nbr);
}

int	create_nod_from_arg(t_base *base, int i)
{
	char	**split;
	t_env	*tmp;

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
		{
			tmp->value = ft_calloc(1, sizeof(char));
			ft_free_strarr(split);
		}
		else
			tmp->value = assign_value(split);
		base->max_arg_export = check_max_arg(tmp->value, base);
	}
	export_add_on_nod(base, tmp);
	return (0);
}

int	ft_export(t_base *base, int fd[2])
{
	int		i;

	i = 1;
	if (base->lst->arg[1] == NULL)
		return (export_null(base, fd));
	if (base->lst->arg[i][0] == '-')
		return (print_err(EXPORT, base->lst->arg[1], "invalid option", 2));
	while (base->lst->arg[i])
	{
		if (check_error_export(base->lst->arg[i], base) == -1)
			return (1);
		if (base->lst->arg[i][0] == '=' || base->lst->arg[i][0] == ' ')
		{
			ft_display_error(2, base);
			return (1);
		}
		create_nod_from_arg(base, i);
		i++;
	}
	return (0);
}
