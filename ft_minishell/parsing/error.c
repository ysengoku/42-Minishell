/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:51:23 by dvo               #+#    #+#             */
/*   Updated: 2024/03/27 14:50:25 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_error(int i)
{
	if (i == 1)
		ft_fprintf(2, "syntax error near unexpected token\n");
}
