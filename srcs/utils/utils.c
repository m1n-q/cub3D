/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:54:41 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*strjoin2_(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*tmp;

	ret = strjoin_(s1, s2);
	tmp = ret;
	ret = strjoin_(ret, s3);
	free(tmp);
	return (ret);
}

char	**ft_split2(char *str, char *ch)
{
	char	*start;
	char	**ret;
	char	*ptr;

	if (!str || !ch)
		return (NULL);
	ptr = strdup_(str);
	start = ptr;
	while (*ptr)
	{
		if (ft_strchr(ch, *ptr))
			*ptr = ch[0];
		ptr++;
	}
	ret = ft_split(start, ch[0]);
	free(start);
	return (ret);
}

void	err_exit(char *msg, t_param *p)
{
	int	i;

	msg = strjoin2_(P_RED, msg, P_RESET);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	i = 0;
	if (p)
	{
		while (i < 4)
			free(p->tex_path[i++]);
		if (p->map)
			lst_clear(&p->map);
		if (p->worldmap)
		{
			i = 0;
			while (i < p->cfg->mapheight)
				free(p->worldmap[i++]);
			free(p->worldmap);
		}
	}
	exit(1);
}

char	*formatstr(char *fstr, char *arg, int tofree)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*ret;

	i = -1;
	while (fstr[++i])
	{
		if (fstr[i] == '{' && fstr[i + 1] == '}')
		{
			s1 = substr_(fstr, 0, i);
			s2 = substr_(fstr + i + 2, 0, ft_strlen(fstr + i + 2));
			ret = strjoin2_(s1, arg, s2);
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

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}
