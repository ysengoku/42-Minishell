/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:50:27 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/03 07:53:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err_malloc(void)
{
	write(2, "minishell: Fatal: memory allocation failed\n", 44);
	return (1);
}

void	exit_after_malloc_fail(t_base *base, void *s, char **arr)
{
	print_err_malloc();
	if (s)
		free(s);
	if (arr)
		ft_free_strarr(arr);
	exit(clear_before_exit(base, 1));
}

int	free_error_env(t_env *tmp, int i, t_base *base)
{
	if (tmp->value)
		free (tmp->value);
	free(base->env[i]);
	base->env[i] = NULL;
	return (-1);
}

void	check_error_write_char(t_norm *norm, char *res)
{
	if (norm->j == -1)
	{
		free(res);
		res = NULL;
		norm->i = -1;
	}
}
