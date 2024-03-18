/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:28:09 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 15:28:11 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int srch, size_t n)
{
	size_t	i;
	char	*c;
	char	crh;

	crh = srch;
	c = (char *)(str);
	i = 0;
	while (i < n && c[i] != crh)
		i++;
	if (i == n)
		return (0);
	return (c + i);
}
