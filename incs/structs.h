/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:33:58 by mishin            #+#    #+#             */
/*   Updated: 2022/01/15 00:43:47 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct imgs
{
	void	*img;
	int		*addr;
	int		bpp;
	int		linesize;
	int		endian;
	int		width;
	int		height;
} IMG;

typedef struct linedraw
{
	int	length;
	int	x;
	int	start_y;
	int	end_y;
} LINEDRAW;

typedef struct vector
{
	double	x;
	double	y;
} VECTOR;

typedef struct	s_lst
{
	char			*content;
	struct s_lst	*next;
}				t_lst;

typedef struct config
{
	int	mapWidth;
	int mapHeight;
	int screenWidth;
	int screenHeight;
	int blockScale;			//	(screenWidth / mapWidth)	// screen Width를 기준으로 블럭의 가로를 정하고 있음. 블럭의 가로에 비례해서 높이를 그려줌.
	int NUM_RAYS;			//	screenWidth
	int SCALE;				// (screenWidth / NUM_RAYS)
	int collisionRange;		// (blockScale / 10)
	int	minimapScale;		// (blockScale / 10)

}	CONFIG;


typedef struct paramset
{
	void	*mlx;
	void	*win;
	int		**buf3D;	//NOTE: buffer	=> 직관적으로 생각할 수 있는 2차원 배열 형태
	int		**buf2D;
	int		**texture;	//NOTE: texture	=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)

// -------추가--------------------
	CONFIG	*cfg;
	t_lst	*map;
	int		width;
	int		height;

	char	*tex_path[4];
	int		type_set[7];
	int		floor_color[3];
	int		ceili_color[3];
	int		**worldMap;
// ------------------------------

	VECTOR	pos;
	VECTOR	dir;

	IMG		img3D;		//NOTE: IMG		=> mlx에서 사용되는 1차원 배열 형태 (width * y + x)
	IMG		img2D;

	IMG		wall1;
	IMG		wall2;
	IMG		wall3;
	IMG		wall4;
	IMG		wall5;

	IMG		wall_N;
	IMG		wall_S;
	IMG		wall_E;
	IMG		wall_W;


	IMG		grid;
	IMG		block;
	IMG		hblock;

} PARAM;

typedef struct dda
{
	VECTOR	raydir;
	VECTOR	hit;			// which box of the map we're in
	VECTOR	step;			// what direction to step in x or y-direction (either +1 or -1)

	double	dist_vert;		// length of ray from current position to next vert-side
	double	dist_horz;		// length of ray from current position to next horz-side
	double	delta_vert;		// length of ray from one vert-side to next vert-side
	double	delta_horz;		// length of ray from one vert-side to next horz-side

	double	perp_dist;
	VECTOR	perp_dir;

	int		side;			// was a NS or a EW wall hit?
} DDA;


#endif
