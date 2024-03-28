/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/03/28 16:43:26 by dvo              ###   ########.fr       */
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

int	write_char(int i, t_line *tmp, char *str, t_base *base)
{
	int		j;
	char	*arg_string;
	int		last_arg;

	arg_string = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!arg_string)
		return (-1);
	j = 0;
	while (str[i] && ((str[i] != '<' \
	&& str[i] != '>' && str[i] != '|' && str[i] != ' ') || tmp->char_type != STANDARD))
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (enter_quote_mode(str, i, tmp) == 0)
			{
				arg_string[j] = str[i];
				j++;
			}
		}
		else if (str[i] == '$' && tmp->char_type != QUOTE)
		{
			arg_string = translate_dollar(str + i + 1, base, tmp, arg_string);
			j = 0;
			while (arg_string[j])
				j++;
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '<' \
			&& str[i] != '|' && str[i] != '>' && str[i] != '$' \
			&& enter_quote_mode(str, i, tmp) == 0)
				i++;
			if (str[i] != 34 && str[i] != 39)
				i--;
		}
		else
		{
			arg_string[j] = str[i];
			j++;
		}
		i++;
	}
	arg_string[j] = '\0';
	last_arg = 0;
	while (tmp->arg[last_arg])
		last_arg++;
	tmp->arg[last_arg] = arg_string;
	return (i);
}

void	write_nod(int i, t_line *tmp, char *str, t_base *base)
{
	while (str[i])
	{
		if (str[i] == '>')
			i = write_out_file(i, tmp, str);
		else if (str[i] == '<')
			i = write_in_file(i, tmp, str);
		else if (str[i] == ' ')
			i++;
		else
			i = write_char(i, tmp, str, base);
	}
}
