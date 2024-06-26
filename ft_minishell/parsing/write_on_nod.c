/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 20:14:05 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	enter_condition_mode(t_norm *norm, char **res, int boo, \
t_base *base)
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
		*res = translate_dollar(norm->str + norm->i + 1, base, *res, norm->tmp);
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
		*res = translate_tilde(norm->str + norm->i, base, *res);
		norm->j = index_tilde(norm, &norm->i, *res);
	}
}

static t_norm	attribute_norm(int *index, t_line *tmp, char *str, t_base *base)
{
	t_norm	norm;

	norm.i = *index;
	norm.str = str;
	norm.tmp = tmp;
	norm.base = base;
	return (norm);
}

static void	dollars_condition(t_norm *norm, char **res, t_base *base)
{
	if (norm->str[norm->i] == '$' && norm->tmp->char_type != QUOTE \
	&& norm->tmp->char_type != DOC \
	&& (((norm->str[norm->i + 1] == 34 || norm->str[norm->i + 1] == 39) \
	&& norm->tmp->char_type == STANDARD) || (norm->str[norm->i + 1] >= '0' \
	&& norm->str[norm->i + 1] <= '9') || (norm->str[norm->i + 1] >= '?' \
	&& norm->str[norm->i + 1] <= 'Z') || (norm->str[norm->i + 1] >= '_' && \
	norm->str[norm->i + 1] <= 'z')) && norm->tmp->char_type != DOC_QUOTE && \
	norm->tmp->char_type != DOC_DOUBLE_Q)
		enter_condition_mode(norm, res, 2, base);
	else if (norm->str[norm->i] == '~' && norm->tmp->char_type == STANDARD && \
	(norm->str[norm->i + 1] == '/' || norm->str[norm->i + 1] == '\0') \
	&& norm->j == 0)
		enter_condition_mode(norm, res, 4, base);
	else
		enter_condition_mode(norm, res, 3, base);
}

static int	ft_check(char *res, char *str, t_line *tmp, t_norm norm)
{
	if (norm.j == -1)
		return (0);
	if (res && norm.j != -1 && str[norm.i] && ((str[norm.i] != '<' && \
	str[norm.i] != '>' && str[norm.i] != '|' && str[norm.i] != ' ' && \
	str[norm.i] != 9) || (tmp->char_type == QUOTE || \
	tmp->char_type == DOUBLE_Q)))
		return (1);
	return (0);
}

char	*write_char(int *index, t_line *tmp, char *str, t_base *base)
{
	char	*res;
	t_norm	norm;

	norm = attribute_norm(index, tmp, str, base);
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
	{
		norm.j = -1;
		return (NULL);
	}
	norm.j = 0;
	while (ft_check(res, str, tmp, norm) == 1)
	{
		if (str[norm.i] == 34 || str[norm.i] == 39)
			enter_condition_mode(&norm, &res, 1, base);
		else
			dollars_condition(&norm, &res, base);
		norm.i++;
	}
	check_error_write_char(&norm, res);
	if (res)
		res[norm.j] = '\0';
	*index = norm.i;
	return (res);
}
