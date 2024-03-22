/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:14:16 by dvo               #+#    #+#             */
/*   Updated: 2024/03/21 11:06:57 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *st1, char *st2)
{
	write(2, st1, ft_strlen(st1));
	if (st2)
	{
		write(2, ": ", 2);
		write(2, st2, ft_strlen(st2));
	}
	write(2, "\n", 1);
}

int	ft_free_all(char **ar, t_base *base, int ret)
{
	ft_free_split(ar);
	if (base)
	{
		if (base->ag1)
			free(base->ag1);
		free(base);
	}
	close((close(0), 1));
	return (ret);
}

void	attribute_folder(t_base *base, char *str)
{
	char	*ar[2];

	ar[0] = ft_strdup(str);
	ar[1] = NULL;
	execve(str, ar, base->env);
	if (ft_strchr(str, '/') == 1)
		print_error(strerror(errno), str);
	else
		print_error("command not found", ar[0]);
	free(ar[0]);
	exit(ft_free_all(NULL, base, 127));
}
