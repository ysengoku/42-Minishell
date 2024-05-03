/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:48:46 by dvo               #+#    #+#             */
/*   Updated: 2024/05/02 23:13:17 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add(char const *str1, char const *str2, size_t i, char *srep)
{
	int	j;

	j = 0;
	while (str1[i])
	{
		srep[i] = (str1[i]);
		i++;
	}
	srep[i] = '=';
	i++;
	while (str2[j])
	{
		srep[i] = (str2[j]);
		i++;
		j++;
	}
	srep[i] = '\0';
}

static char	*ft_strjoin_char(char const *s1, char const *s2)
{
	char		*srep;
	size_t		i;

	i = ft_strlen(s1) + ft_strlen(s2) + 2;
	srep = malloc(sizeof(char) * i);
	if (!srep)
	{
		perror("minishell");
		return (NULL);
	}
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
	if (!join1)
		return (NULL);
	while (split[i])
	{
		join2 = ft_strjoin_char(join1, split[i]);
		free(join1);
		if (!join2)
			return (NULL);
		join1 = join2;
		join2 = NULL;
		i++;
	}
	ft_free_strarr(split);
	return (join1);
}

void	set_pwdlog(t_base *base)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env_var(base, "PWD");
	if (pwd && pwd->value)
		ft_strcpy(base->pwd_log, pwd->value);
	oldpwd = find_env_var(base, OLDPWD);
	if (oldpwd && oldpwd->value)
		ft_strcpy(base->oldpwd_log, oldpwd->value);
}
