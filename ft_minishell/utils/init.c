/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:55:17 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/22 14:09:42 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_base	*init_base(char **env)
{
	t_base	*base;

	base = ft_calloc(1, sizeof(t_base));
	if (!base)
		perror("malloc");
	base->env = env;
	base->exit_code = 0;
	return (base);
}

void	check_shell_level(char **env)
{
	int		i;
	int		level;
	char	*shlevel;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			shlevel = env[i];
		i++;
	}
	level = ft_atoi(shlevel + 6) + 1;
	tmp = ft_itoa(level);
	ft_strcpy(shlevel + 6, tmp);
	free(tmp);
}
