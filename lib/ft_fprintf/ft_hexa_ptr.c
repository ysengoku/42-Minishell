/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:48:34 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 22:13:37 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_hexa_low(unsigned int n, int out)
{
	size_t		i;
	char		*str;
	ssize_t		error;

	i = 0;
	str = ft_itoa_ul_16(n);
	while (str[i])
	{
		error = write(out, &str[i], 1);
		if (error == -1)
			return (-1);
		i++;
	}
	free(str);
	return (i);
}

int	ft_write_hexa_upp(unsigned int n, int out)
{
	char		*str;
	size_t		i;
	ssize_t		error;

	i = 0;
	str = ft_itoa_ul_16(n);
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		error = write(out, &str[i], 1);
		if (error == -1)
			return (-1);
		i++;
	}
	free(str);
	return (i);
}

int	ft_write_ptr(unsigned long n, int out)
{
	char		*str;
	size_t		i;
	ssize_t		error;

	i = 0;
	if (n == 0)
	{
		error = write(1, "(nil)", 5);
		if (error == -1)
			return (-1);
		return (5);
	}
	str = ft_itoa_ul_16(n);
	write (out, "0x", 2);
	while (str[i])
	{
		error = write(out, &str[i], 1);
		if (error == -1)
			return (-1);
		i++;
	}
	i = i + 2;
	free(str);
	return (i);
}
