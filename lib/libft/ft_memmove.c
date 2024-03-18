/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:28:24 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 15:28:25 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*dc;
	const char		*sc;
	size_t			i;

	dc = dest;
	sc = src;
	i = n - 1;
	if (dc == 0 && sc == 0)
		return (0);
	if (dc > sc)
	{
		while (i + 1 > 0)
		{
			dc[i] = sc[i];
			i--;
		}
	}
	else
		ft_memcpy(dc, sc, n);
	return (dest);
}
