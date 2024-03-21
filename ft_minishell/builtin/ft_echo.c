/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:16:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/21 12:07:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_base *base) 
{
	int	i;
	int	newline;
	int	fd_out;

	// check_redirection(base, 0, &fd_out);
	if (base->lst->write[0] == NULL)
		fd_out = 1;
	else
	{
		i = 0;
		while (base->lst->write[i])
		{
			fd_out = open_output_file(base, i);
			i++;
			if (base->lst->write[i])
				ft_close(fd_out, 0);
		}
	}
	i = 1;
	newline = ft_strncmp(base->lst->arg[i], "-n", 2);
	if (newline == 0)
		i++;
	while (base->lst->arg[i])
	{
		write(fd_out, base->lst->arg[i], ft_strlen(base->lst->arg[i]));
		if (base->lst->arg[++i])
			write (fd_out, " ", 1);
	}
	if (newline)
		write (fd_out, "\n", 1);
	ft_close(fd_out, 0);
	// free
	exit(0);
}

// int main(int argc, char **argv) 
// {
// 	(void)argc;
//     ft_echo(argv, NULL, false);
// 	// ft_echo(argv, "test_output.txt", false);
// 	// ft_echo(argv, "test_output.txt", true);
//     return 0;
// }

/*
Example:
echo hello world -----> STDOUT
echo hello world > test_output.txt -----> REDIRECTION
echo -n hello world > test_output.txt -----> REDIRECTION without newline
echo hello world >> test_output.txt -----> REDIRECTION + append
*/

/*
int	ft_echo(char **arg, char *output_file, bool append) //// append --> Just for test
// arg --> list->arg
// output_file --> list->write
// append --> list->append
{
	int	i;
	int	newline;
	int	fd_out;

	i = 1;
	if (output_file == NULL)
		fd_out = 1;
	else
	{
		if (append == false)
			fd_out = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd_out = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0644);
		// if (fd_out < 0)
		// 	//--- error handling ---
	}
	i++; //// Just for test
	newline = ft_strncmp(arg[i], "-n", 2); // check if there is '-n'
	if (newline == 0)
		i++;
	while (arg[i])
	{
		write(fd_out, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write (fd_out, " ", 1);
		i++;
	}
	if (newline)
		write (fd_out, "\n", 1);
	if (fd_out != 1)
		close(fd_out);
	return (0);
}
*/