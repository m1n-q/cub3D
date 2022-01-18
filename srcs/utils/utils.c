/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 13:56:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*ft_strjoin2(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*tmp;

	ret = ft_strjoin(s1, s2);
	tmp = ret;
	ret = ft_strjoin(ret, s3);
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
	ptr = ft_strdup(str);
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

void	err_exit(char *msg, PARAM *P)
{
	int	i;

	msg = ft_strjoin2(P_RED, msg, P_RESET);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	i = 0;
	if (P)
	{
		while (i < 4)
			free(P->tex_path[i++]);
		if (P->map)
			lst_clear(&P->map);
		if (P->worldMap)
		{
			i = 0;
			while (i < P->cfg->mapHeight)
				free(P->worldMap[i++]);
			free(P->worldMap);
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
			s1 = ft_substr(fstr, 0, i);
			s2 = ft_substr(fstr + i + 2, 0, ft_strlen(fstr + i + 2));
			ret = ft_strjoin2(s1, arg, s2);
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
