/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:53 by dvo               #+#    #+#             */
/*   Updated: 2024/03/22 14:15:56 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cnt_param(char *str, t_line *line)
{
	int		i;

	i = 0;
	if (str[i] != '<' && str[i] != '>' && str[i] != ' ')
	{
		line->nb_arg++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '<')
		{
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
			line->nb_arg++;
			i++;
			while (str[i] != 34)
				i++;
		}
		else if (str[i] == 39)
		{
			line->nb_arg++;
			i++;
			while (str[i] != 39)
				i++;
		}
		else if (str[i] != ' ' && (str[i - 1] == ' ' || str[i - 1] == 34))
			line->nb_arg++;
		i++;
	}
 return (0);
}
