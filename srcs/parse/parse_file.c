#include "cub3D.h"

void	malloc_worldmap(t_param *p)
{
	int	i;

	p->worldmap = (int **)calloc_(p->cfg->mapheight, sizeof(int *));
	i = 0;
	while (i < p->cfg->mapheight)
		p->worldmap[i++] = (int *)calloc_(p->cfg->mapwidth, sizeof(int));
}

void	fill_worldmap(t_param *p)
{
	int		y;
	int		x;
	t_lst	*tmp;

	malloc_worldmap(p);
	y = -1;
	tmp = p->map;
	while (++y < p->cfg->mapheight)
	{
		x = -1;
		while (++x < p->cfg->mapwidth)
		{
			if (tmp->content[x] == '\0')
			{
				while (x < p->cfg->mapwidth)
					p->worldmap[y][x++] = ' ';
				break ;
			}
			if (ft_isdigit(tmp->content[x]))
				p->worldmap[y][x] = tmp->content[x] - 48;
			else
				p->worldmap[y][x] = tmp->content[x];
		}
		tmp = tmp->next;
	}
}

void	filename_check(char *filename, char *extension, t_param *p)
{
	int	f_len;
	int	e_len;

	f_len = ft_strlen(filename);
	e_len = ft_strlen(extension);
	if (f_len <= e_len)
		err_exit("Error: invalid filename", p);
	if (ft_strncmp(filename + f_len - e_len, extension, e_len) != 0)
		err_exit("Error: invalid extension", p);
}

void	cnt_mapheight(t_param *p)
{
	t_lst	*tail;
	int		cnt;

	cnt = 0;
	tail = lst_get_tail(p->map);
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
	p->cfg->mapheight = lst_get_len(p->map) - cnt;
}

void	parse_file(t_param *p, char *filename)
{
	int		fd;
	char	*line;

	filename_check(filename, ".cub", p);
	fd = open(filename, O_RDONLY);
	if (fd < 3)
		err_exit("Error: open() failure", p);
	p->cfg->mapwidth = 0;
	while (get_next_line_(fd, &line) > 0)
	{
		parse_line(p, line);
		free(line);
		line = NULL;
	}
	parse_line(p, line);
	free(line);
	close(fd);
	cnt_mapheight(p);
	fill_worldmap(p);
}

// 55 확장자 .cub 보다 길어야한다 같거나 짧다면 리턴 0
// 57 str의 마지막 4글자, end 4글자를 비교 (같으면 1, 다른면 0 리턴)
// 66 파일이름에 확장자(.cub)가 포함됬는지 확인
// 71 마지막 라인이면 0을, 아니면 1을, 에러는 -1을 리턴한다