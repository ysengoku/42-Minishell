/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:51:23 by dvo               #+#    #+#             */
/*   Updated: 2024/04/06 18:39:41 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_error(int i, t_base *base)
{
	if (i == 1)
		ft_fprintf(2, "syntax error near unexpected token\n");
	if (i == 2)
		ft_fprintf(2, "export : '%s' : not a valid identifier\n", base->error_msg);
	if (i == 3)
		ft_fprintf(2, "parse error near\n");
	base->exit_code = 2;
}
