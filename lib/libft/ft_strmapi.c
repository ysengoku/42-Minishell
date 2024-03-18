/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:10:52 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:10:54 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	char		*srep;
	size_t		len;

	i = 0;
	len = ft_strlen(s) + 1;
	srep = malloc(sizeof(char) * len);
	if (srep == 0)
		return (0);
	while (s[i])
	{
		srep[i] = f(i, s[i]);
		i++;
	}
	srep[i] = 0;
	return (srep);
}
