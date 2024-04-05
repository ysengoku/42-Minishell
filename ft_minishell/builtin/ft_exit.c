/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:28:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/05 13:43:02 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	convert_exitcode(char *s);
static int			check_value(char *s);
static int			argument_value_error(char *s);

void	ft_exit(t_base *base, t_line *node, int fd[2])
{
	int	exit_code;

	if (node->arg[1])
		exit_code = convert_exitcode(node->arg[1]) % 256;
	else
		exit_code = 0;
	ft_close(fd[IN], fd[OUT], 0);
	unlink_heredoc();
	rl_clear_history();
	free_base_content(base);
	free_envlist(base);
	free(base);
	write(1, "exit\n", 5);
	exit(exit_code);
}

static long long	convert_exitcode(char *s)
{
	int			i;
	long long	sign;
	long long	nbr;

	if (check_value(s) == 2)
		return (2);
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
		nbr += (s[i] - '0');
		if (s[i + 1])
			nbr *= 10;
		if ((sign == 1 && nbr < 0) || (sign == -1 && nbr > 0))
			return (argument_value_error(s));
		i++;
	}
	return (nbr * sign);
}

static int	check_value(char *s)
{
	int	i;

	i = 0;
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
	return (2);
}
