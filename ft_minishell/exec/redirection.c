#include "minishell.h"

void	check_redirection(t_base *base, int *fd_in, int *fd_out)
{
	int	i;

	i = 0;
	if (base->lst->read[0] != NULL)
	{
		while (base->lst->read[i])
		{
			*fd_in = open_input_file(base, i);
			//if (*fd_in == -1)
			// error handling
			i++;
			if (base->lst->read[i])
				ft_close(*fd_in, 0);
		}
	}
	i = 0;
	if (base->lst->write[0] != NULL)
	{
		while (base->lst->write[i])
		{
			*fd_out = open_output_file(base, i);
			//if (*fd_out == -1)
			// error handling
			i++;
			if (base->lst->write[i])
				ft_close(*fd_out, 0);
		}
	}
}