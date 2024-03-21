/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chara_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:58 by dvo               #+#    #+#             */
/*   Updated: 2024/03/21 14:36:46 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_string(t_line *line)
{
	//printf("arg=%i, in=%i, out=%i\n", line->count->nb_arg, line->count->nb_in, line->count->nb_out);
	line->arg = calloc(line->count->nb_arg + 1, sizeof(char*));
	line->read = calloc(line->count->nb_in + 1, sizeof(char*));
	line->write = calloc(line->count->nb_out + 1, sizeof(char *));
}

void	create_nod(t_line **line, char *str)
{
	t_line	*tmp;
	t_line	*nxt;
	int		i;
	
	(void)nxt;
	i = 0;
	nxt = *line;
	tmp = ft_calloc(1, sizeof(t_line));
	tmp->next = NULL;
	cnt_param(str, tmp);
	malloc_string(tmp);
	while (str[i])
	{
		if (str[i] == '>')
			i = write_out_file(i, tmp, str);
		else if (str[i] == '<')
			i = write_in_file(i, tmp, str);
		else if (str[i] == ' ')
			i++;
		else if (str[i] == 34)
			i = write_double_quote(i, tmp, str);
		else if (str[i] == 39)
		{
			printf("%i\n", i);
			i = write_simple_quote(i, tmp, str);
		}
		else
			i = write_char(i, tmp, str);
	}
	if (*line == NULL)
		*line = tmp;
	else
	{
		while (nxt->next)
			nxt = nxt->next;
		nxt->next = tmp;
	}
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

char	**ft_chara_split(char *s, t_base *base)
{
	char		**srep;
	int			i;
	t_line		*line;

	i = 0;
	line = NULL;
	if (ft_strlen(s) == 0)
		return (ft_calloc(1, sizeof(char *)));
	s = check_quote(s);
	srep = ft_split(s, '|');
	while (srep[i])
	{
		create_nod(&line, srep[i]);
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
	// 	i = 0;
	// 	while (line->read && line->read[i])
	// 	{
	// 		printf("infile[%i] is :%s\n", i, line->read[i]);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	while (line->write && line->write[i])
	// 	{
	// 		printf("outfile[%i] is :%s\n", i, line->write[i]);
	// 		i++;
	// 	}
	// 	line = line->next;
	// }
	base->lst = line;
	return (srep);
}
