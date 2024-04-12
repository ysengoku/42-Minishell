/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:55:17 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/12 16:55:44 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_base	*init_base(char **env)
{
	t_base	*base;

	base = ft_calloc(1, sizeof(t_base));
	if (!base)
		perror("malloc");
	base->env = env;
	base->exit_code = 0;
	return (base);
}
