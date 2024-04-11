/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:53 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 01:29:45 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_recreate_str(char *str, int i)
{
	char	*new_str;
	int		len;
	
	while (i != 0 && (str[i] == '<' || str[i] == '>' || str[i] == ' ' || str[i] == '\0'))
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
	// printf("str %p\n", str); //---> 0x561d06c8a8b0
	// printf("new str %p\n", new_str); //---> 0x561d06ca69f0
	return (new_str);
}

int	cnt_file(int i, char **str)
{
	while ((*str)[i] == ' ' || (*str)[i] == 9)
		i++;
	if ((*str)[i] == '<' || (*str)[i] == '>' || (*str)[i] == '\0')
	{
		// printf("before %p\n", *str); //---> 0x561d06c8a8b0 ==> This was free'd
		*str = ft_recreate_str(*str, i);
		// printf("after %p\n", *str); //---> 0x561d06ca69f0
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
	if ((*str)[i] != '<' && (*str)[i] != '>' && (*str)[i] != ' ' && (*str)[i] != 9  && (*str)[i] != '\0')
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
