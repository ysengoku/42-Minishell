/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_UL_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:48:49 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 21:50:47 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned long	ft_expnt16(int a)
{
	unsigned long	i;

	i = 1;
	while (a > 0)
	{
		i = i * 16;
		a--;
	}
	return (i);
}

static void	ft_putlnbr(unsigned long n, char *srep, int a)
{
	size_t				i;
	unsigned long		tp;
	char				*exemple;

	exemple = "0123456789abcdef";
	i = 0;
	while (a > 0)
	{
		tp = n / (ft_expnt16(a));
		srep[i] = exemple[tp];
		n = n % ft_expnt16(a);
		a--;
		i++;
	}
	srep[i] = exemple[n];
}

char	*ft_itoa_ul_16(unsigned long n)
{
	int				expt;
	unsigned long	tmp;
	char			*srep;

	tmp = n;
	expt = 0;
	while (tmp >= 16)
	{
		tmp = tmp / 16;
		expt++;
	}
	tmp = expt + 2;
	srep = malloc(sizeof(char) * tmp);
	if (srep == 0)
		return (0);
	ft_putlnbr(n, srep, expt);
	srep[tmp - 1] = 0;
	return (srep);
}
