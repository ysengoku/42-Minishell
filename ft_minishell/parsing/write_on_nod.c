/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/03/22 14:28:55 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_simple_quote(int i, t_line *tmp, char *str)
{
	int	j;
	char *quote;

	i++;
	j = 0;
	quote = calloc(1, sizeof(ft_strlen(str)));
	while (str[i] != 39)
		quote[j++] = str[i++];
	quote[j] = '\0';
	j = 0;
	while (quote[j])
	{
		quote[j] = quote[j] * -1;
		j++;
	}
	i++; 
	j = 0;
	while (tmp->arg[j])
		j++;
	tmp->arg[j] = quote;
	return(i);
}

int write_double_quote(int i, t_line *tmp, char *str)
{
	int	j;
	char *quote;

	i++;
	j = 0;
	quote = calloc(1, sizeof(ft_strlen(str)));
	while (str[i] != 34)
		quote[j++] = str[i++];
	quote[j] = '\0';
	j = 0;
	while (quote[j])
	{
		quote[j] = quote[j] * -1;
		j++;
	}
	i++; 
	j = 0;
	while (tmp->arg[j])
		j++;
	tmp->arg[j] = quote;
	return(i);
}

int	write_out_file(int i, t_line *tmp, char *str)
{
	int		j;
	t_file	*stock;
	t_file	*last;
	
	last = tmp->file;
	i++;
	stock = calloc(1, sizeof(t_file));
	stock->filename = calloc(ft_strlen(str), sizeof(char));
	if (str[i] == '>')
	{
		stock->type = OUT_APPEND;
		i++;
	}
	else
		stock->type = OUT_TRUNC;
	j = 0;
	if (str[i] == '<' || str[i] == '>')
			return (-1);
	while(str[i] == ' ')
		i++;
	if (str[i] == '<' || str[i] == '>')
			return (-1);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>' && str[i] != 34\
	&& str[i] != 39)
		stock->filename[j++] = str[i++];
	stock->filename[j] = '\0';
	if (tmp->file == NULL)
		tmp->file = stock;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = stock;
	}
	return(i);
}

int	write_in_file(int i, t_line *tmp, char *str)
{
	int		j;
	t_file	*stock;
	t_file	*last;
	
	last = tmp->file;
	i++;
	stock = calloc(1, sizeof(t_file));
	stock->filename = calloc(ft_strlen(str), sizeof(char));
	if (str[i] == '<')
	{
		stock->type = HERE_DOC;
		i++;
	}
	else
		stock->type = INFILE;
	j = 0;
	if (str[i] == '>' || str[i] == '<')
		return (-1);
	while(str[i] == ' ')
		i++;
	if (str[i] == '<' || str[i] == '>')
		return (-1);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|' && str[i] != 34\
	&& str[i] != 39)
		stock->filename[j++] = str[i++];
	stock->filename[j] = '\0';
		if (tmp->file == NULL)
		tmp->file = stock;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = stock;
	}
	return(i);
}

int	write_char(int i, t_line *tmp, char *str)
{
	int	j;
	char	*arg_string;
	int	last_arg;

	arg_string = calloc(ft_strlen(str) + 1, sizeof(char));
	j = 0;
	while (str[i] && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|' && str[i] != ' '\
	&& str[i] != 34 && str[i] != 39)
	{
		arg_string[j] = str[i];
		i++;
		j++;
	}
	arg_string[j] = '\0';
	last_arg = 0;
	while (tmp->arg[last_arg])
		last_arg++;
	tmp->arg[last_arg] = arg_string;
	return(i);
}
