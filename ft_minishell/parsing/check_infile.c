#include "../minishell.h"

void	check_infile(char **line, int i)
{
	int	fd;
	char c;

	i++;
	fd = open(line[i], O_RDONLY);
	i++;
	c = check_end_arg(line, i);
	if (c == '|')
	{
		pipex_in(line, i);
	}
	else
		end_exec(line, i);
}