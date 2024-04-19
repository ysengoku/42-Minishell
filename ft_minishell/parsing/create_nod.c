/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:50:22 by dvo               #+#    #+#             */
/*   Updated: 2024/04/19 15:32:00 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_arg(int i, t_line *tmp, char *str, t_base *base)
{
	char	*arg;
	int		last_nod;

	arg = write_char(&i, tmp, str, base);
	if (!arg)
		return (i);
	last_nod = 0;
	while (tmp->arg[last_nod])
		last_nod++;
	tmp->arg[last_nod] = arg;
	return (i);
}

static void	attribute_nod(t_base *base, t_line	*tmp)
{
	t_line	*nxt;

	nxt = base->lst;
	if (base->lst == NULL)
		base->lst = tmp;
	else
	{
		while (nxt->next)
			nxt = nxt->next;
		nxt->next = tmp;
	}
}

static void	write_nod(int i, t_line *tmp, char *str, t_base *base)
{
	while (str[i])
	{
		if (str[i] == '>')
			i = write_out_file(i, tmp, str, base);
		else if (str[i] == '<')
			i = write_in_file(i, tmp, str, base);
		else if (str[i] == ' ' || str[i] == 9)
			i++;
		else
			i = write_arg(i, tmp, str, base);
	}
}

int	create_nod(char *str, t_base *base)
{
	t_line	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(1, sizeof(t_line));
	if (!tmp)
		return (-1);
	tmp->next = NULL;
	tmp->file = NULL;
	tmp->nb_arg = base->max_arg_export;
	tmp->char_type = STANDARD;
	if (cnt_param(&str, tmp) == -1)
	{
		tmp->nb_arg = 0;
		cnt_param(&str, tmp);
		ft_display_error(1, base);
		tmp->error_syntax = 1;
	}
	tmp->arg = ft_calloc(tmp->nb_arg + 2, sizeof(char *));
	write_nod(i, tmp, str, base);
	attribute_nod(base, tmp);
	if (tmp->error_syntax == 1)
		return (-1);
	return (0);
}
