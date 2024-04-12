/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:15:56 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 19:18:49 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	enter_quote_mode(char *str, int i, t_line *tmp)
{
	if (str[i] == 34 && tmp->char_type == STANDARD)
		tmp->char_type = DOUBLE_Q;
	else if (str[i] == 39 && tmp->char_type == STANDARD)
		tmp->char_type = QUOTE;
	else if (str[i] == 34 && tmp->char_type == DOUBLE_Q)
		tmp->char_type = STANDARD;
	else if (str[i] == 39 && tmp->char_type == QUOTE)
		tmp->char_type = STANDARD;
	else if (str[i] == 34 && tmp->char_type == DOC)
		tmp->char_type = DOC_DOUBLE_Q;
	else if (str[i] == 39 && tmp->char_type == DOC)
		tmp->char_type = DOC_QUOTE;
	else if (str[i] == 34 && tmp->char_type == DOC_DOUBLE_Q)
		tmp->char_type = DOC;
	else if (str[i] == 39 && tmp->char_type == DOC_QUOTE)
		tmp->char_type = DOC;
	else
		return (0);
	return (1);
}

int	index_dollars(char *str, int *ptr_i, t_line *tmp, char *res)
{
	int	j;
	int	i;

	i = *ptr_i + 1;
	j = 0;
	while (res && res[j])
		j++;
	if (str[i] != '?')
	{
		while ((str[i] && str[i] != ' ' && str[i] != '<' \
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
	}
	*ptr_i = i;
	return (j);
}
