/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:16:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 11:04:34 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_newline(char **s, int *i, int *newline);

int	ft_echo(t_line *node, int fd[2])
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (node->arg[i])
		check_newline(node->arg, &i, &newline);
	while (node->arg[i])
	{
		write(fd[OUT], node->arg[i], ft_strlen(node->arg[i]));
		if (node->arg[++i])
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
	if (arg[*i][j] != '-' || (arg[*i][j] == '-' && !arg[*i][j + 1]))
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
