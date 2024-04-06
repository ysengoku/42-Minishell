/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chara_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:58 by dvo               #+#    #+#             */
/*   Updated: 2024/04/07 00:21:52 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_nod(char *str, t_base *base)
{
	t_line	*tmp;
	t_line	*nxt;
	int		i;

	i = 0;
	nxt = base->lst;
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
	if (base->lst == NULL)
		base->lst = tmp;
	else
	{
		while (nxt->next)
			nxt = nxt->next;
		nxt->next = tmp;
	}
	return (0);
}

char	*check_quote(char *s, t_base *base)
{
	int			i;
	t_line		line;

	ft_bzero(&line, sizeof(t_line));
	line.char_type = STANDARD;
	i = 0;
	while (s[i])
	{
		if (s[i] == '|' && line.char_type == STANDARD)
		{
			i++;
			while (s[i] == ' ' || s[i] == 9)
				i++;
			if (s[i] == '|' || s[i] == '\0')
				return (ft_display_error(3, base), NULL);
		}
		if (s[i] == 39 || s[i] == 34)
			enter_quote_mode(s, i, &line);
		else if (line.char_type != STANDARD)
			s[i] = s[i] * -1;
		i++;
	}
	if (line.char_type != STANDARD)
		return (ft_display_error(3, base), NULL); 
	return (s);
}

int	ft_chara_split(char *s, t_base **base)
{
	char		**srep;
	int			i;

	i = 0;
	s = check_quote(s, *base);
	if (s == NULL)
		return (-1);
	srep = ft_split(s, '|');
	while (srep[i])
	{
		srep[i] = check_quote(srep[i], *base);
		if (create_nod(srep[i], *base) == -1)
		{
			free_base_content(*base);
			return (ft_free_strarr(srep), -1);
		}
		i++;
	}
	ft_free_strarr(srep);
	return (0);
}
