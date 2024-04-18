/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:26:54 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/18 08:26:56 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_oldpwd_path(t_base *base);

char	*expand_path(t_base *base, char *arg)
{
	char	*path;

	path = NULL;
	if (arg == NULL || ft_strcmp(arg, "--") == 0)
	{
		if (!find_env_var(base, HOME) || !find_env_var(base, HOME)->value)
		{
			ft_fprintf(2, "minishell: cd: %s not set\n", HOME);
			return (NULL);
		}
		path = ft_strdup(getenv(HOME));
		if (!path)
			ft_perror("malloc", 1);
	}
	//else if (ft_strncmp(arg, "~", 2) == 0 || ft_strncmp(arg, "~/", 3) == 0)
	//{
	//	path = ft_strdup(getenv(HOME));
	//	if (!path)
	//		ft_perror("malloc", 1);
	//}
	else if (ft_strncmp(arg, "-", 2) == 0)
		path = get_oldpwd_path(base);
	return (path);
}

static char	*get_oldpwd_path(t_base *base)
{
	t_env	*oldpwd;
	char	*path;

	oldpwd = find_env_var(base, OLDPWD);
	if (!oldpwd || !oldpwd->value)
	{
		if (base->oldpwd_log[0] == 0)
		{
			ft_fprintf(2, "minishell: cd: %s not set\n", OLDPWD);
			return (NULL);
		}
		path = ft_strdup(base->oldpwd_log);
		if (!path)
			ft_perror("malloc", 1);
		return (path);
	}
	path = ft_strdup(oldpwd->value);
	if (!path)
		perror("malloc");
	return (path);
}
