#include "../minishell.h"

int	write_out_file(int i, t_line *tmp, char *str)
{
	int	j;

	i++;
	if (tmp->write)
		free(tmp->write);
	tmp->write = calloc(1, sizeof(ft_strlen(str)));
	if (str[i] == '>')
	{
		tmp->append = true;
		i++;
	}
	j = 0;
	if (str[i] == '<')
			return (-1);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '|')
	{
		tmp->write[j] = str[i];
		i++;
		j++;
	}
		tmp->write[j] = '\0';
	return(i);
}

int	write_in_file(int i, t_line *tmp, char *str)
{
	int	j;

	i++;
	if (tmp->write)
		free(tmp->write);
	tmp->write = calloc(1, sizeof(ft_strlen(str)));
	if (str[i] == '<')
	{
		tmp->append = true;
		i++;
	}
	j = 0;
	if (str[i] == '>')
			return (-1);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|')
	{
		tmp->write[j] = str[i];
		i++;
		j++;
	}
		tmp->write[j] = '\0';
	return(i);
}

int	write_char(int i, t_line *tmp, char *str)
{
	int	j;
	char	*arg_string;

	arg_string = calloc(ft_strlen(str) + 1, sizeof(char));
	j = 0;
	while (str[i] && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|')
	{
		arg_string[j] = str[i];
		i++;
		j++;
	}
	
	arg_string[j] = '\0';
	tmp->arg = ft_split (arg_string, ' ');
	return(i);
}

void	create_nod(t_line **line, char *str)
{
	t_line	*tmp;
	t_line	*nxt;
	int		i;
	(void)nxt;
	i = 0;
	nxt = *line;
	tmp = ft_calloc(1, sizeof(t_line));
	tmp->next = NULL;
	while (str[i])
	{
		if (str[i] == '>')
			i = write_out_file(i, tmp, str);
		else if (str[i] == '<')
			i = write_in_file(i, tmp, str);
		else if (str[i] == ' ')
			i++;
		else
			i = write_char(i, tmp, str);
	}
	if (line == NULL)
		*line = tmp;
	// else
	// {
	// 	while (nxt->next)
	// 		nxt = nxt->next;
	// 	tmp = nxt->next;
	//}
	
}

char	**ft_chara_split(char const *s)
{
	char		**srep;
	int			i;
	t_line		*line;

	i = 0;
	line = NULL;
	if (ft_strlen(s) == 0)
		return (ft_calloc(1, sizeof(char *)));
	srep = ft_split(s, '|');
	while (srep[i])
	{
		create_nod(&line, srep[i]);
		i++;
	}
	i = 0;
	while ((line->arg)[i])
	{
		printf("%s", line->arg[i]);
		i++;
	}
	return (srep);
}
