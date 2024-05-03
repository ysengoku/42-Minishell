/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:15:56 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 23:30:56 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			{
				if (ft_new_arg(norm->tmp, res, j) == 1)
					return (-1);
			}
			else
				return (ft_display_error(4, norm->base));
			j = -1;
		}
		j++;
	}
	if (norm->str[i] != '?')
		i = nxt_index_dollars(norm->str, i, norm->tmp);
	*ptr_i = i;
	return (j);
}
