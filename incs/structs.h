/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:33:58 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 19:14:01 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//NOTE: t_img.data	=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)
//NOTE: buffer		=> 직관적으로 생각할 수 있는 2차원 배열 형태
typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		linesize;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_drawinfo
{
	int	length;
	int	x;
	int	start_y;
	int	end_y;
}	t_drawinfo;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

typedef struct s_config
{
	int	mapwidth;
	int	mapheight;
	int	blockscale;
	int	collision_range;
}	t_config;

typedef struct s_param
{
	void		*mlx;
	void		*win;
	int			**buf3d;
	int			textures[TEXNUM][TEXHEIGHT][TEXWIDTH];

	t_config	*cfg;
	t_lst		*map;
	char		*tex_path[4];
	int			type_set[7];
	int			floor_color;
	int			ceili_color;
	int			**worldmap;

	t_vector	pos;
	t_vector	dir;

	t_img		img3d;
	t_img		wall_n;
	t_img		wall_s;
	t_img		wall_e;
	t_img		wall_w;

	t_img		grid;
	t_img		block;
	t_img		hblock;

}	t_param;

typedef struct s_dda
{
	t_vector	step;
	t_vector	raydir;
	t_vector	perp_dir;
	t_vector	hit;
	double		dist_vert;
	double		dist_horz;
	double		delta_vert;
	double		delta_horz;
	double		perp_dist;
	int			side;
}	t_dda;
#endif

// 	hit			: which box of the map we're in
//	step		: what direction to step in x or y-direction (either +1 or -1)
//	dist_vert	: length of ray from current position to next vert-side
//	dist_horz	: length of ray from current position to next horz-side
//	delta_vert	: length of ray from one vert-side to next vert-side
//	delta_horz	: length of ray from one vert-side to next horz-side
//	side		: was a NS or a EW wall hit?
