/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:15:56 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 13:26:56 by yusengok         ###   ########.fr       */
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

static void	ft_new_arg( t_line *tmp, char *res, int j)
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
	str = ft_calloc(j + 2, sizeof(char)); ///// -----> Need to check malloc protect
	while (res[check] && res[check] != ' ' && res[check] != '\t')
		str[i++] = res[check++];
	str[i] = '\0';
	add_arg_to_node(tmp, str);
	i = 0;
	while (res[check] && (res[check] == ' ' || res[check] == '\t'))
		check++;
	while (res[check])
		res[i++] = res[check++];
	while (res[i])
		res[i++] = '\0';
}

static int	nxt_index_dollars(char *str, int i, t_line *tmp)
{
	while ((str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '='\
	&& str[i] != '|' && str[i] != '>' && str[i] != '$' && str[i] != '.' \
	&& str[i] != 34 && str[i] != 39 && str[i] != 9 && str[i] != 47))
	{
		if (enter_quote_mode(str, i, tmp) == 1)
		{
			i++;
			break ;
		}
		if (str[i] == '$' && tmp->char_type != QUOTE)
			break ;
		i++;
	}
	i--;
	return (i);
}

static int	check_type(int j, t_norm *norm, char *res)
{
	if (res[j] == ' ' && norm->tmp->char_type == STANDARD)
		return (1);
	return (0);
}

int	index_dollars(t_norm *norm, int *ptr_i, char *res)
{
	int	i;
	int	j;

	j = norm->j;
	i = *ptr_i + 1;
	while (res && res[j])
	{
		if (check_type(j, norm, res) == 1)
		{
			if (norm->tmp->typ_write_chr == 0)
				ft_new_arg(norm->tmp, res, j);
			else
			{
				ft_display_error(4, norm->base);
				return (-1);
			}
			j = -1;
		}
		j++;
	}
	if (norm->str[i] != '?')
		i = nxt_index_dollars(norm->str, i, norm->tmp);
	*ptr_i = i;
	return (j);
}
