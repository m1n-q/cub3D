#include "cub3D.h"

void	malloc_worldmap(t_param *P)
{
	int	i;

	P->worldmap = (int **)calloc_(P->cfg->mapheight, sizeof(int *));
	i = 0;
	while (i < P->cfg->mapheight)
		P->worldmap[i++] = (int *)calloc_(P->cfg->mapwidth, sizeof(int));
}

void	fill_worldmap(t_param *P)
{
	int		y;
	int		x;
	t_lst	*tmp;

	malloc_worldmap(P);
	y = -1;
	tmp = P->map;
	while (++y < P->cfg->mapheight)
	{
		x = -1;
		while (++x < P->cfg->mapwidth)
		{
			if (tmp->content[x] == '\0')
			{
				while (x < P->cfg->mapwidth)
					P->worldmap[y][x++] = ' ';
				break ;
			}
			if (ft_isdigit(tmp->content[x]))
				P->worldmap[y][x] = tmp->content[x] - 48;
			else
				P->worldmap[y][x] = tmp->content[x];
		}
		tmp = tmp->next;
	}
}

void	filename_check(char *filename, char *extension, t_param *P)
{
	int	f_len;
	int	e_len;

	f_len = ft_strlen(filename);
	e_len = ft_strlen(extension);
	if (f_len <= e_len)
		err_exit("Error: invalid filename", P);
	if (ft_strncmp(filename + f_len - e_len, extension, e_len) != 0)
		err_exit("Error: invalid extension", P);
}

void	cnt_mapheight(t_param *P)
{
	t_lst	*tail;
	int		cnt;

	cnt = 0;
	tail = lst_get_tail(P->map);
	while (tail)
	{
		if (ft_strlen(tail->content) == 0)
		{
			cnt++;
			tail = tail->prev;
		}
		else
			break ;
	}
	P->cfg->mapheight = lst_get_len(P->map) - cnt;
}

void	parse_file(t_param *P, char *filename)
{
	int		fd;
	char	*line;

	filename_check(filename, ".cub", P);
	fd = open(filename, O_RDONLY);
	if (fd < 3)
		err_exit("Error: open() failure", P);
	P->cfg->mapwidth = 0;
	while (get_next_line_(fd, &line) > 0)
	{
		parse_line(P, line);
		free(line);
		line = NULL;
	}
	parse_line(P, line);
	free(line);
	close(fd);
	cnt_mapheight(P);
	fill_worldmap(P);
}

// 55 확장자 .cub 보다 길어야한다 같거나 짧다면 리턴 0
// 57 str의 마지막 4글자, end 4글자를 비교 (같으면 1, 다른면 0 리턴)
// 66 파일이름에 확장자(.cub)가 포함됬는지 확인
// 71 마지막 라인이면 0을, 아니면 1을, 에러는 -1을 리턴한다
