/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:22:44 by dvo               #+#    #+#             */
/*   Updated: 2024/02/08 15:06:35 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add(char const *str1, char const *str2, size_t i, char *srep)
{
	while (str1 && str1[i])
	{
		srep[i] = (str1[i]);
		i++;
	}
	srep[i] = '/';
	i++;
	while (str2 && str2[i - ft_strlen(str1) - 1])
	{
		srep[i] = (str2[i - ft_strlen(str1) - 1]);
		i++;
	}
	srep[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*srep;
	size_t		i;

	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (i <= 1)
	{
		srep = ft_calloc(1, 1);
		return (srep);
	}
	srep = malloc(sizeof(char) * i + 1);
	if (srep == 0)
		return (0);
	i = 0;
	add(s1, s2, i, srep);
	return (srep);
}
