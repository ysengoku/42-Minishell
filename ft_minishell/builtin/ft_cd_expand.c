/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:26:54 by yusengok          #+#    #+#             */
/*   Updated: 2024/05/02 23:25:12 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(t_base *base);
static char	*get_oldpwd_path(t_base *base);

char	*expand_path(t_base *base, char *arg)
{
	char	*path;

	path = NULL;
	if (arg == NULL || ft_strcmp(arg, "--") == 0)
		path = get_home_path(base);
	else if (ft_strncmp(arg, "-", 2) == 0)
		path = get_oldpwd_path(base);
	return (path);
}

static char	*get_home_path(t_base *base)
{
	t_env	*home;
	char	*path;

	home = find_env_var(base, HOME);
	if (home == NULL || home->value == NULL)
	{
		ft_fprintf(2, "minishell: cd: %s not set\n", HOME);
		return (NULL);
	}
	path = ft_strdup(home->value);
	if (!path)
	{
		perror("minishell");
		return (NULL);
	}
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
		{
			perror("minishell");
			return (NULL);
		}
		return (path);
	}
	path = ft_strdup(oldpwd->value);
	if (!path)
		perror("minishell");
	return (path);
}
