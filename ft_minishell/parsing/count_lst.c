/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:53 by dvo               #+#    #+#             */
/*   Updated: 2024/03/22 18:15:48 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cnt_file(int i, char *str)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (-1);
	if (str[i] == 34)
	{
		i++;
		while (str[i] != 34)
			i++;
	}
	else if (str[i] == 39)
	{
		i++;
		while (str[i] != 39)
			i++;
	}
	return (i);
}

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
			i = cnt_file(i, str);
		}
		else if (str[i] == '>')
		{
			i++;
			if (str[i] == '>')
				i++;
			i = cnt_file(i, str);
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
		if (i == -1)
			return (-1);
		i++;
	}
 return (0);
}
