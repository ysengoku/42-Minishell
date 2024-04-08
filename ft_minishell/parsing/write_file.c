/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:31 by dvo               #+#    #+#             */
/*   Updated: 2024/04/08 14:38:26 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (str[i] == ' ')
		i++;
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
	while (str[i] == ' ' || str[i] == 9)
		i++;
	if (stock->type == HERE_DOC)
		tmp->char_type = DOC;
	stock->filename = write_char(&i, tmp, str, base);
	if (stock->type == HERE_DOC)
		tmp->char_type = STANDARD;
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
