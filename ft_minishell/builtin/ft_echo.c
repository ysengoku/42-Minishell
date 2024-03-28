/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:16:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/28 10:44:11 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_newline(char **s, int *i, int *newline);

int	ft_echo(t_base *base)
{
	int	i;
	int	newline;
	int	fd[2];

	fd[IN] = STDIN_FILENO;
	fd[OUT] = STDOUT_FILENO;
	if (check_redirection(base, &fd[IN], &fd[OUT]) == 1)
		return (EXIT_FAILURE);
	i = 1;
	check_newline(base->lst->arg, &i, &newline);
	while (base->lst->arg[i])
	{
		write(fd[OUT], base->lst->arg[i], ft_strlen(base->lst->arg[i]));
		if (base->lst->arg[++i])
			write (fd[OUT], " ", 1);
	}
	if (newline)
		write (fd[OUT], "\n", 1);
	return (ft_close(fd[IN], fd[OUT], 0));
}

static void	check_newline(char **arg, int *i, int *newline)
{
	int	j;

	j = 0;
	if (arg[*i][j] != '-')
		return ;
	j++;
	while (arg[*i][j])
	{
		if (arg[*i][j++] != 'n')
			return ;
	}
	*newline = 0;
	while (arg[++(*i)])
	{
		j = 0;
		if (arg[*i][j] != '-')
			return ;
		j++;
		while (arg[*i][j])
		{
			if (arg[*i][j++] != 'n')
				return ;
		}
	}
}
