/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:17:13 by dvo               #+#    #+#             */
/*   Updated: 2024/03/21 14:15:04 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../../lib/libft/libft.h"
# include "../../lib/ft_fprintf/ft_printf.h"

typedef struct s_base
{
	char	**env;
	char	**av;
	int		ac;
	int		fd_one;
	int		fd_two;
	char	*ag1;
	int		status;
	int		fd_return[2];
}				t_base;

char	*search_exec(char *envp, char *str, char *init);
char	**create_ar(char *str, t_base *base);
int		ft_free_all(char **ar, t_base *base, int ret);
void	ft_free_split(char **srep);
void	print_error(char *st1, char *st2);
void	child_loop(t_base *base, int fd[2], int i);
void	first_child(t_base *base);
void	last_child(t_base *base);
void	attribute_folder(t_base *base, char *str);
void	open_last_file(t_base *base);
void	open_first_file(t_base *base);
int		ft_pipex_child(char *str, t_base *base);

#endif