/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:45:42 by dvo               #+#    #+#             */
/*   Updated: 2023/11/11 18:45:49 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword( char const *s, char c, int word)
{
	int	i;
	int	cmpt;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	cmpt = 1;
	while (s[i] && cmpt != word)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			cmpt++;
		i++;
	}
	if (cmpt == word)
	{
		cmpt = 0;
		while (s[i] != c && s[i] != 0)
		{
			i++;
			cmpt++;
		}
	}
	return (cmpt);
}

static void	ft_strwt(char const *s, char c, int word, char *srep)
{
	int	i;
	int	cmpt;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	cmpt = 1;
	while (s[i] && cmpt != word)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			cmpt++;
		i++;
	}
	if (cmpt == word)
	{
		cmpt = 0;
		while (s[i] != c && s[i] != 0)
		{
			srep[cmpt] = s[i];
			cmpt++;
			i++;
		}
		srep[cmpt] = 0;
	}
}

static void	ft_freebug(char **srep, int i)
{
	i--;
	while (i >= 0)
	{
		free(srep[i]);
		i--;
	}
	free(srep);
}

char	**ft_split(char const *s, char c)
{
	char		**srep;
	int			i;
	size_t		len;

	i = 0;
	if (ft_strlen(s) == 0 && c == 0)
		return (ft_calloc(1, sizeof(char *)));
	srep = ft_calloc((ft_countword(s, c, 0) + 1), sizeof(char *));
	if (srep == 0)
		return (0);
	while (i < (ft_countword(s, c, 0) + 1) - 1)
	{
		len = ft_countword(s, c, i + 1) + 1;
		srep[i] = malloc(sizeof(char) * len);
		if (srep[i] == 0)
		{
			ft_freebug(srep, i);
			return (0);
		}
		ft_strwt(s, c, i + 1, srep[i]);
		i++;
	}
	srep[i] = 0;
	return (srep);
}
