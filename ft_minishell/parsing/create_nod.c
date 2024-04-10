/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:50:22 by dvo               #+#    #+#             */
/*   Updated: 2024/04/09 16:27:20 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	attribute_nod(t_base *base, t_line	*tmp)
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
	tmp->char_type = STANDARD;
	if (cnt_param(str, tmp) == -1)
	{
		free(tmp);
		ft_display_error(1, base);
		return (-1);
	}
	tmp->arg = ft_calloc(tmp->nb_arg + 1, sizeof(char *));
	write_nod(i, tmp, str, base);
	attribute_nod(base, tmp);
	return (0);
}
