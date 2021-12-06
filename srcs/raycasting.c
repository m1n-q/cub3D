#include "cub3D.h"

VECTOR	get_raydir(VECTOR dir, double angle)
{
	VECTOR	raydir;

	raydir.x = cos(angle) * dir.x  - sin(angle) * dir.y;
	raydir.y = sin(angle) * dir.x  + cos(angle) * dir.y;

	return (raydir);
}

VECTOR	get_stepdir(VECTOR pos, DDA D)
{
	VECTOR	step;

	if (D.raydir.x < 0)
		step.x = -1.0;
	else
		step.x = 1.0;


	if (D.raydir.y > 0)
		step.y = 1.0;
	else
		step.y = -1.0;

	return (step);
}

VECTOR	get_dist_vh(VECTOR pos, DDA D)
{
	double	dist_vert;
	double	dist_horz;

	if (D.raydir.x < 0)
		dist_vert = (pos.x - (int)pos.x) * D.delta_vert / BLOCK_SIZE;
	else
		dist_vert = ((int)pos.x + BLOCK_SIZE - pos.x) * D.delta_vert / BLOCK_SIZE;


	if (D.raydir.y > 0)
		dist_horz = ((int)pos.y + BLOCK_SIZE - pos.y) * D.delta_horz / BLOCK_SIZE;
	else
		dist_horz = (pos.y - (int)pos.y) * D.delta_horz / BLOCK_SIZE;

	return ((VECTOR){dist_vert, dist_horz});
}

void	get_perp_dist(PARAM *P, DDA *D)
{
	double	perp_dist;
	double	perp_delta;
	double	k;
	VECTOR	perp_dir;

	perp_dir.x = cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y;
	perp_dir.y = sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y;
	perp_delta = (perp_dir.y / perp_dir.x);
	k = P->pos.y - P->pos.x * perp_delta;		// constant for perpendicular linear
	D->perp_dist = fabs(perp_delta * D->hit.x - D->hit.y + k) / sqrt(pow(perp_delta, 2.0) + 1);

	// draw_perpdir(P, perp_dir);
}

LINEDRAW	get_draw_info(double perp_dist)
{
	LINEDRAW	draw;

	draw.length = (int)(screenHeight * sqrt(texHeight)) / perp_dist;
	draw.start_y = -draw.length / 2 + screenHeight / 2;
	if (draw.start_y < 0)
		draw.start_y = 0;
	draw.end_y = draw.length / 2 + screenHeight / 2;
	if (draw.end_y >= screenHeight)
		draw.end_y = screenHeight - 1;

	return (draw);
}

VECTOR	get_texture_pos(DDA D)
{
	double wall_hit;
	VECTOR texpos;

	if (D.side == 0)	wall_hit = D.hit.y / BLOCK_SIZE;
	else			wall_hit = D.hit.x / BLOCK_SIZE;

	// 1칸에서 어느만큼인지 * texWidth
	texpos.x = ((wall_hit - floor(wall_hit)) * (double)texWidth);
	// 좌우반전
	if (D.side == HORZ && D.raydir.y > 0)
		texpos.x = texWidth - texpos.x - 1;
	if (D.side == VERT && D.raydir.x < 0)
		texpos.x = texWidth - texpos.x - 1;
	texpos.y = 0.0;

	return (texpos);
}

void	fill_by_texture(PARAM *P, DDA D, VECTOR texpos, LINEDRAW draw)
{
	int		texnum;
	double	tex_stepY;

	//전체 그릴 높이 == draw.length
	//How much to increase the texture coordinate per screen pixel
	tex_stepY = (double)texHeight / (double)draw.length;	// drawStart 일때 tespos.y == 0, drawEnd 일때 tespos.y == 0 되도록

	texnum = worldMap[(int)(D.hit.y / BLOCK_SIZE)][(int)(D.hit.x / BLOCK_SIZE)] - 1;
	for (int y = draw.start_y; y < draw.end_y; y++)
	{
		texpos.y = fmin(texpos.y, texHeight - 1);
		int color = P->texture[texnum][(int)texpos.y * texHeight + (int)texpos.x];

		// make color darker for horizontal sides
		if (D.side == HORZ)
			color = (color >> 1) & 8355711;
		P->buf3D[y][draw.x] = color;
		texpos.y += tex_stepY;
	}
}

DDA	get_DDA_info(VECTOR pos, VECTOR dir, double r)
{
	DDA D;

	D.hit = pos;
	D.raydir = get_raydir(dir, r);
	D.delta_vert = sqrt(1 + pow(D.raydir.y, 2.0) / (pow(D.raydir.x + 0.0001, 2.0))) * BLOCK_SIZE;
	D.delta_horz = sqrt(1 + pow(D.raydir.x, 2.0) / (pow(D.raydir.y + 0.0001, 2.0))) * BLOCK_SIZE;

	// check step direction
	D.step = get_stepdir(pos, D);
	D.dist_vert = get_dist_vh(pos, D).x;
	D.dist_horz = get_dist_vh(pos, D).y;

	return (D);
}

void	run_DDA(DDA *D)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (D->dist_vert < D->dist_horz)
		{
			D->dist_vert += D->delta_vert;
			D->hit.x += D->step.x;
			D->side = VERT;
		}
		else
		{
			D->dist_horz += D->delta_horz;
			D->hit.y += D->step.y;
			D->side = HORZ;
		}

		// Check if ray has hit a wall
		if (worldMap[(int)(D->hit.y / BLOCK_SIZE)][(int)(D->hit.x / BLOCK_SIZE)] > 0)
			hit = 1;
	}
}

VECTOR	check_hit(PARAM *P)
{
	DDA			D;
	VECTOR		texpos;
	LINEDRAW	draw;
	double		angle = (PI / 6);
	double		dr = (angle * 2.0 / NUM_RAYS);

	for (double r = -angle; r <= angle; r+=dr)
	{
		D = get_DDA_info(P->pos, P->dir, r);
		run_DDA(&D);

		// draw hit block on 2Dmap
		draw_ray(P, D);
		draw_2Dsquare(P, (int)(D.hit.x / BLOCK_SIZE), (int)(D.hit.y / BLOCK_SIZE), P->hblock);

		get_perp_dist(P, &D);

		//   Calculate height of line to draw on screen
		draw = get_draw_info(D.perp_dist);
		draw.x = (((r + (PI / 6)) / dr) * SCALE);		// draw starting X (pixel)

		texpos = get_texture_pos(D);
		fill_by_texture(P, D, texpos, draw);

		// fill floor and ceiling
		verLine(draw.x, 0, draw.start_y, 0x000044, P);
		verLine(draw.x, draw.end_y, screenHeight - 1, 0x446600, P);
	}

	return (VECTOR){1.0, 1.0};
}
