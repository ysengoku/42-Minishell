/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:25:55 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:25:56 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int srch)
{
	int		i;
	int		max;
	char	*c;
	char	cch;

	cch = srch;
	max = 0;
	c = (char *)(str);
	while (c[max])
		max++;
	if (cch == '\0')
		return (c + max);
	i = max - 1;
	while (i >= 0 && c[i] != cch)
		i--;
	if (i < 0)
		return (0);
	return (c + i);
}
