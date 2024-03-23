/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 07:55:07 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/22 15:54:17 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(t_base *base);

int	check_redirection(t_base *base, int *fd_in, int *fd_out)
{
	// check here_doc
	// read here_doc here
	// get here_doc count: if count > 1, 
	while (base->lst->file)
	{
		if (base->lst->file->type == INFILE)
		{
			ft_close(*fd_in, 0);
			*fd_in = open_infile(base);
		}
		else if (base->lst->file->type == HERE_DOC)
		{
			ft_close(*fd_in, 0);
			*fd_in = ft_heredoc(base);
		}
		else
		{
			ft_close(*fd_out, 0);
			*fd_out = open_outfile(base);
		}
		if (*fd_in == -1 || *fd_out == -1)
		{
			ft_close(*fd_in, *fd_out);
			return (EXIT_FAILURE);
		}
		base->lst->file = base->lst->file->next;
	}
	return (0);
}

static int	ft_heredoc(t_base *base)
{
	int		fd_heredoc;
	char 	*line;
	char	*tmp;

	fd_heredoc = open("here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
	{
		perror("heredoc");
		return (-1);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		tmp = ft_strtrim(line, "\n");
		if (!tmp)
		{
			print_error("minishell", "malloc failed");
			return (-1);
		}
		if (ft_strcmp(tmp, base->lst->file->filename) == 0) // line_len -1でstrncmpする?
			break ;
		ft_putstr_fd(line, fd_heredoc);
		free(line);
		free(tmp);
	}
	if (line)
		free(line);
	free(tmp);
	return (open_heredoc(base));
}

// 1st loop 
// --> here_doc_count
// --> last delimiter == valid
// stock here_doc in tmp file (here_doc)
// 2nd loop
// if here_doc_count != 1 --> return

/*
bash-3.2$ < inn << stop cat
> stp
> stop
bash: inn: No such file or directory

bash-3.2$ << stop cat
> hello stop
> stop
hello stop

bash-3.2$ << stopp << stop cat
> hello
> stopp
> stop
(cat writes nothing)

bash-3.2$ << stopp << stop cat > out2
> Hello
> stop
> stopp
> 
(delimiter doesn't work / out2 isn not created)
*/