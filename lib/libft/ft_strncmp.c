/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:39:48 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 15:39:49 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)(s1);
	str2 = (unsigned char *)(s2);
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[i] && str1[i] == str2[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}
