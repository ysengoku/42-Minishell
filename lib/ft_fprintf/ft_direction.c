/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:25:29 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 21:52:33 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_unknow_c(char type_var, int out)
{
	ssize_t	error;

	if (type_var == '\0')
		return (-1);
	error = write(out, "%", 1);
	if (error == -1)
		return (-1);
	error = write(out, &type_var, 1);
	if (error == -1)
		return (-1);
	return (2);
}

int	ft_direction(char type_var, va_list ptr, int out)
{
	if (type_var == 's')
		return (ft_write_string(va_arg(ptr, char *), out));
	else if (type_var == 'c')
		return (ft_write_char(va_arg(ptr, int), out));
	else if (type_var == 'i' || type_var == 'd')
		return (ft_write_int(va_arg(ptr, int), out));
	else if (type_var == 'u')
		return (ft_write_un_dec(va_arg(ptr, unsigned int), out));
	else if (type_var == 'x')
		return (ft_write_hexa_low(va_arg(ptr, unsigned int), out));
	else if (type_var == 'X')
		return (ft_write_hexa_upp(va_arg(ptr, unsigned int), out));
	else if (type_var == 'p')
		return (ft_write_ptr(va_arg(ptr, unsigned long), out));
	else if (type_var == '%')
		return (write(out, &type_var, 1));
	else
	{
		return (ft_unknow_c(type_var, out));
	}
	return (2);
}
