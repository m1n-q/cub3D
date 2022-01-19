/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:41 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:16:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_texture(t_param *p, int type, char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path = ft_strtrim(&line[i + 2], " \t");
	if (!path)
		err_exit("ft_strtrim() failure", p);
	i = -1;
	while (path[++i])
		if (path[i] == ' ' || path[i] == '\t')
			err_exit("space in path", p);
	if (i == 0)
		err_exit("no path", p);
	p->tex_path[type] = path;
	return ;
}

//  3 (여기 함수에 들어왔다면) type은 NO, SO, WE, EA 중 하나이다 (0 ~ 3)
//  9 공백일 때 인덱스 넘기기
// 11 line[i]부터 앞 2글자는 NO,SO,WE,EA 중 하나이기 때문에 i + 2를 한다
// 15,16 path 중간에 white space 문자가 있다면 error
// 18 path 문자열이 없다면 error
