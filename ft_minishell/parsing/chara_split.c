/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chara_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:58 by dvo               #+#    #+#             */
/*   Updated: 2024/04/10 17:19:25 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_next(char *s, t_base *base, t_line *line, int i)
{
	while (s[i])
	{
		if (s[i] == '|' && line->char_type == STANDARD)
		{
			i++;
			while (s[i] == ' ' || s[i] == 9)
				i++;
			if (s[i] == '|' || s[i] == '\0')
				return (ft_display_error(1, base), -1);
		}
		if (s[i] == 39 || s[i] == 34)
			enter_quote_mode(s, i, line);
		else if (line->char_type != STANDARD)
			s[i] = s[i] * -1;
		i++;
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
	while (s[i] == ' ' || s[i] == 9)
		i++;
	if (s[i] == '|')
		return (ft_display_error(1, base), NULL);
	if (check_quote_next(s, base, &line, i) == -1)
		return (NULL);
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
			if ((*base)->lst == NULL)
				return (ft_free_strarr(srep), -1);
			else
				return (0);
		}
		i++;
	}
	ft_free_strarr(srep);
	return (0);
}
