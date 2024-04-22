/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:03:21 by dvo               #+#    #+#             */
/*   Updated: 2024/04/22 14:45:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_syntax(char *str, t_base *base)
{
	int	i;

	i = 0;
	if (str[0] == '=' || str[0] == ' ' || str[0] == '\0' || \
	(str[0] >= '0' && str[0] <= '9'))
	{
		base->error_msg = str;
		ft_display_error(2, base);
		return (-1);
	}
	while (str[i] && !(str[i] == '=' || (str[i] == '+' && str[i + 1] == '=')))
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
	if (str[i] == '+' && str[i + 1] == '=')
		return (1);
	return (0);
}

static int	check_max_arg(char *str, t_base *base)
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

static int	atr_nod_from_expt(t_base *base, t_line *node, t_env *tmp, int i)
{
	char	**split;

	split = split_export_arg(node->arg[i]);
	if (!split)
		return (-1);
	tmp->key = ft_strdup(split[0]);
	if (!tmp->key)
		return (ft_free_strarr(split), -1);
	if (split[1] == NULL)
	{
		tmp->value = ft_calloc(1, sizeof(char));
		ft_free_strarr(split);
	}
	else
		tmp->value = assign_value(split);
	base->max_arg_export = check_max_arg(tmp->value, base);
	return (0);
}

int	create_nod_from_arg(t_base *base, t_line *node, int i)
{
	t_env	*tmp;

	tmp = ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (1);
	if (ft_strchr(node->arg[i], '=') == NULL)
	{
		tmp->key = ft_strdup(node->arg[i]);
		tmp->value = NULL;
	}
	else
	{
		if (atr_nod_from_expt(base, node, tmp, i) == -1)
			return (1);
	}
	export_add_on_nod(base, tmp);
	return (0);
}

int	ft_export(t_base *base, t_line *node, int fd[2])
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	if (node->arg[1] == NULL)
		return (export_null(base, fd));
	ft_close(fd[IN], fd[OUT], 0);
	if (node->arg[i][0] == '-')
		return (print_err(EXPORT, node->arg[1], "invalid option", 2));
	while (node->arg[i])
	{
		status = check_syntax(node->arg[i], base);
		if (status == -1)
			return (1);
		if (status == 1)
			status = add_env_value(base, node, i);
		else
			status = create_nod_from_arg(base, node, i);
		i++;
	}
	return (status);
}
