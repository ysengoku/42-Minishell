/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/04/18 08:29:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_arg(int i, t_line *tmp, char *str, t_base *base)
{
	char	*arg;
	int		last_nod;

	arg = write_char(&i, tmp, str, base);
	if (!arg)
		return (i);
	last_nod = 0;
	while (tmp->arg[last_nod])
		last_nod++;
	tmp->arg[last_nod] = arg;
	return (i);
}

void	enter_condition_mode(t_norme *norm, char **res, int boo, t_base *base)
{
	if (boo == 1)
	{
		if (enter_quote_mode(norm->str, norm->i, norm->tmp) == 0)
		{
			(*res)[norm->j] = norm->str[norm->i];
			norm->j++;
		}
	}
	if (boo == 2)
	{
		*res = translate_dollar(norm->str + norm->i + 1, base, *res);
		norm->j = index_dollars(norm, &norm->i, *res);
	}
	if (boo == 3)
	{
		(*res)[norm->j] = norm->str[norm->i];
		norm->j++;
		(*res)[norm->j] = '\0';
	}
	if (boo == 4)
	{
		*res = translate_dollar("HOME", base, *res);
		norm->j = index_wave(norm, &norm->i, *res);
	}
}

t_norme	attribute_norm(int *index, t_line *tmp, char *str, t_base *base)
{
	t_norme	norm;

	norm.i = *index;
	norm.str = str;
	norm.tmp = tmp;
	norm.base = base;
	return (norm);
}

void	dollars_condition(t_norme *norm, char	**res, t_base *base)
{
	if (norm->str[norm->i] == '$' && norm->tmp->char_type != QUOTE \
	&& norm->tmp->char_type != DOC && ((norm->str[norm->i + 1] >= '0' \
	&& norm->str[norm->i + 1] <= '9') || (norm->str[norm->i + 1] >= '?' \
	&& norm->str[norm->i + 1] <= 'Z') || (norm->str[norm->i + 1] >= '_' && \
	norm->str[norm->i + 1] <= 'z')) && norm->tmp->char_type != DOC_QUOTE && \
	norm->tmp->char_type != DOC_DOUBLE_Q)
		enter_condition_mode(norm, res, 2, base);
	else if (norm->str[norm->i] == '~' && norm->tmp->char_type == STANDARD && \
	(norm->str[norm->i + 1] == '/' || norm->str[norm->i + 1] == '\0') && norm->j == 0)
		enter_condition_mode(norm, res, 4, base);
	else
		enter_condition_mode(norm, res, 3, base);
}

char	*write_char(int *index, t_line *tmp, char *str, t_base *base)
{
	char	*res;
	t_norme	norm;

	norm = attribute_norm(index, tmp, str, base);
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	norm.j = 0;
	while (res && norm.j != -1 && str[norm.i] && ((str[norm.i] != '<' && \
	str[norm.i] != '>' && str[norm.i] != '|' && str[norm.i] != ' ' && \
	str[norm.i] != 9) || (tmp->char_type == QUOTE || \
	tmp->char_type == DOUBLE_Q)))
	{
		if (str[norm.i] == 34 || str[norm.i] == 39)
			enter_condition_mode(&norm, &res, 1, base);
		else
			dollars_condition(&norm, &res, base);
		norm.i++;
	}
	if (norm.j == -1)
	{
		return (free(res), NULL);
	}
	if (res)
		res[norm.j] = '\0';
	*index = norm.i;
	return (res);
}
