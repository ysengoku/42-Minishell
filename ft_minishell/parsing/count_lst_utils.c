/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:11:31 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/12 10:47:06 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_recreate_str(char *str, int i)
{
	char	*new_str;
	int		len;

	while (i != 0
		&& (str[i] == '<' || str[i] == '>' || str[i] == ' ' || str[i] == '\0'))
		i--;
	if (i != 0)
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

static int	cnt_file(int i, char **str)
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
