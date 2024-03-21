/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:53 by dvo               #+#    #+#             */
/*   Updated: 2024/03/21 00:52:14 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cnt_param(char *str, t_line *line)
{
	t_cnt 	*cnt;
	int		i;

	i = 0;
	cnt = calloc(1, sizeof(t_cnt));
	if (str[i] != '<' && str[i] != '>' && str[i] != ' ')
	{
		cnt->nb_arg++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '<')
		{
			cnt->nb_in++;
			i++;
			if (str[i] == '<')
				i++;
			while (str[i] == ' ')
			 i++;
			if (str[i] == '>' || str[i] == '<')
				return (-1);
		}
		else if (str[i] == '>')
		{
			cnt->nb_out++;
			i++;
			if (str[i] == '>')
				i++;
			while (str[i] == ' ')
			 i++;
			if (str[i] == '<' || str[i] == '>')
				return (-1);
		}
		else if (str[i] == 34)
		{
			cnt->nb_arg++;
			i++;
			while (str[i] != 34)
				i++;
		}
		else if (str[i] == 39)
		{
			cnt->nb_arg++;
			i++;
			while (str[i] != 39)
				i++;
		}
		else if (str[i] != ' ' && (str[i - 1] == ' ' || str[i - 1] == 34))
			cnt->nb_arg++;
		i++;
	}
 line->count = cnt;
 return (0);
}
