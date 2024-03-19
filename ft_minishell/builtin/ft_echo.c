/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:16:05 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/19 13:53:19 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_echo(t_base *base) 
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
		// if (list->append == false)
		// fd_out = open(list->write, , O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			fd_out = open(output_file, O_RDWR| O_CREAT | O_APPEND, 0644);
		// fd_out = open(list->write, O_RDWR| O_CREAT | O_APPEND, 0644);
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

int main(int argc, char **argv) 
{
	(void)argc;
    // ft_echo(argv, NULL, false);
	// ft_echo(argv, "test_output.txt", false);
	ft_echo(argv, "test_output.txt", true);
    return 0;
}

/*
Example:
echo hello world -----> STDOUT
echo hello world > test_output.txt -----> REDIRECTION
echo -n hello world > test_output.txt -----> REDIRECTION without newline
echo hello world >> test_output.txt -----> REDIRECTION + append
*/