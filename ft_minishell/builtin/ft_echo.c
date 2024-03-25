/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:16:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/25 12:37:06 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_newline(char *s);

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
	newline = check_newline(base->lst->arg[i]);
	if (newline == 0)
		i++;
	while (base->lst->arg[i])
	{
		write(fd[OUT], base->lst->arg[i], ft_strlen(base->lst->arg[i]));
		if (base->lst->arg[++i])
			write (fd[OUT], " ", 1);
	}
	if (newline)
		write (fd[OUT], "\n", 1);
	ft_close(fd[IN], fd[OUT]);
	return (0);
}

static int	check_newline(char *s)
{
	if (*s != '-')
		return (1);
	s++;
	while (*s)
	{
		if (*s != 'n')
			return (1);
		s++;
	}
	return (0);
}
