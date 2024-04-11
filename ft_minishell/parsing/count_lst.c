/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:53 by dvo               #+#    #+#             */
/*   Updated: 2024/04/10 17:14:02 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_recreate_str(char *str, int i)
{
	char	*new_str;
	int		len;
	
	while (i != 0 && (str[i] == '<' || str[i] == '>' || str[i] == ' '))
		i--;
	i++;
	new_str = ft_calloc(i + 1, sizeof(char));
	len = 0;
	while (len < i)
	{
		new_str[len] = str[len];
		len++;
	}
	new_str[len] = '\0';
	return (new_str);
}

int	cnt_file(int i, char **str)
{
	while ((*str)[i] == ' ' || (*str)[i] == 9)
		i++;
	if ((*str)[i] == '<' || (*str)[i] == '>' || (*str)[i] == '\0')
	{
		*str = ft_recreate_str(*str, i);
		return (-1);
	}
	if ((*str)[i] == 34)
	{
		i++;
		while ((*str)[i] != 34)
			i++;
	}
	else if ((*str)[i] == 39)
	{
		i++;
		while ((*str)[i] != 39)
			i++;
	}
	return (i);
}

int	skip_file(char **str, int i)
{
	if ((*str)[i] == '<')
	{
		i++;
		if ((*str)[i] == '<')
			i++;
		i = cnt_file(i, str);
	}
	else if ((*str)[i] == '>')
	{
		i++;
		if ((*str)[i] == '>')
			i++;
		i = cnt_file(i, str);
	}
	return (i);
}

int	cnt_quote(char *str, t_line *line, int i)
{
	if (str[i] == 34)
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
	return (i);
}

int	cnt_param(char **str, t_line *line)
{
	int		i;

	i = 0;
	if ((*str)[i] != '<' && (*str)[i] != '>' && (*str)[i] != ' ' && (*str)[i] != 9)
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
		{
			line->error_syntax = 1;
			return (-1);
		}
		i++;
	}
	return (0);
}
