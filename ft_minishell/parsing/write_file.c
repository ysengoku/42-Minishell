/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:30:31 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 18:04:56 by yusengok         ###   ########.fr       */
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
	stock = ft_calloc(1, sizeof(t_file)); //FIXED
	if (!stock)
		exit_after_malloc_fail(base, NULL, NULL);
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
	if (i == -1)
		exit_after_malloc_fail(base, stock, NULL);
	if (!stock->filename)
		tmp->error_syntax = 1;
	tmp->typ_write_chr = 0;
	attribute_file_nod(stock, tmp);
	return (i);
}

static void	check_quote_here_doc(int i, char *str, t_file *stock, t_line *tmp)
{
	if (stock->type == HERE_DOC)
	{
		while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>')
		{
			if (str[i] == 34 || str[i] == 39)
			{
				stock->type = HERE_DOC_NO;
				if (str[i] == 34)
					tmp->char_type = DOC_DOUBLE_Q;
				else
					tmp->char_type = DOC_QUOTE;
				return ;
			}
			i++;
		}
	}
}

int	write_in_file(int i, t_line *tmp, char *str, t_base *base)
{
	t_file	*stock;

	i++;
	stock = ft_calloc(1, sizeof(t_file)); //FIXED
	if (!stock)
		exit_after_malloc_fail(base, NULL, NULL);
	if (str[i] == '<')
	{
		stock->type = HERE_DOC;
		i++;
	}
	else
		stock->type = INFILE;
	while (str[i] == ' ' || str[i] == 9)
		i++;
	check_quote_here_doc(i, str, stock, tmp);
	if (stock->type == HERE_DOC)
		tmp->char_type = DOC;
	tmp->typ_write_chr = 1;
	stock->filename = write_char(&i, tmp, str, base);
	if (i == -1)
		exit_after_malloc_fail(base, stock, NULL);
	if (!stock->filename)
		tmp->error_syntax = 1;
	if (stock->type == HERE_DOC)
		tmp->char_type = STANDARD;
	tmp->typ_write_chr = 0;
	attribute_file_nod(stock, tmp);
	return (i);
}
