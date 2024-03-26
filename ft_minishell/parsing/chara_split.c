/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chara_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:58 by dvo               #+#    #+#             */
/*   Updated: 2024/03/25 16:17:13 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_nod(t_line **line, char *str, t_base *base)
{
	t_line	*tmp;
	t_line	*nxt;
	int		i;

	i = 0;
	nxt = *line;
	tmp = ft_calloc(1, sizeof(t_line));
	if (!tmp)
		return (-1);
	tmp->next = NULL;
	tmp->file = NULL;
	if (cnt_param(str, tmp) == -1)
		return (ft_display_error(1), -1);
	tmp->arg = ft_calloc(tmp->nb_arg + 1, sizeof(char*));
	write_nod(i, tmp, str, base);
	if (*line == NULL)
		*line = tmp;
	else
	{
		while (nxt->next)
			nxt = nxt->next;
		nxt->next = tmp;
	}
	return (0);
}

char	*check_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39)
			{
				s[i] = s[i] * (-1);
				i++;
			}
			if (!s[i])
				return (NULL);
		}
		if (s[i] == 34)
		{
			i++;
			while (s[i] && s[i] != 34)
			{
				s[i] = s[i] * (-1);
				i++;
			}
			if (!s[i])
				return (NULL);
		}
		i++;
	}
	return (s);
}

int	ft_chara_split(char *s, t_base **base)
{
	char		**srep;
	int			i;
	t_line		*line;

	i = 0;
	line = NULL;
	s = check_quote(s);
	srep = ft_split(s, '|');
	while (srep[i])
	{
		if (create_nod(&line, srep[i], *base) == -1)
			return (-1);
		i++;
	}
	// while (line)
	// {
	// 	i = 0;
	// 	while (line->arg && line->arg[i])
	// 	{
	// 		printf("arg[%i] is:%s\n", i, line->arg[i]);
	// 		i++;
	// 	}
	// 	while(line->file)
	// 	{
	// 		printf("file: %s, is type %d\n", line->file->filename, line->file->type);
	// 		line->file = line->file->next;
	// 	}
	// 	line = line->next;
	// }
	// exit(1);
	(*base)->lst = line;
	return (0);
}
