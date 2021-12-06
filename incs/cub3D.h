#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "mlx.h"
#include "libft.h"
#include "keys.h"
#include <X11/X.h>

#define mapWidth 25
#define mapHeight 25
#define screenWidth 500
#define screenHeight 500

#define texWidth 256
#define texHeight 256

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

typedef struct paramset
{
	void	*mlx;
	void	*win;
	int		**buf3D;
	int		**buf2D;
	int		**texture;

	VECTOR	pos;
	VECTOR	dir;

	IMG		img3D;
	IMG		img2D;

	IMG		wall1;
	IMG		wall2;
	IMG		wall3;
	IMG		wall4;

	IMG		grid;
	IMG		block;
	IMG		hblock;

} PARAM;

typedef struct dda
{
	VECTOR	raydir;
	VECTOR	hit;			// which box of the map we're in
	VECTOR	step;			// what direction to step in x or y-direction (either +1 or -1)

	double	dist_vert;		// length of ray from current position to next x or y-side
	double	dist_horz;
	double	delta_vert;		// length of ray from one x or y-side to next x or y-side
	double	delta_horz;

	double	perp_dist;
	VECTOR	perp_dir;

	int		side;			// was a NS or a EW wall hit?
} DDA;

#define RGB_Red 0xff0000
#define RGB_Green 0x00ff00
#define RGB_Blue 0x0000ff
#define RGB_White 0xffffff
#define RGB_Black 0x000000
#define RGB_Grey 0x555555
#define RGB_Yellow 0xfbff00

#define BLOCK_SIZE (screenWidth / mapWidth)
#define NUM_RAYS screenWidth
#define SCALE (screenWidth / NUM_RAYS)

#define PI	3.141592

#define BORDER	0
#define N		1
#define S		2
#define E		3
#define W		4

#define VERT	0
#define HORZ	1

extern int worldMap[mapWidth][mapHeight];
extern int All_Textures[];

void	verLine(int x, int drawStart, int drawEnd, int color, PARAM *P);
void	verLine2(int x, int drawStart, int drawEnd, int color, PARAM *P);

int		move(int keycode, PARAM *param);
int		movecur(int x, int y, PARAM *param);
VECTOR	check_hit(PARAM *P);
int		render(PARAM *param);

int		draw_dir(PARAM *param);
int		draw_perpdir(PARAM *P, VECTOR perp_dir);
void	draw_ray(PARAM *P, DDA D);
int		draw_2Dsquare(PARAM *P, int x, int y, IMG img);
int		draw_2Dmap(PARAM *param);
int		draw_2Dplayer(PARAM *param);
void	draw(int w, int h, PARAM *param);

/* screen buffer */
int		init_buffer(PARAM *P);
void	buffer_to_img(PARAM *P, int **buffer, IMG img, int w, int h);
void	clear_buffer(PARAM *P, int **buffer);
void	clear_img(PARAM *P, IMG img);

/* image (load) */
int		load_image(PARAM *P);

/* texture */
int		init_texture(PARAM *P);
int		image_to_texture(int *texture, IMG teximg);
#endif
