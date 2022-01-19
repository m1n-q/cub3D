#include "cub3D.h"

char	*cut_n_join(char *fstr, char *arg, int i)
{
	char	*s1;
	char	*s2;
	char	*ret;

	s1 = substr_(fstr, 0, i);
	s2 = substr_(fstr + i + 2, 0, ft_strlen(fstr + i + 2));
	ret = strjoin2_(s1, arg, s2);
	free(s1);
	free(s2);
	return (ret);
}

char	*formatstr(char *fstr, char *arg, int tofree)
{
	int		i;
	char	*ret;

	i = -1;
	ret = NULL;
	while (fstr[++i])
	{
		if (fstr[i] == '{' && fstr[i + 1] == '}')
		{
			ret = cut_n_join(fstr, arg, i);
			break ;
		}
	}
	if (tofree == 1)
		free(fstr);
	if (tofree == 2)
		free(arg);
	if (tofree == 3)
	{
		free(fstr);
		free(arg);
	}
	return (ret);
}
