/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arg_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:29:03 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 23:29:57 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_arg_to_node(t_line *tmp, char *str)
{
	int		last_nod;

	last_nod = 0;
	while (tmp->arg[last_nod])
		last_nod++;
	tmp->arg[last_nod] = str;
}

static void	ft_new_arg_next(char *res, int check)
{
	int	i;

	i = 0;
	while (res[check] && (res[check] == ' ' || res[check] == '\t'))
		check++;
	while (res[check])
		res[i++] = res[check++];
	while (res[i])
		res[i++] = '\0';
}

int	ft_new_arg( t_line *tmp, char *res, int j)
{
	char	*str;
	int		i;
	int		check;

	check = j;
	while (res && res[check] && (res[check] == ' ' || res[check] == '\t'))
		check++;
	if (!res[check])
		res[j] = '\0';
	i = 0;
	check = 0;
	while (res && res[check] && (res[check] == ' ' || res[check] == '\t'))
		check++;
	str = ft_calloc(j + 2, sizeof(char));
	if (!str)
		return (1);
	while (res[check] && res[check] != ' ' && res[check] != '\t')
		str[i++] = res[check++];
	str[i] = '\0';
	add_arg_to_node(tmp, str);
	ft_new_arg_next(res, check);
	return (0);
}
