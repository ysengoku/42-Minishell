/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_on_nod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:35:03 by dvo               #+#    #+#             */
/*   Updated: 2024/03/25 17:08:10 by dvo              ###   ########.fr       */
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

int	write_double_quote(int i, t_line *tmp, char *str, t_base *base)
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
	if (ft_strchr(quote, '$') != NULL)
		quote = translate_dollar(quote, base);
	j = 0;
	while (tmp->arg[j])
		j++;
	tmp->arg[j] = quote;
	return (i);
}

int	write_char(int i, t_line *tmp, char *str, t_base *base)
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
	if (ft_strchr(arg_string, '$') != NULL)
		arg_string = translate_dollar(arg_string, base);
	last_arg = 0;
	while (tmp->arg[last_arg])
		last_arg++;
	tmp->arg[last_arg] = arg_string;
	return (i);
}

void	write_nod(int i, t_line *tmp, char *str, t_base *base)
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
			i = write_double_quote(i, tmp, str, base);
		else if (str[i] == 39)
			i = write_simple_quote(i, tmp, str);
		else
			i = write_char(i, tmp, str, base);
	}
}
