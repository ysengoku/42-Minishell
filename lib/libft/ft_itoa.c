/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:44:33 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 15:44:35 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_expnt(int a)
{
	int	i;

	i = 1;
	while (a > 0)
	{
		i = i * 10;
		a--;
	}
	return (i);
}

static void	ft_putlnbr(int n, char *srep, int a)
{
	int	i;
	int	tp;

	i = 0;
	if (n < 0)
	{
		srep[i] = '-';
		srep[1] = '0' - (n / ft_expnt(a));
		n = n % ft_expnt(a);
		n = n * -1;
		i = 2;
		a--;
	}
	while (a > 0)
	{
		tp = n / (ft_expnt(a));
		srep[i] = tp + '0';
		n = n % ft_expnt(a);
		a--;
		i++;
	}
	srep[i] = n + '0';
}

char	*ft_itoa(int n)
{
	int		expt;
	int		i;
	int		tmp;
	char	*srep;

	i = 0;
	if (n < 0)
		i++;
	tmp = n;
	expt = 0;
	while (tmp >= 10 || tmp <= -10)
	{
		tmp = tmp / 10;
		expt++;
	}
	tmp = expt + i + 2;
	srep = malloc(sizeof(char) * tmp);
	if (srep == 0)
		return (0);
	ft_putlnbr(n, srep, expt);
	srep[tmp - 1] = 0;
	return (srep);
}
