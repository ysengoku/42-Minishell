/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:55:17 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 18:53:20 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_base	*init_base(char **env)
{
	t_base	*base;

	base = ft_calloc(1, sizeof(t_base));
	if (!base)
	{
		perror("minishell");
		return (NULL);
	}
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
	shlevel = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			shlevel = env[i];
		i++;
	}
	if (shlevel)
	{
		level = ft_atoi(shlevel + 6) + 1;
		if (level >= 255)
			return ;
		tmp = ft_itoa(level);
		if (!tmp)
			return ;
		ft_strcpy(shlevel + 6, tmp);
		free(tmp);
	}
}
