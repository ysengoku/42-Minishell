/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/04/03 17:18:38 by dvo              ###   ########.fr       */
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
	else
		return (0);
	return (1);
}

int	write_arg(int i, t_line *tmp, char *str, t_base *base)
{
	char	*arg;
	int		last_nod;

	arg = write_char(&i, tmp, str, base);
	if (!arg)
		return (-1);
	last_nod = 0;
	while (tmp->arg[last_nod])
		last_nod++;
	tmp->arg[last_nod] = arg;
	return (i);
}

char	*write_char(int *index, t_line *tmp, char *str, t_base *base)
{
	int		j;
	char	*res;
	int		i;

	i = *index;
	res = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i] && ((str[i] != '<' \
	&& str[i] != '>' && str[i] != '|' && \
	str[i] != ' ') || tmp->char_type != STANDARD))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (enter_quote_mode(str, i, tmp) == 0)
			{
				res[j] = str[i];
				j++;
			}
		}
		else if (str[i] == '$' && tmp->char_type != QUOTE)
		{
			res = translate_dollar(str + i + 1, base, res);
			j = 0;
			while (res[j])
				j++;
			i++;
			if (str[i] != '?')
			{
				while (str[i] && str[i] != ' ' && str[i] != '<' \
				&& str[i] != '|' && str[i] != '>' && str[i] != '$' \
				&& str[i] != 34 && str[i] != 39)
					i++;
				if (enter_quote_mode(str, i, tmp) == 0 && (str[i] != 34 || str[i] != 39))
					i--;
			}
		}
		else
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	*index = i;
	return (res);
}

void	write_nod(int i, t_line *tmp, char *str, t_base *base)
{
	while (str[i])
	{
		if (str[i] == '>')
			i = write_out_file(i, tmp, str, base);
		else if (str[i] == '<')
			i = write_in_file(i, tmp, str, base);
		else if (str[i] == ' ')
			i++;
		else
			i = write_arg(i, tmp, str, base);
	}
}
