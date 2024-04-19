/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:20:50 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 10:32:37 by yusengok         ###   ########.fr       */
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

int	index_tilde(t_norm *norm, int *ptr_i, char *res)
{
	int	j;
	int	i;

	i = *ptr_i + 1;
	j = 0;
	while (res && res[j])
		j++;
	norm->tmp->typ_write_chr = 0;
	while (norm->str[i] && norm->str[i] != ' ' && norm->str[i] != '/')
		i++;
	i--;
	*ptr_i = i;
	return (j);
}
