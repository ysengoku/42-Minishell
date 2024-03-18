/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:02:58 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 21:49:11 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_expnt(int a)
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

int	cnt_dec(int n)
{
	int	tmp;
	int	a;

	a = 0;
	tmp = n;
	while (tmp >= 10 || tmp <= -10)
	{
		tmp = tmp / 10;
		a++;
	}
	return (a);
}

int	ft_putnbr(int n, int out)
{
	int	a;
	int	sign;
	int	tmp;
	int	cnt;

	a = 0;
	sign = 1;
	cnt = 0;
	if (n < 0)
	{
		sign = -1;
		cnt = write (out, "-", 1);
		if (cnt == -1)
			return (-1);
	}
	a = cnt_dec(n) + 1;
	cnt = a + cnt;
	while (--a >= 0)
	{
		tmp = (sign * ((n / ft_expnt(a))) + 48);
		if (write (out, &tmp, 1) == -1)
			return (-1);
		n = n % ft_expnt(a);
	}
	return (cnt);
}
