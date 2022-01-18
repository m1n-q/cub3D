#include "cub3D.h"

void	parse_texture(PARAM *P, int type, char *line)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	path = ft_strtrim(&line[i + 2], " \t");
	if (!path)
		err_exit("Error: ft_strtrim() failure", P);
	i = -1;
	while (path[++i])
		if (path[i] == ' ' || path[i] == '\t')
			err_exit("Error: space in path", P);
	if (i == 0)
		err_exit("Error: no path", P);
	P->tex_path[type] = path;
	return ;
}

//  3 (여기 함수에 들어왔다면) type은 NO, SO, WE, EA 중 하나이다 (0 ~ 3)
//  9 공백일 때 인덱스 넘기기
// 11 line[i]부터 앞 2글자는 NO,SO,WE,EA 중 하나이기 때문에 i + 2를 한다
// 15,16 path 중간에 white space 문자가 있다면 error
// 18 path 문자열이 없다면 error
