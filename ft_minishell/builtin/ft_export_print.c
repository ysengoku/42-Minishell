/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:34:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/10 09:40:36 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_line(int fd_out, t_env *print);
static int	check_end(t_base *base);
static void	reset_order(t_base *base);

int	export_null(t_base *base, int fd[2])
{
	t_env	*tmp;
	t_env	*print;

	while (check_end(base) == 0)
	{
		tmp = base->envn;
		print = tmp;
		while (print->order != 0)
			print = print->next;
		while (tmp)
		{
			if (tmp->order == 0 && strcmp(print->key, tmp->key) > 0)
				print = tmp;
			tmp = tmp->next;
		}
		if (strcmp(print->key, "_") != 0)
			print_line(fd[OUT], print);
		print->order = 1;
	}
	reset_order(base);
	return (ft_close(fd[IN], fd[OUT], 0));
}

static void	print_line(int fd_out, t_env *print)
{
	ft_fprintf(fd_out, "declare -x %s", print->key);
	if (print->value)
		ft_fprintf(fd_out, "=\"%s\"", print->value);
	ft_fprintf(fd_out, "\n");
}

static int	check_end(t_base *base)
{
	t_env	*check;

	check = base->envn;
	while (check)
	{
		if (check->order == 0)
			return (0);
		check = check->next;
	}
	return (1);
}

static void	reset_order(t_base *base)
{
	t_env	*reset;

	reset = base->envn;
	while (reset)
	{
		reset->order = 0;
		reset = reset->next;
	}
}
