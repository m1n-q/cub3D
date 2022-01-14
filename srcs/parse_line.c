#include "cub3D.h"

int	get_type(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEILI);
	return (UN_DEF);
}

void	set_max_width(PARAM *P, char *line)
{
	int len;
	int max;

	len = ft_strlen(line);
	max = len;
	while (line[--len] == ' ')
		max--;
	if (max > P->width)
		P->width = max;
}

// map파일의 한 줄을 읽어 파싱하는 곳
// 리턴값 : 실패 0, 성공 1 
void	parse_line(PARAM *P, char *line)
{
	int	type;

	if (!line)
		return ;
	type = get_type(line);
	
	if (ft_strlen(line) == 0) // 빈 라인이면 1리턴
		return ;


	// type 중복 체크
	if (type != UN_DEF && P->type_set[type])
		err_exit("Error: type id duplicated", P);

	// 모든 type의 값이 세팅되었고 undegine type인 경우
	// undefine type은 map정보다 그래서 str을 추가해준다
	if (P->type_set[NO] && P->type_set[SO]
		&& P->type_set[WE] && P->type_set[EA]
		&& P->type_set[FLOOR] && P->type_set[CEILI])
	{
		set_max_width(P, line);
		P->map = lst_add_back(P->map, line);
		if (!P->map)
			err_exit("Error: malloc failure", P);
		return ;
	}

//---------------라인이 지정된 키값으로 시작할 때(지도정보는 여길 지나가지 않음)---------------------
	P->type_set[type] = 1; // type 체크 (중복방지)
	
	// line의 시작이 NO, SO, WE, EA 중의 하나일 때 (0 ~ 4)
	if (type >= NO && type <= EA)
		return (parse_texture(P, type, line));
		// config.test_path[i]에 경로 문자열 세팅

	else if (type == FLOOR || type == CEILI)
		return (parse_rgb(P, type, line));
		// config.c[TEX_SKY || TEX_FLOOR]에 RGB값 세팅
	
	// 모든 type값들이 아직 setting되지 않았는데 중간에 undefine(map정보)이 나온 경우 (빈줄,온리공백줄은 위에서 걸러진다)
	return ;
}