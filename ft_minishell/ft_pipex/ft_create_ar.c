/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:12:00 by dvo               #+#    #+#             */
/*   Updated: 2024/02/20 14:05:44 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	search_path_envp(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**create_ar(char *str, t_base *base)
{
	int		i;
	char	**ar;

	i = search_path_envp(base->env);
	if (i == -1)
		attribute_folder(base, str);
	ar = ft_split(str, ' ');
	if (!ar)
	{
		ft_write(strerror(errno), NULL);
		return (NULL);
	}
	base->ag1 = search_exec((base->env)[i], ar[0], str);
	if (!base->ag1)
	{
		ft_write("command not found", ar[0]);
		ft_free_split(ar);
		return (NULL);
	}
	return (ar);
}
