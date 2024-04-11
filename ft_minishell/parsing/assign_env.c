/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:10:47 by dvo               #+#    #+#             */
/*   Updated: 2024/04/11 07:58:23 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**attribute_null_env(t_base *base)
{
	char	**env;
	char	*env3;
	char	buf[PATH_MAX];

	env = ft_calloc(5, sizeof(char *));
	if (getcwd(buf, sizeof(buf)) == 0)
		return (ft_perror("getcwd", 1), NULL);
	env[0] = ft_strjoin("PWD=", buf);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("OLDPWD");
	env3 = ft_strjoin("_=", buf);
	env[3] = ft_strjoin(env3, "/./minishell");
	free(env3);
	base->null_env = 1;
	return (env);
}

void	attribute_nod_env(t_base *base, t_env *tmp)
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

int	assign_env(t_base *base)
{
	int		i;
	t_env	*tmp;
	char	**split;

	i = 0;
	if (!base->env[i])
		base->env = attribute_null_env(base);
	while (base->env[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
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
		}
		i++;
		attribute_nod_env(base, tmp);
	}
	return (0);
}
