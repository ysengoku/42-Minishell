/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:14:42 by dvo               #+#    #+#             */
/*   Updated: 2024/02/16 15:39:04 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_split(char **srep)
{
	int	i;

	i = 0;
	if (!srep)
		return ;
	while (srep[i])
		i++;
	i--;
	while (i >= 0)
	{
		free(srep[i]);
		srep[i] = NULL;
		i--;
	}
	free(srep);
	srep = NULL;
}

char	*search_on_split(char **exec, char *str)
{
	int		i;
	char	*to_find;

	i = 0;
	while (exec[i])
	{
		to_find = ft_strjoin(exec[i], str);
		if (access(to_find, X_OK) == 0)
			return (to_find);
		free(to_find);
		i++;
	}
	return (NULL);
}

char	*search_exec(char *envp, char *str, char *init)
{
	char	**exec;
	char	*to_find;
	char	*env;

	if (!init || (!str && init[0] != '\0'))
		return (NULL);
	env = ft_strtrim(envp, "PATH=");
	if (!env)
		return (NULL);
	if (access(str, X_OK) == 0)
	{
		to_find = ft_strdup(str);
		return (free (env), to_find);
	}
	exec = ft_split(env, ':');
	free(env);
	if (!exec)
		return (NULL);
	to_find = search_on_split(exec, str);
	ft_free_split(exec);
	if (to_find)
		return (to_find);
	return (NULL);
}
