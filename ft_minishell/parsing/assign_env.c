/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:10:47 by dvo               #+#    #+#             */
/*   Updated: 2024/04/23 13:27:23 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**attribute_null_env(t_base *base)
{
	char	**env;
	char	*env3;
	char	buf[PATH_MAX];

	env = ft_calloc(5, sizeof(char *));
	if (!env)
		return (NULL);
	if (getcwd(buf, sizeof(buf)) == 0)
		return (ft_perror("getcwd", 1), NULL);
	env[0] = ft_strjoin("PWD=", buf);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("OLDPWD");
	env3 = ft_strjoin("_=", buf);
	env[3] = ft_strjoin(env3, "/./minishell");
	free(env3);
	if (!env[0] || !env[1] || !env[2] || !env[3])
	{
		ft_free_strarr(env);
		return (NULL);
	}
	base->null_env = 1;
	return (env);
}

static void	attribute_nod_env(t_base *base, t_env *tmp)
{
	t_env	*last;

	last = base->envn;
	if (!base->envn)
		base->envn = tmp;
	else
	{
		while (last->next)
			last = last->next;
		last->next = tmp;
	}
}

int	assign_value_key_to_env(t_env *tmp, int i, t_base *base)
{
	char	**split;

	if (ft_strchr(base->env[i], '=') == NULL)
	{
		tmp->key = ft_strdup(base->env[i]);
		tmp->value = NULL;
	}
	else
	{
		split = ft_split(base->env[i], '=');
		tmp->key = ft_strdup(split[0]);
		tmp->value = assign_value(split);
		if (!tmp->value)
			return (-1);
	}
	return (0);
}

int	free_error_env(t_env *tmp, int i, t_base *base)
{
	if (tmp->value)
		free (tmp->value);
	free(base->env[i]);
	base->env[i] = NULL;
	return (-1);
}

int	assign_env(t_base *base)
{
	int		i;
	t_env	*tmp;

	i = 0;
	if (!base->env[i])
		base->env = attribute_null_env(base);
	if (!base->env)
		return (-1);
	while (base->env[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		if (!tmp)
			return (-1);
		if (assign_value_key_to_env(tmp, i, base) == -1)
			return (-1);
		if (!tmp->key)
			return (free_error_env(tmp, i, base));
		i++;
		attribute_nod_env(base, tmp);
	}
	set_pwdlog(base);
	return (0);
}
