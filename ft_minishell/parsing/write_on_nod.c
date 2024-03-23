/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/03/23 17:52:48 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_simple_quote(int i, t_line *tmp, char *str)
{
	int		j;
	char	*quote;

	i++;
	j = 0;
	quote = calloc(1, sizeof(ft_strlen(str)));
	if (!quote)
		return (-1);
	while (str[i] != 39)
		quote[j++] = str[i++];
	quote[j] = '\0';
	j = 0;
	while (quote[j])
	{
		quote[j] = quote[j] * -1;
		j++;
	}
	i++;
	j = 0;
	while (tmp->arg[j])
		j++;
	tmp->arg[j] = quote;
	return (i);
}

int	write_double_quote(int i, t_line *tmp, char *str)
{
	int		j;
	char	*quote;

	i++;
	j = 0;
	quote = calloc(1, sizeof(ft_strlen(str)));
	if (!quote)
		return (-1);
	while (str[i] != 34)
		quote[j++] = str[i++];
	quote[j] = '\0';
	j = 0;
	while (quote[j])
	{
		quote[j] = quote[j] * -1;
		j++;
	}
	i++;
	j = 0;
	while (tmp->arg[j])
		j++;
	tmp->arg[j] = quote;
	return (i);
}

int	write_char(int i, t_line *tmp, char *str)
{
	int		j;
	char	*arg_string;
	int		last_arg;

	arg_string = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!arg_string)
		return (-1);
	j = 0;
	while (str[i] && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|' && str[i] != ' '\
	&& str[i] != 34 && str[i] != 39)
		arg_string[j++] = str[i++];
	arg_string[j] = '\0';
	last_arg = 0;
	while (tmp->arg[last_arg])
		last_arg++;
	tmp->arg[last_arg] = arg_string;
	return (i);
}

void	write_nod(int i, t_line *tmp, char *str)
{
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
			i = write_simple_quote(i, tmp, str);
		else
			i = write_char(i, tmp, str);
	}
}
