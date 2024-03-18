/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:36:34 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:36:35 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(const char *str, int sign)
{
	unsigned long long int	max;
	int						a;

	a = 0;
	max = 0;
	while (str[a] >= '0' && str[a] <= '9' && (a < 19))
	{
		max = max * 10 + (str[a] - '0');
		a++;
	}
	if (a == 19 && str[a] >= '0' && str[a] <= '9')
	{
		if (sign < 0)
			return (0);
		if (sign > 0)
			return (-1);
	}
	if (sign < 0)
		max--;
	if (max >= LLONG_MAX && sign < 0)
		return (0);
	if (max >= LLONG_MAX && sign > 0)
		return (-1);
	return (1);
}

static int	condition(const char *str, int l)
{
	int	i;

	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' && l == 0)
	{
		i++;
		return (-1);
	}
	else if (str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	result = 0;
	sign = 1;
	i = condition(str, 1);
	if (condition(str, 0) == -1)
	{
		sign = -1;
		i++;
	}
	if (ft_overflow(str + i, sign) != 1)
		return (ft_overflow(str + i, sign));
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	result = result * sign;
	return (result);
}
