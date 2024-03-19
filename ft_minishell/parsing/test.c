#include "../minishell.h"

// void command_line(char **line, t_base *base)
// {
// 	int	i;

// 	i = 0;
// 	while(line[i])
// 	{
// 		if(ft_strncmp(line[i], "<", 2) == 0)
// 			i = check_infile(line, i);
// 		else if(ft_strncmp(line[i], "|", 2) == 0)
// 			i = ft_pipex(line, i);
// 		else if(ft_strncmp(line[i], ">", 2) == 0)
// 			i = check_outfile(line, i);
// 		else if(ft_strncmp(line[i], ";", 2) == 0)
// 			i = ft_semicolon(line, i);
// 		else
// 			i = exec_command(line, i);
// 	}
// }

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
		str = readline(NULL);
		line = ft_chara_split(str);
		(void)line;
		//command_line(line, base);
		add_history(str);
	}
}
