#include "cub3D.h"

int	is_dir(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	fill_worldMap(PARAM *P)
{
	int i;
	int j;
	int **world;
	t_lst	*tmp;

	world = (int **)malloc(sizeof(int *) * P->height);
	i = 0;
	while (i < P->height)
	{
		world[i++] = (int *)malloc(sizeof(int) * P->width);
	}
	i = 0;
	tmp = P->map;
	while (i < P->height)
	{
		j = 0;
		while (j < P->width)
		{
			if (tmp->content[j] == '\0')
			{
				while (j < P->width)
					world[i][j++] = 9;
				break ;
			}
			if (ft_isdigit(tmp->content[j]))
				world[i][j] = tmp->content[j] - 48;
			else
				world[i][j] = tmp->content[j];
			j++;
		}
		tmp = tmp->next;
		i++;
	}
	P->worldMap = world;
}
// e.g.
// filename == "map_file_name.cub"
// extension == ".cub"
// did_filename_include_extension
void	filename_check(char *filename, char *extension, PARAM *P)
{
	int	f_len; // filename length
	int	e_len; // extension length

	f_len = ft_strlen(filename);
	e_len = ft_strlen(extension); // 4글자

	// 확장자 .cub 보다 길어야한다 같거나 짧다면 리턴 0
	if (f_len <= e_len) 
		err_exit("Error: invalid filename", P);
	
	// str의 마지막 4글자, end 4글자를 비교 
	// 같으면 1, 다른면 0 리턴 
	if (ft_strncmp(filename + f_len - e_len, extension, e_len) != 0)
		err_exit("Error: invalid extension", P);	
}



void	parse_file(PARAM *P, char *filename)
{
	int			fd;
	char		*line;

	// 파일이름에 확장자(.cub)가 포함됬는지 확인
	filename_check(filename, ".cub", P);
		
	fd = open(filename, O_RDONLY);
	if (fd < 3)
		err_exit("Error: open() failure", P);

	while (get_next_line(fd, &line)) // 마지막 라인이면 0을, 아니면 1을, 에러는 -1을 리턴한다
	{
		parse_line(P, line);
		free(line);
		//line = NULL;
	}
	parse_line(P, line); // 마지막 라인
	free(line);

	close(fd);

	P->height = lst_get_len(P->map);
	
	printf("w:%d, h:%d\n", P->width, P->height);

	fill_worldMap(P);

	
}

