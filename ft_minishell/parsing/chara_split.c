#include "../minishell.h"

static int	check_chara(char const *s, int i)
{
	int res;

	res = 0;
	if (s[i] != ';' || s[i] != '|' || s[i] != ' ')
		return (0);
	if (i != 0 && s[i] == ' ' && s[i - 1] == ' ')
		return (0);
	if (s[i] == ';' || s[i] == '|')
		res++;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i])
		res++;
	return (res);
}

static int	ft_countword( char const *s, int word)
{
	int	i;
	int	cmpt;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (0);
	cmpt = 1;
	while (s[i] && cmpt != word)
	{
		cmpt = check_chara(s, i);
		i++;
	}
	if (cmpt >= word)
	{
		cmpt = 0;
		while (s[i] != c && s[i] != 0)
		{
			i++;
			cmpt++;
		}
	}
	return (cmpt);
}

static void	ft_strwt(char const *s, int word, char *srep)
{
	int	i;
	int	cmpt;

	i = 0;
	while (s[i] && s[i] == c)
		i++;
	cmpt = 1;
	while (s[i] && cmpt != word)
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			cmpt++;
		i++;
	}
	if (cmpt == word)
	{
		cmpt = 0;
		while (s[i] != c && s[i] != 0)
		{
			srep[cmpt] = s[i];
			cmpt++;
			i++;
		}
		srep[cmpt] = 0;
	}
}

static void	ft_freebug(char **srep, int i)
{
	i--;
	while (i >= 0)
	{
		free(srep[i]);
		i--;
	}
	free(srep);
}

char	**ft_chara_split(char const *s)
{
	char		**srep;
	int			i;
	size_t		len;

	i = 0;
	if (ft_strlen(s) == 0)
		return (ft_calloc(1, sizeof(char *)));
	srep = ft_calloc((ft_countword(s, 0) + 1), sizeof(char *));
	if (srep == 0)
		return (0);
	while (i < (ft_countword(s, 0) + 1) - 1)
	{
		len = ft_countword(s, i + 1) + 1;
		srep[i] = malloc(sizeof(char) * len);
		if (srep[i] == 0)
		{
			ft_freebug(srep, i);
			return (0);
		}
		ft_strwt(s, i + 1, srep[i]);
		i++;
	}
	srep[i] = 0;
	return (srep);
}
