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

void	dealloc(t_param *p)
{
	int	i;

	if (p)
	{
		i = 0;
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
}

void	err_exit(char *msg, t_param *p)
{
	msg = strjoin2_(P_RED, msg, P_RESET);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	dealloc(p);
	system("leaks cub3D &> res; cat res | grep leaked > res1; cat res1; rm res res1");
	exit(1);
}

void	err_exit_(char *msg, t_param *p)
{
	char	*tmp;

	tmp = msg;
	msg = strjoin2_(P_RED, msg, P_RESET);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free(msg);
	free(tmp);
	dealloc(p);
	system("leaks cub3D &> res; cat res | grep leaked > res1; cat res1; rm res res1");
	exit(1);
}
