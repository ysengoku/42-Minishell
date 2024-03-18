/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:50:59 by dvo               #+#    #+#             */
/*   Updated: 2024/02/04 22:13:51 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_result(const char *c, va_list ptr, int out)
{
	int		cnt;
	size_t	i;
	int		error;

	cnt = 0;
	i = 0;
	while (c[i])
	{
		if (c[i] == '%')
		{
			i++;
			error = ft_direction(c[i], ptr, out);
			cnt = cnt + error;
		}
		else
		{
			error = write(out, &c[i], 1);
			cnt++;
		}
		if (error == -1)
			return (-1);
		i++;
	}
	return (cnt);
}

int	ft_fprintf(int out, const char *c, ...)
{
	va_list	ptr;
	int		cnt;

	if (c == NULL)
		return (-1);
	va_start(ptr, c);
	cnt = write_result(c, ptr, out);
	va_end(ptr);
	return (cnt);
}
