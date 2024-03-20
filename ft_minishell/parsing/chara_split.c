#include "../minishell.h"

int	write_out_file(int i, t_line *tmp, char *str)
{
	int	j;
	char *file;

	i++;
	file = calloc(1, sizeof(ft_strlen(str)));
	if (str[i] == '>')
	{
		tmp->append = true;
		i++;
	}
	j = 0;
	if (str[i] == '<' || str[i] == '>')
			return (-1);
	while(str[i] == ' ')
		i++;
	if (str[i] == '<' || str[i] == '>')
			return (-1);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '|' && str[i] != '>')
		file[j++] = str[i++];
	file[j] = '\0';
	j = 0;
	while (tmp->write[j])
		j++;
	tmp->write[j] = file;
	return(i);
}

int	write_in_file(int i, t_line *tmp, char *str)
{
	int		j;
	char	*file;

	i++;
	
	file = calloc(1, sizeof(ft_strlen(str)));
	if (str[i] == '<')
	{
		tmp->here_doc = true;
		i++;
	}
	j = 0;
	if (str[i] == '>' || str[i] == '<')
			return (-1);
	while(str[i] == ' ')
		i++;
	if (str[i] == '<' || str[i] == '>')
			return (-1);
	while (str[i] && str[i] != ' ' && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|')
		file[j++] = str[i++];
	file[j] = '\0';
	j = 0;
	while (tmp->read[j])
		j++;
	tmp->read[j] = file;
	return(i);
}

int	write_char(int i, t_line *tmp, char *str)
{
	int	j;
	char	*arg_string;
	int	last_arg;

	arg_string = calloc(ft_strlen(str) + 1, sizeof(char));
	j = 0;
	while (str[i] && str[i] != '<' \
	&& str[i] != '>' && str[i] != '|' && str[i] != ' ')
	{
		arg_string[j] = str[i];
		i++;
		j++;
	}
	arg_string[j] = '\0';
	last_arg = 0;
	while (tmp->arg[last_arg])
		last_arg++;
	tmp->arg[last_arg] = arg_string;
	return(i);
}

int	cnt_param(char *str, t_line *line)
{
	t_cnt 	*cnt;
	int		i;

	i = 0;
	cnt = calloc(1, sizeof(t_cnt));
	if (str[i] != '<' && str[i] != '>' && str[i] != ' ')
	{
		cnt->nb_arg++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == '<')
		{
			cnt->nb_in++;
			i++;
			if (str[i] == '<')
				i++;
			while (str[i] == ' ')
			 i++;
			if (str[i] == '>' || str[i] == '<')
				return (-1);
		}
		else if (str[i] == '>')
		{
			cnt->nb_out++;
			i++;
			if (str[i] == '>')
				i++;
			while (str[i] == ' ')
			 i++;
			if (str[i] == '<' || str[i] == '>')
				return (-1);
		}
		else if (str[i] != ' ' && str[i - 1] == ' ')
			cnt->nb_arg++;
		i++;
	}
 line->count = cnt;
 return (0);
}

void	malloc_string(t_line *line)
{
	printf("arg=%i, in=%i, out=%i\n", line->count->nb_arg, line->count->nb_in, line->count->nb_out);
	line->arg = calloc(line->count->nb_arg + 1, sizeof(char*));
	line->read = calloc(line->count->nb_in + 1, sizeof(char*));
	line->write = calloc(line->count->nb_out + 1, sizeof(char *));
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
	cnt_param(str, tmp);
	malloc_string(tmp);
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
	if (*line == NULL)
		*line = tmp;
	else
	{
		while (nxt->next)
			nxt = nxt->next;
		nxt->next = tmp;
	}
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
	while (line)
	{
		i = 0;
		while (line->arg && line->arg[i])
		{
			printf("arg[%i] is:%s\n", i, line->arg[i]);
			i++;
		}
		i = 0;
		while (line->read && line->read[i])
		{
			printf("infile[%i] is :%s\n", i, line->read[i]);
			i++;
		}
		i = 0;
		while (line->write && line->write[i])
		{
			printf("outfile[%i] is :%s\n", i, line->write[i]);
			i++;
		}
		line = line->next;
	}
	return (srep);
}
