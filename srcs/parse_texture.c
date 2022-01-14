#include "cub3D.h"

// type은 NO, SO, WE, EA 중 하나이다 (0 ~ 3)
// line은 위의 type 문자열 + 공백하나 로 시작한다
void	parse_texture(PARAM *P, int type, char *line)
{
	int		start;
	int		end;
	char	*path;

	// 여기에 들어왔다는 것은 line 의 앞 2글자는 NO,SO,WE,EA 중 하나고 3번째는 공백이다
	start = 3; //4번재 글자부터 시작

	// 공백일 때 인덱스 넘기기 (아래의 조건문은 중복이다)
	while (line[start] == ' ')
		start++;
	
	end = ft_strlen(line);

	// end는 마지막 nul 문자의 인덱스다
	// start가 마지막 nul 인덱스라는 말은 예컨데 "NO " 다음 공백 말곤 아무 문자가 없다는 뜻이다
	if (end == start)
		err_exit("Error: no texture path", P);;

	// substr은 line의 start 인덱스 부터 (end - start)개 만큼 
	// 자체적으로 동적 할당한 메모리에 복사하여 리턴
	path = ft_substr(line, start, end - start);
	if (!path)
		err_exit("Error: malloc failure", P);

	P->tex_path[type] = path;
	// NO textures/wall_1.xpm 에서
	// NO 다음 "textures/wall_1.xpm" 와 같은 경로 문자열이
	// config->tex_pathp[]에 담긴다 

	return ;
}
