/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:36:45 by dvo               #+#    #+#             */
/*   Updated: 2024/02/11 20:46:08 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

/*
int	ft_strchr(const char *str, char cch)
{
	size_t		i;
	char		*c;

	i = 0;
	c = (char *)(str);
	while (c[i] != cch && c[i] != '\0')
		i++;
	if (cch == '\0' && c[i] == '\0')
		return (1);
	if (c[i] == '\0')
		return (0);
	return (1);
}
*/