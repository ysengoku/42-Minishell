/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:37:25 by dvo               #+#    #+#             */
/*   Updated: 2024/04/19 12:01:10 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t ele, size_t size)
{
	char	*res;
	size_t	n;

	n = ele * size;
	if (n && (n / ele != size || n / size != ele))
		return (0);
	res = malloc (ele * size);
	if (res == 0)
		return (res);
	ft_bzero(res, ele * size);
	return (res);
}
