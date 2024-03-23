/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:44:12 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 15:44:15 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char		*p;
	size_t		i;
	size_t		j;
	char		*c;

	c = (char *)(src);
	i = 0;
	j = ft_strlen(c) + 1;
	p = malloc (sizeof(char) * (j));
	if (p == NULL)
		return (0);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
