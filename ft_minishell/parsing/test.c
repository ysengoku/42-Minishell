/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvo <dvo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:34:48 by dvo               #+#    #+#             */
/*   Updated: 2024/03/20 23:45:15 by dvo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av, char **env)
{
	char *str;
	char	**line;
	t_base *base;

	base = ft_calloc(1, sizeof(t_base));
	base->env = env;
	(void) ac;
	(void) av;
	while(1)
	{
		str = readline("<<<");
		add_history(str);
		line = ft_chara_split(str);
		(void)line;
		//command_line(line, base);
		
	}
}
