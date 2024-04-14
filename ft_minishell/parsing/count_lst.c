/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:53 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 13:35:25 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_syntax_error(t_line *line)
{
	line->error_syntax = 1;
	return (-1);
}

int	cnt_param(char **str, t_line *line)
{
	int		i;

	i = 0;
	if ((*str)[i] != '<' && (*str)[i] != '>' && (*str)[i] != ' ' \
	&& (*str)[i] != 9 && (*str)[i] != '\0')
	{
		if ((*str)[i] == 34 || (*str)[i] == 39)
			i = cnt_quote(*str, line, i);
		line->nb_arg++;
		i++;
	}
	while ((*str)[i])
	{
		if ((*str)[i] == '<' || (*str)[i] == '>')
			i = skip_file(str, i);
		else if ((*str)[i] == 34 || (*str)[i] == 39)
			i = cnt_quote(*str, line, i);
		else if ((*str)[i] != ' ' && (*str)[i] != 9 && ((*str)[i - 1] == ' ' \
		|| (*str)[i - 1] == 34 || (*str)[i - 1] == 9))
			line->nb_arg++;
		if (i == -1)
			return (set_syntax_error(line));
		i++;
	}
	return (0);
}
