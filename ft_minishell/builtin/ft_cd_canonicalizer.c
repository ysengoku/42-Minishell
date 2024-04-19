/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_canonicalizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:39:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/19 07:49:37 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_canonicalize(int *src, int *dest, char *curpath);

void	canonicalize_path(char *curpath, t_line *node)
{
	int	src;
	int	dest;

	(void) node;
	src = 0;
	dest = 0;
	while (curpath[src])
		ft_canonicalize(&src, &dest, curpath);
	curpath[dest] = '\0';
	if (!curpath[0])
		ft_strcpy(curpath, "/");
}

static void	ft_canonicalize(int *src, int *dest, char *curpath)
{
	if (curpath[*src] == '/' && curpath[*src + 1] == '.'
		&& (curpath[*src + 2] == '/' || curpath[*src + 2] == '\0'))
		*src += 2;
	else if (curpath[*src] == '/' && curpath[*src + 1] == '.'
		&& curpath[*src + 2] == '.'
		&& (curpath[*src + 3] == '/' || curpath[*src + 3] == '\0'))
	{
		if (*dest > 0)
		{
			while (curpath[--(*dest)] != '/' && *dest > 1)
				;
		}
		*src += 3;
	}
	else if (curpath[*src] == '/' && curpath[*src + 1] == '/')
		*src += 1;
	else
		curpath[(*dest)++] = curpath[(*src)++];
}
