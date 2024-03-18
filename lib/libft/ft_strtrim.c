/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:13:46 by dvo               #+#    #+#             */
/*   Updated: 2024/02/08 15:36:41 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(const char *s1, const char *set, int n)
{
	int	i;
	int	j;

	if (n == 1)
		j = 0;
	else
		j = ft_strlen(s1) - 1;
	i = 0;
	while (set[i])
	{
		if (set[i] == s1[j])
		{
			if (n == 1)
				j++;
			else
				j--;
			i = 0;
		}
		else
			i++;
	}
	return (j);
}

static char	*ft_strldup( const char *src, int l)
{
	char	*p;
	int		i;

	i = 0;
	l++;
	p = malloc (sizeof(char) * (l));
	if (p == NULL)
		return (0);
	while (src[i] && i < l - 1)
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*srep;
	int		i;
	int		maxl;

	if (!s1)
		return (NULL);
	i = ft_compare(s1, set, 1);
	maxl = ft_compare(s1, set, 0) + 1;
	if (maxl - i < 1)
	{
		srep = ft_calloc(1, 1);
		return (srep);
	}
	srep = ft_strldup((s1 + i), (maxl - i));
	return (srep);
}
