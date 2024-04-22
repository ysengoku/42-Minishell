/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:28:22 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/22 07:58:29 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	convert_exitcode(char *s);
static int			check_value(char *s);
static int			argument_value_error(char *s);
static int			clear_before_exit(t_base *base, int exit_code);

int	ft_exit(t_base *base, t_line *node, int fd[2])
{
	int	exit_code;

	//write(2, "exit\n", 5); ///// commented for Tester
	if (node->arg[1])
	{
		if (convert_exitcode(node->arg[1]) != -1
			|| (strcmp(node->arg[1], "-1") == 0))
		{
			exit_code = convert_exitcode(node->arg[1]) % 256;
			if (node->arg[2])
			{
				free_base_content(base);
				return (print_err(EXIT, "too many arguments", NULL, 1));
			}
		}
		else
			exit_code = 2;
	}
	else if (g_received_signal != 0)
		exit_code = 128 + g_received_signal;
	else
		exit_code = base->exit_code;
	ft_close(fd[IN], fd[OUT], 0);
	exit(clear_before_exit(base, exit_code));
	return (0);
}

static long long	convert_exitcode(char *s)
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

static int	clear_before_exit(t_base *base, int exit_code)
{
	unlink_heredoc();
	rl_clear_history();
	free_base_content(base);
	free_envlist(base);
	free(base);
	return (exit_code);
}
