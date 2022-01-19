/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:37 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:16:37 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_type(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!ft_strncmp(&line[i], "NO", 2) && ft_strchr(" \t", line[i + 2]))
		return (NO);
	else if (!ft_strncmp(&line[i], "SO", 2) && ft_strchr(" \t", line[i + 2]))
		return (SO);
	else if (!ft_strncmp(&line[i], "WE", 2) && ft_strchr(" \t", line[i + 2]))
		return (WE);
	else if (!ft_strncmp(&line[i], "EA", 2) && ft_strchr(" \t", line[i + 2]))
		return (EA);
	else if (!ft_strncmp(&line[i], "F", 1) && ft_strchr(" \t", line[i + 1]))
		return (FLOOR);
	else if (!ft_strncmp(&line[i], "C", 1) && ft_strchr(" \t", line[i + 1]))
		return (CEILI);
	return (UN_DEF);
}

void	set_max_width(t_param *p, char *line)
{
	int	width;

	width = ft_strlen(line);
	while (width > 0)
	{
		if (line[width - 1] == ' ' || line[width - 1] == '\t')
			width--;
		else
			break ;
	}
	if (width > p->cfg->mapwidth)
		p->cfg->mapwidth = width;
}

int	check_type_set(t_param *p)
{
	return (p->type_set[NO] && p->type_set[SO]
		&& p->type_set[WE] && p->type_set[EA]
		&& p->type_set[FLOOR] && p->type_set[CEILI]);
}

void	parse_line(t_param *p, char *line)
{
	int	type;

	if (!line)
		return ;
	type = get_type(line);
	if (is_empty_line(line) && !p->map)
		return ;
	if (type != UN_DEF && p->type_set[type])
		err_exit("double keys", p);
	if (check_type_set(p))
	{
		set_max_width(p, line);
		p->map = lst_add_back(p->map, line);
		if (!p->map)
			err_exit("failure", p);
		return ;
	}
	p->type_set[type] = 1;
	if (type >= NO && type <= EA)
		return (parse_texture(p, type, line));
	else if (type == FLOOR || type == CEILI)
		return (parse_rgb(p, type, line));
	err_exit("invalid key", p);
}

// 32 가장 긴 라인의 width값이 설정되도록
// 36 map파일의 한 줄을 읽어 파싱하는 곳 (리턴값 : 실패 0, 성공 1)
// 43 빈 라인이면 1리턴
// 45 type 중복 체크
// 47 모든 type의 값이 세팅되었고 undefine type인 경우
//    undefine type은 map정보다 그래서 str을 추가해준다
// 56 지도정보는 해당 라인 아래로는 지나가지 않음
// 57 type 체크 (중복방지)
// 59 type key가 NO SO WE EA 인 경우
// 61 type key가 F C 인 경우
// 62 모든 type값들이 아직 setting되지 않았는데 중간에 undefine(map정보)이 나온 경우
//    (빈줄,온리공백줄은 위에서 걸러진다)
