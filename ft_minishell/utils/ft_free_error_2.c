/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_error_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:08:05 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 20:14:19 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_error_env(t_env *tmp, int i, t_base *base)
{
	if (tmp->value)
		free (tmp->value);
	free(base->env[i]);
	base->env[i] = NULL;
	return (-1);
}

void	check_error_write_char(t_norm *norm, char *res)
{
	if (norm->j == -1)
	{
		free(res);
		res = NULL;
		norm->i = -1;
	}
}
