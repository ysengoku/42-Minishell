/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:28:04 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 15:28:06 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dc;
	const char	*sc;
	size_t		i;

	i = 0;
	dc = dest;
	sc = src;
	if (dc == 0 && sc == 0)
		return (0);
	while (i < n)
	{
		dc[i] = sc[i];
		i++;
	}
	return (dest);
}
