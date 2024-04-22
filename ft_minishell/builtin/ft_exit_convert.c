/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:54:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/22 15:14:02 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			check_value(char *s);
static int			argument_value_error(char *s);

long long	convert_exitcode(char *s)
{
	int			i;
	long long	sign;
	long long	nbr;

	if (check_value(s) == -1)
		return (-1);
	i = 0;
	sign = 1;
	nbr = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i])
	{
		if ((nbr > LLONG_MAX / 10)
			|| (sign == 1 && nbr == LLONG_MAX / 10 && (s[i] - '0') > 7)
			|| (sign == -1 && nbr == LLONG_MAX / 10 && (s[i] - '0') > 8))
			return (argument_value_error(s));
		nbr = nbr * 10 + (s[i] - '0');
		i++;
	}
	return (nbr * sign);
}

static int	check_value(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (argument_value_error(s));
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (argument_value_error(s));
		i++;
	}
	if (((s[0] == '-' || s[0] == '+') && i > 21) || i > 20)
		return (argument_value_error(s));
	return (0);
}

static int	argument_value_error(char *s)
{
	ft_fprintf(2, "minishell: exit: %s: numeric argument required\n", s);
	return (-1);
}
