/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:26 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:27:28 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(char *ctr, char *csrh, size_t len, size_t i)
{
	size_t	isr;

	isr = 0;
	while (ctr[isr] == csrh[isr] && (isr + i < len && csrh[isr]))
	{
		isr++;
	}
	if (csrh[isr] == '\0')
		return (1);
	return (0);
}

char	*ft_strnstr(const char *str, const char *srch, size_t len)
{
	size_t				i;
	char				*ctr;
	char				*csrh;

	len = (long int)(len);
	ctr = (char *)(str);
	csrh = (char *)(srch);
	if (csrh[0] == 0)
		return (ctr);
	if (ctr == 0 && len == 0)
		return (0);
	i = 0;
	while (ctr[i] && i < len)
	{
		if (ctr[i] == csrh[0])
		{
			if (ft_compare(ctr + i, csrh, len, i) == 1)
				return (ctr + i);
		}
		i++;
	}
	return (0);
}
