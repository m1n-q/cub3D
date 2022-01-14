#include "cub3D.h"

void	set_color(PARAM *P, int type, char **rgb)
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
			err_exit("Error: invalid value of RGB", P);
		color = color | (tmp << (16 - (i * 8)));
		// tmp값은 0~255로 8비트(1byte)로 표현한다 
		// int 는 4byte의 공간이 있다
		// i값에 따라 
		// 첫번째 Red값은 16비트(2byte) 왼쪽으로 이동시킨 값으로 변환한다
			// (int변수의 왼쪽에서 부터 2번째 byte에 위치한다)
		// 두번째 Green값은 8비트(1byte) 왼족으로 이동시킨 값으로 변환한다
			// (int변수의 왼쪽에서 부터 3번째 byte에 위치한다)
		// 세번째 Blue값은 0비트, 즉 그대로 놔둔다
			// (int변수의 왼쪽에서 부터 4번째(마지막) byte에 위치한다)
		// or 연산을 통해 color의 왼쪽부터 Red비트,Green비트,Blue비트가 추가되며 자리잡는다
		if (type == FLOOR)
			P->floor_color[i] = color;
		else if (type == CEILI)
			P->ceili_color[i] = color;
		i++;
	}
}

void parse_rgb(PARAM *P, int type, char *line)
{
	int			i;

	i = 2;  // key가 "F " 또는 "C "이기 때문에 2부터 시작
	while (line[i])  
		if (!ft_strchr(" ,0123456789", line[i++]))
			err_exit("Error: invalid character in RGB", P);
			// line[i] 는 '공백'이거나, ','이거나 '숫자'이어야 한다 아니면 리턴 0
	

	char **rgb;
	char *tmp;
	int j;

	line = ft_strtrim(line + 2, " \t");
	if (!line)
		err_exit("Error: malloc failure", P);

	rgb = ft_split(line, ',');

	i = 0;
	while (rgb[i])
	{
		tmp = rgb[i];
		rgb[i] = ft_strtrim(rgb[i], " \t");
		if (!rgb[i])
			err_exit("Error: malloc failure", P);
		free(tmp);
		j = 0;
		while(rgb[i][j])
			if (ft_isdigit(rgb[i][j++]) == 0)
				err_exit("Error: invalid character in RGB", P);
		i++;
	}

	if (i != 3)
		err_exit("Error: invalid value of RGB", P);

	set_color(P, type, rgb);
	
	return ;
}