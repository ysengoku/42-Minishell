/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:37:25 by dvo               #+#    #+#             */
/*   Updated: 2023/11/13 16:37:27 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t ele, size_t Size)
{
	char	*res;
	size_t	n;

	n = ele * Size;
	if (n && (n / ele != Size || n / Size != ele))
		return (0);
	res = malloc (ele * Size);
	if (res == 0)
		return (res);
	ft_bzero(res, ele * Size);
	return (res);
}
