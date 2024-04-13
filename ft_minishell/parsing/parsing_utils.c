/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:15:56 by dvo               #+#    #+#             */
/*   Updated: 2024/04/13 21:49:35 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	enter_quote_mode(char *str, int i, t_line *tmp)
{
	if (str[i] == 34 && tmp->char_type == STANDARD)
		tmp->char_type = DOUBLE_Q;
	else if (str[i] == 39 && tmp->char_type == STANDARD)
		tmp->char_type = QUOTE;
	else if (str[i] == 34 && tmp->char_type == DOUBLE_Q)
		tmp->char_type = STANDARD;
	else if (str[i] == 39 && tmp->char_type == QUOTE)
		tmp->char_type = STANDARD;
	else if (str[i] == 34 && tmp->char_type == DOC)
		tmp->char_type = DOC_DOUBLE_Q;
	else if (str[i] == 39 && tmp->char_type == DOC)
		tmp->char_type = DOC_QUOTE;
	else if (str[i] == 34 && tmp->char_type == DOC_DOUBLE_Q)
		tmp->char_type = DOC;
	else if (str[i] == 39 && tmp->char_type == DOC_QUOTE)
		tmp->char_type = DOC;
	else
		return (0);
	return (1);
}

void	ft_new_arg( t_line *tmp, char *res, int j)
{
	char	*str;
	int		i;
	int 	last_nod;
	
	i = 0;
	str = ft_calloc(j + 2, sizeof(char));
	while( i < j)
	{
		str[i] = res[i];
		i++;
	}
	str[i] = '\0';
	last_nod = 0;
	while (tmp->arg[last_nod])
		last_nod++;
	tmp->arg[last_nod] = str;
	i = 0;
	j++;
	while (res[j])
		res[i++] = res[j++];
	while (res[i])
		res[i++] = '\0';
	tmp->type_write_char = 2;
}

int	index_dollars(char *str, int *ptr_i, t_line *tmp, char *res)
{
	int	j;
	int	i;

	i = *ptr_i + 1;
	j = 0;
	while (res && res[j])
	{
		if ((j >= i || tmp->type_write_char == 2) && res[j] == ' ')
		{
			if (tmp->type_write_char == 0 || tmp->type_write_char == 2)
				ft_new_arg(tmp, res, j);
			else
				return(ft_display_error(4, NULL), -1);
			j = 0;
		}
		j++;
	}
	tmp->type_write_char = 0;
	if (str[i] != '?')
	{
		while ((str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '='\
		&& str[i] != '|' && str[i] != '>' && str[i] != '$' && str[i] != '.' \
		&& str[i] != 34 && str[i] != 39 && str[i] != 9 && str[i] != 47))
		{
			if (enter_quote_mode(str, i, tmp) == 1)
			{
				i++;
				break ;
			}
			if (str[i] == '$' && tmp->char_type != QUOTE)
				break ;
			i++;
		}
		i--;
	}
	*ptr_i = i;
	return (j);
}
