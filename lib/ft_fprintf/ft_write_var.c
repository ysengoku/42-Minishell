/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:25:42 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 21:50:18 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_char(int c, int out)
{
	return (write(out, &c, 1));
}

int	ft_write_string(char *s, int out)
{
	size_t	i;
	ssize_t	error;

	i = 0;
	if (s == NULL)
		s = "(null)";
	while (s[i])
	{
		error = write(out, &s[i], 1);
		if (error == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_write_int(int rep, int out)
{
	return (ft_putnbr(rep, out));
}

int	ft_write_un_dec(unsigned int n, int out)
{
	int				a;
	unsigned int	tmp;
	int				cmp;
	ssize_t			error;

	a = 0;
	tmp = n;
	while (tmp >= 10)
	{
		tmp = tmp / 10;
		a++;
	}
	cmp = a + 1;
	while (a >= 0)
	{
		tmp = ((n / ft_expnt(a)) + 48);
		error = write (out, &tmp, 1);
		if (error == -1)
			return (-1);
		n = n - ((tmp - 48) * ft_expnt(a));
		a--;
	}
	return (cmp);
}
