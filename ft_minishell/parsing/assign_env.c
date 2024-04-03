/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:10:47 by dvo               #+#    #+#             */
/*   Updated: 2024/04/03 19:13:36 by dvo              ###   ########.fr       */
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

int	assign_env(t_base *base, char **env)
{
	int		i;
	t_env	*tmp;
	t_env	*last;
	char	**split;

	i = 0;
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_env));
		split = ft_split(env[i], '=');
		tmp->key = ft_strdup(split[0]);
		tmp->value = assign_value(split);
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
