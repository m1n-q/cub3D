/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:17:50 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 22:37:23 by mishin           ###   ########.fr       */
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
