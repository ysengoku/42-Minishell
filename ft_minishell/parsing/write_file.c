/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:31 by dvo               #+#    #+#             */
/*   Updated: 2024/04/19 10:32:37 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	attribute_file_nod(t_file *stock, t_line *tmp)
{
	t_file	*last;

	if (!stock->filename && !stock->next)
	{
		free (stock);
		return ;
	}
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
	stock = ft_calloc(1, sizeof(t_file));
	if (str[i] == '>')
	{
		stock->type = OUT_APPEND;
		i++;
	}
	else
		stock->type = OUT_TRUNC;
	while (str[i] == ' ')
		i++;
	tmp->typ_write_chr = 1;
	stock->filename = write_char(&i, tmp, str, base);
	if (!stock->filename)
		tmp->error_syntax = 1;
	tmp->typ_write_chr = 0;
	attribute_file_nod(stock, tmp);
	return (i);
}

int	write_in_file(int i, t_line *tmp, char *str, t_base *base)
{
	t_file	*stock;

	i++;
	stock = ft_calloc(1, sizeof(t_file));
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
	tmp->typ_write_chr = 1;
	stock->filename = write_char(&i, tmp, str, base);
	if (!stock->filename)
		tmp->error_syntax = 1;
	if (stock->type == HERE_DOC)
		tmp->char_type = STANDARD;
	tmp->typ_write_chr = 0;
	attribute_file_nod(stock, tmp);
	return (i);
}
