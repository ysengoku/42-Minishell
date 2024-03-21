/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_ar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:12:00 by dvo               #+#    #+#             */
/*   Updated: 2024/03/21 11:06:57 by yusengok         ###   ########.fr       */
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
		print_error(strerror(errno), NULL);
		return (NULL);
	}
	base->ag1 = search_exec((base->env)[i], ar[0], str);
	if (!base->ag1)
	{
		print_error("command not found", ar[0]);
		ft_free_split(ar);
		return (NULL);
	}
	return (ar);
}
