/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:29:14 by dvo               #+#    #+#             */
/*   Updated: 2023/11/07 17:12:54 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	idst;
	size_t	iecrit;

	idst = 0;
	i = 0;
	iecrit = 0;
	while (src[i] != '\0')
		i++;
	while (idst < size && dst[idst] != '\0')
	{
		idst++;
		i++;
	}
	if (idst == size)
		return (i);
	while (src[iecrit] != '\0' && idst < size - 1)
	{
		dst[idst] = src[iecrit];
		iecrit++;
		idst++;
	}
	dst[idst] = '\0';
	return (i);
}
