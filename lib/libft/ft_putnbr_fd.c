/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:02:58 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:02:59 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_expnt(int a)
{
	int	res;

	res = 1;
	while (a > 0)
	{
		res = res * 10;
		a--;
	}
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	a;
	int	sign;
	int	tmp;

	a = 0;
	sign = 1;
	if (n < 0)
	{
		sign = -1;
		write (fd, "-", 1);
	}
	tmp = n;
	while (tmp >= 10 || tmp <= -10)
	{
		tmp = tmp / 10;
		a++;
	}
	while (a >= 0)
	{
		tmp = sign * ((n / ft_expnt(a)) + (48 * sign));
		write (fd, &tmp, 1);
		n = n - (sign *((tmp - 48) * ft_expnt(a)));
		a--;
	}
}
