/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:55:24 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/12 23:33:14 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err(char *s1, char *s2, char *s3, int exit_status)
{
	write(2, "minishell: ", 11);
	write(2, s1, ft_strlen(s1));
	if (s2)
	{
		write(2, ": ", 2);
		write(2, s2, ft_strlen(s2));
	}
	if (s3)
	{
		write(2, ": ", 2);
		write(2, s3, ft_strlen(s3));
	}
	write(2, "\n", 1);
	return (exit_status);
}

void	ft_display_error(int i, t_base *base)
{
	if (i == 1)
		ft_fprintf(2, "syntax error near unexpected token\n");
	if (i == 2)
		ft_fprintf(2, "export : '%s' : not a valid identifier\n",
			base->error_msg);
	if (i == 3)
		ft_fprintf(2, "parse error near\n");
	if (i == 4)
		ft_fprintf(2, "ambiguous redirect\n");
	base->exit_code = 2;
}

int	ft_perror(const char *s, int exit_status)
{
	write(2, "minishell: ", 11);
	perror(s);
	return (exit_status);
}
