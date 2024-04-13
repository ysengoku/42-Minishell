/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:31 by dvo               #+#    #+#             */
/*   Updated: 2024/04/12 23:30:29 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	attribute_file_nod(t_file *stock, t_line *tmp)
{
	t_file	*last;

	last = tmp->file;
	if (tmp->file == NULL)
		tmp->file = stock;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = stock;
	}
}

int	write_out_file(int i, t_line *tmp, char *str, t_base *base)
{
	t_file	*stock;

	i++;
	stock = calloc(1, sizeof(t_file));
	if (str[i] == '>')
	{
		stock->type = OUT_APPEND;
		i++;
	}
	else
		stock->type = OUT_TRUNC;
	while (str[i] == ' ')
		i++;
	tmp->type_write_char = 1;
	stock->filename = write_char(&i, tmp, str, base);
	tmp->type_write_char = 0;
	attribute_file_nod(stock, tmp);
	return (i);
}

int	write_in_file(int i, t_line *tmp, char *str, t_base *base)
{
	t_file	*stock;

	i++;
	stock = calloc(1, sizeof(t_file));
	if (str[i] == '<')
	{
		stock->type = HERE_DOC;
		i++;
	}
	else
		stock->type = INFILE;
	while (str[i] == ' ' || str[i] == 9)
		i++;
	if (stock->type == HERE_DOC)
		tmp->char_type = DOC;
	tmp->type_write_char = 1;
	stock->filename = write_char(&i, tmp, str, base);
	if (stock->type == HERE_DOC)
		tmp->char_type = STANDARD;
	tmp->type_write_char = 0;
	attribute_file_nod(stock, tmp);
	return (i);
}
