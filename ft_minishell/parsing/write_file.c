/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:31 by dvo               #+#    #+#             */
/*   Updated: 2024/04/01 22:46:34 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	quote_in_file(int *j, char *str, int i, t_file *stock)
// {
// 	int	tmp;

// 	tmp = *j;
// 	if (str[i] == 34)
// 	{
// 		i++;
// 		while (str[i] != 34)
// 			stock->filename[tmp++] = str[i++] * -1;
// 	}
// 	else if (str[i] == 39)
// 	{
// 		i++;
// 		while (str[i] != 39)
// 			stock->filename[tmp++] = str[i++] * -1;
// 	}
// 	i++;
// 	*j = tmp;
// 	return (i);
// }

// int	ft_write_file(char *str, int *i, t_file *stock)
// {
// 	int	j;

// 	j = 0;
// 	if (str[i] == '<' || str[i] == '>')
// 		return (-1);
// 	while (str[i] == ' ')
// 		i++;
// 	if (str[i] == '<' || str[i] == '>')
// 		return (-1);
// 	while (str[i] && str[i] != ' ' && str[i] != '<' \
// 	&& str[i] != '|' && str[i] != '>')
// 	{
// 		if (str[i] == 34 || str[i] == 39)
// 			i = quote_in_file(&j, str, i, stock);
// 		stock->filename[j++] = str[i++];
// 	}
// 	stock->filename[j] = '\0';
// 	return (i);
// }

int	write_out_file(int i, t_line *tmp, char *str, t_base *base)
{
	t_file	*stock;
	t_file	*last;

	last = tmp->file;
	i++;
	stock = calloc(1, sizeof(t_file));
	if (str[i] == '>')
	{
		stock->type = OUT_APPEND;
		i++;
	}
	else
		stock->type = OUT_TRUNC;
	stock->filename = write_char(&i, tmp, str, base);
	if (tmp->file == NULL)
		tmp->file = stock;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = stock;
	}
	return (i);
}

int	write_in_file(int i, t_line *tmp, char *str, t_base *base)
{
	t_file	*stock;
	t_file	*last;

	last = tmp->file;
	i++;
	stock = calloc(1, sizeof(t_file));
	if (str[i] == '<')
	{
		stock->type = HERE_DOC;
		i++;
	}
	else
		stock->type = INFILE;
	stock->filename = write_char(&i, tmp, str, base);
	if (tmp->file == NULL)
		tmp->file = stock;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = stock;
	}
	return (i);
}
