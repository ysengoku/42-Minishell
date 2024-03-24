/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:55:24 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 12:55:45 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *s1, char *s2, int exit_status)
{
	write(2, "minishell:", 10);
	write(2, s1, ft_strlen(s1));
	if (s2)
	{
		write(2, ": ", 2);
		write(2, s2, ft_strlen(s2));
	}
	write(2, "\n", 1);
	return (exit_status);
}
