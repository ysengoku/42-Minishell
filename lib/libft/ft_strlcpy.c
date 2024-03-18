/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:06:38 by dvo               #+#    #+#             */
/*   Updated: 2023/11/07 17:26:41 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	test;

	i = 0;
	while (src[i] != '\0')
		i++;
	if (size != 0)
	{
		test = 0;
		while (test < size - 1 && src[test] != '\0')
		{
			dest[test] = src[test];
			test++;
		}
		dest[test] = '\0';
	}
	return (i);
}
