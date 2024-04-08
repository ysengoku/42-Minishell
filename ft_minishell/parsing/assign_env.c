/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:10:47 by dvo               #+#    #+#             */
/*   Updated: 2024/04/08 19:23:02 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add(char const *str1, char const *str2, size_t i, char *srep)
{
	while (str1[i])
	{
		srep[i] = (str1[i]);
		i++;
	}
	srep[i] = '=';
	i++;
	while (str2[i - ft_strlen(str1)])
	{
		srep[i] = (str2[i - ft_strlen(str1)]);
		i++;
	}
	srep[i] = '\0';
}

char	*ft_strjoin_char(char const *s1, char const *s2)
{
	char		*srep;
	size_t		i;

	i = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (i <= 1)
	{
		srep = ft_calloc(1, 1);
		return (srep);
	}
	srep = malloc(sizeof(char) * i);
	if (srep == 0)
		return (0);
	i = 0;
	add(s1, s2, i, srep);
	return (srep);
}

char	*assign_value(char **split)
{
	int		i;
	char	*join1;
	char	*join2;

	i = 2;
	join1 = ft_strdup(split[1]);
	while (split[i])
	{
		join2 = ft_strjoin_char(join1, split[i]);
		free(join1);
		join1 = join2;
		join2 = NULL;
		i++;
	}
	ft_free_strarr(split);
	return (join1);
}

char **attribute_null_env(t_base *base)
{
	char	**env;
	char	*env3;
	
	env = ft_calloc(5, sizeof(char *));
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == 0)
			return (ft_perror("getcwd", 1), NULL);
	env[0] = ft_strjoin("PWD=", buf);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("OLDPWD");
	env3 = ft_strjoin("_=", buf);
	env[3] = ft_strjoin(env3, "/./minishell");
	base->null_env = 1;
	return(env);
}

int	assign_env(t_base *base, char **env)
{
	int		i;
	t_env	*tmp;
	t_env	*last;
	char	**split;

	i = 0;
	if (!env[i])
		env = attribute_null_env(base);
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		if (ft_strchr(env[i], '=') == NULL)
		{
			tmp->key = ft_strdup(env[i]);
			tmp->value = NULL;
		}
		else
		{
			split = ft_split(env[i], '=');
			tmp->key = ft_strdup(split[0]);
			tmp->value = assign_value(split);
		}
		if (!base->envn)
			base->envn = tmp;
		else
		{
			last = base->envn;
			while (last->next)
				last = last->next;
			last->next = tmp;
		}
		i++;
	}
	last = base->envn;
	return (0);
}
