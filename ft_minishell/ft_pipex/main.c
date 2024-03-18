/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:11:29 by dvo               #+#    #+#             */
/*   Updated: 2024/02/26 11:22:02 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex_parent(t_base *base)
{
	int		i;

	if (pipe(base->fd_return) == -1)
		ft_fprintf(2, "%s\n", strerror(errno));
	first_child(base);
	i = 3;
	while (i < base->ac - 2)
	{
		child_loop(base, base->fd_return, i);
		i++;
	}
	last_child(base);
}

int	main(int argc, char **argv, char **envp)
{
	t_base	*base;
	int		status;

	if (argc < 5)
	{
		ft_fprintf(2, "Wrong number of argument\n");
		return (1);
	}
	base = ft_calloc(1, sizeof(t_base));
	if (!base)
	{
		ft_fprintf(2, "%s\n", strerror(errno));
		return (1);
	}
	base->env = envp;
	base->ac = argc;
	base->av = argv;
	base->status = 0;
	ft_pipex_parent(base);
	status = base->status;
	free(base);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	return (0);
}
