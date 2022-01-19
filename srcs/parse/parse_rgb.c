/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:16:39 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 18:16:39 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_color(t_param *p, int type, char **rgb)
{
	int	i;
	int	color;
	int	tmp;

	i = 0;
	color = 0;
	while (i < 3)
	{
		tmp = ft_atoi(rgb[i]);
		if (tmp < 0 || tmp > 255)
			err_exit("invalid value of RGB", p);
		color = color | (tmp << (16 - (i * 8)));
		i++;
	}
	if (type == FLOOR)
		p->floor_color = color;
	else if (type == CEILI)
		p->ceili_color = color;
}

void	parse_rgb(t_param *p, int type, char *line)
{
	int		i;
	char	*rgb_str;
	char	**rgb_val;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	rgb_str = ft_strtrim(&line[i + 1], " \t");
	if (!rgb_str)
		err_exit("ft_strtrim() failure", p);
	i = 0;
	while (rgb_str[i])
		if (!ft_strchr(" \t,0123456789", rgb_str[i++]))
			err_exit("invalid character in RGB", p);
	rgb_val = ft_split2(rgb_str, " ,\t");
	if (!rgb_val)
		err_exit("ft_split2 failure", p);
	i = 0;
	while (rgb_val[i])
		i++;
	if (i != 3)
		err_exit("there are more than 3 RGB val ", p);
	set_color(p, type, rgb_val);
	return ;
}

/*  <line 16>
	tmp값은 0~255로 8비트(1byte)로 표현한다
	int 는 4byte의 공간이 있다
	i값에 따라
	첫번째 Red값은 16비트(2byte) 왼쪽으로 이동시킨 값으로 변환한다
	(int변수의 왼쪽에서 부터 2번째 byte에 위치한다)
	두번째 Green값은 8비트(1byte) 왼족으로 이동시킨 값으로 변환한다
	(int변수의 왼쪽에서 부터 3번째 byte에 위치한다)
	세번째 Blue값은 0비트, 즉 그대로 놔둔다
	(int변수의 왼쪽에서 부터 4번째(마지막) byte에 위치한다)
	or 연산을 통해 color의 왼쪽부터 Red비트,Green비트,Blue비트가 추가되며 자리잡는다
*/

// 25 여기함수에 들어왔다는 것은 line은 (white space제외)F 또는 C로 시작한다
// 34 여기서부터 line[i]은 F 또는 C 중 하나다
// 39 line은 (공백)(컴마)(숫자)의 문자로만 구성되어야 한다 아니면 리턴 0
// 41 (공백)(컴마)(탭) 을 기준으로 split을 한다
//     여기서 (공백)(컴마)(탭)문자들은 빠지고 오직 숫자로면 구성된 2차원 문자열이 생성된다
// 45 ~ 48 split된 갯수가 3개(RGB) 인지 체크
// 49 각 RGB값을 세팅한다
