/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:25:19 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/20 09:27:06 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write(char *st1, char *st2)
{
	write(2, st1, ft_strlen(st1));
	if (st2)
	{
		write(2, ": ", 2);
		write(2, st2, ft_strlen(st2));
	}
	write(2, "\n", 1);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;
	
	i = 0;
    while ((s1[i] || s2[i]) && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}
