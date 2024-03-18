/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:35:23 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:35:24 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strldup(char *str, const char *c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len - 1)
	{
		str[i] = c[i];
		i++;
	}
	str[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		max;

	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if ((len == 0) || (start > INT_MAX) || (start >= ft_strlen(s)))
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	if (len + start < ft_strlen(s))
		max = len + 1;
	else
		max = ft_strlen(s) - start + 1;
	str = malloc(sizeof(char) * (max));
	if (str == 0)
		return (str);
	ft_strldup(str, s + start, max);
	return (str);
}
