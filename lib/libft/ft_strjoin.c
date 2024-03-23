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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	res_len;
	unsigned int	i;
	unsigned int	j;

	res_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(res_len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

/*
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
*/