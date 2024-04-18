/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:15:56 by dvo               #+#    #+#             */
/*   Updated: 2024/04/18 16:38:21 by yusengok         ###   ########.fr       */
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

static void	ft_new_arg( t_line *tmp, char *res, int j)
{
	char	*str;
	int		i;
	int		last_nod;

	i = 0;
	str = ft_calloc(j + 2, sizeof(char));
	while (i < j)
	{
		str[i] = res[i];
		i++;
	}
	str[i] = '\0';
	last_nod = 0;
	while (tmp->arg[last_nod])
		last_nod++;
	tmp->arg[last_nod] = str;
	i = 0;
	j++;
	while (res[j])
		res[i++] = res[j++];
	while (res[i])
		res[i++] = '\0';
	tmp->type_write_char = 2;
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

int	index_dollars(t_norme *norm, int *ptr_i, char *res)
{
	int	j;
	int	i;

	i = *ptr_i + 1;
	j = 0;
	while (res && res[j])
	{
		if ((j >= i || norm->tmp->type_write_char == 2) && res[j] == ' ' && norm->tmp->char_type == STANDARD)
		{
			if (norm->tmp->type_write_char == 0 || norm->tmp->type_write_char == 2)
				ft_new_arg(norm->tmp, res, j);
			else
			{
				ft_display_error(4, norm->base);
				return (-1);
			}
			j = 0;
		}
		j++;
	}
	norm->tmp->type_write_char = 0;
	if (norm->str[i] != '?')
		i = nxt_index_dollars(norm->str, i, norm->tmp);
	*ptr_i = i;
	return (j);
}

int	index_wave(t_norme *norm, int *ptr_i, char *res)
{
	int	j;
	int	i;

	i = *ptr_i + 1;
	j = 0;
	while (res && res[j])
		j++;
	norm->tmp->type_write_char = 0;
	while (norm->str[i] && norm->str[i] != ' ' && norm->str[i] != '/')
		i++;
	i--;
	*ptr_i = i;
	return (j);
}
