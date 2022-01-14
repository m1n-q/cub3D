#include "cub3D.h"
#define PRINT	printf("raydir : %f, %f\n", raydir.x, raydir.y); \
				printf("pos = (%f, %f)\n", P->pos.x, P->pos.y); \
				printf("hit = (%f, %f)\n", hit.x, hit.y); \
				printf("perp delta = %f\n", perp_delta); \
				printf("perp dist = %f\n", perpendicular_dist); \
				printf("y = (%f / %f) * x + %f\n", perpendicular.x, perpendicular.y, k); \
				printf("============================================\n\n");



VECTOR	raycasting(PARAM *P)
{
	VECTOR	raydir;
	VECTOR	hit;			// which box of the map we're in
	VECTOR	step;			// what direction to step in x or y-direction (either +1 or -1)
	double	dist_vert;		// length of ray from current position to next x or y-side
	double	dist_horz;
	double	delta_vert;		// length of ray from one x or y-side to next x or y-side
	double	delta_horz;
	double	perpendicular_dist;

	int		side;			// was a NS or a EW wall hit?
	VECTOR	perp_dir;


	double	angle = (PI / 6);
	double	dr = (angle * 2.0 / P->cfg->NUM_RAYS);
	// printf("dr = %f\n", dr);

	for (double r = -angle; r <= angle; r+=dr)
	{
		raydir.x = cos(r) * P->dir.x  - sin(r) * P->dir.y;
		raydir.y = sin(r) * P->dir.x  + cos(r) * P->dir.y;
		hit.x = P->pos.x;
		hit.y = P->pos.y;
		delta_vert = sqrt(1 + pow(raydir.y, 2.0) / (pow(raydir.x + 0.0001, 2.0))) * P->cfg->blockScale;
		delta_horz = sqrt(1 + pow(raydir.x, 2.0) / (pow(raydir.y + 0.0001, 2.0))) * P->cfg->blockScale;

		// check step direction
		if (raydir.x < 0)
		{
			step.x = -1.0;
			dist_vert = (P->pos.x - (int)P->pos.x) * delta_vert / P->cfg->blockScale;
		}
		else
		{
			step.x = 1.0;
			dist_vert = ((int)P->pos.x + P->cfg->blockScale - P->pos.x) * delta_vert / P->cfg->blockScale;
		}
		if (raydir.y > 0)
		{
			step.y = 1.0;
			dist_horz = ((int)P->pos.y + P->cfg->blockScale - P->pos.y) * delta_horz / P->cfg->blockScale;

		}
		else
		{
			step.y = -1.0;
			dist_horz = (P->pos.y - (int)P->pos.y) * delta_horz / P->cfg->blockScale;
		}


		// perform DDA
		int hitt = 0;
		while (hitt == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (dist_vert < dist_horz)
			{
				dist_vert += delta_vert;
				hit.x += step.x;
				side = VERT;
			}
			else
			{
				dist_horz += delta_horz;
				hit.y += step.y;
				side = HORZ;
			}

			// Check if ray has hit a wall
			if (worldMap[(int)(hit.y / P->cfg->blockScale)][(int)(hit.x / P->cfg->blockScale)] > 0)
				hitt = 1;
		}

		// draw hit block on 2Dmap
		draw_2Dsquare(P, (int)(hit.x / P->cfg->blockScale), (int)(hit.y / P->cfg->blockScale), P->hblock);


		if (side == VERT)perpendicular_dist = dist_vert - delta_vert;
		else          perpendicular_dist = dist_horz - delta_horz;


		perp_dir.x = cos(PI / 2) * P->dir.x - sin(PI / 2) * P->dir.y;
		perp_dir.y = sin(PI / 2) * P->dir.x + cos(PI / 2) * P->dir.y;
		double perp_delta = (perp_dir.y / perp_dir.x);
		double k = P->pos.y - P->pos.x * perp_delta;		// constant for perpendicular linear
		perpendicular_dist = fabs(perp_delta * hit.x - hit.y + k) / sqrt(pow(perp_delta, 2.0) + 1);
		// PRINT


		//   Calculate height of line to draw on screen
		int lineHeight = (int)(P->cfg->screenHeight * sqrt(P->cfg->texHeight)) / perpendicular_dist;
		int drawStart = -lineHeight / 2 + P->cfg->screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + P->cfg->screenHeight / 2;
		if (drawEnd >= P->cfg->screenHeight)
			drawEnd = P->cfg->screenHeight - 1;



		draw_perpdir(P, perp_dir);

		int	pixel_x;
		pixel_x = (((r + (PI / 6)) / dr) * P->cfg->SCALE);

		//   choose wall color
		// int color;
		// switch (worldMap[(int)hit.y / P->cfg->blockScale][(int)hit.x / P->cfg->blockScale])
		// {
		// 	case 1:color = RGB_Red;		break; // red
		// 	case 2:color = RGB_Green;	break; // green
		// 	case 3:color = RGB_Blue;	break; // blue
		// 	case 4:color = RGB_White;	break; // white
		// 	default:color = RGB_Yellow;	break; // yellow
		// }
		// if (side == HORZ)
		// 	color = color / 2;
		// verLine(pixel_x, drawStart, drawEnd, color, P);





		draw_ray(P, hit, raydir, side);

		int texNum = worldMap[(int)(hit.y / P->cfg->blockScale)][(int)(hit.x / P->cfg->blockScale)] - 1;
		double wall_hit;
		if (side == 0)	wall_hit = hit.y / P->cfg->blockScale;
		else			wall_hit = hit.x / P->cfg->blockScale;
		// wall_hit -= floor(wall_hit);


		// 1칸에서 어느만큼인지 * P->cfg->texWidth
		int texX = (int)((wall_hit - floor(wall_hit)) * (double)P->cfg->texWidth);
		// 좌우반전
		if (side == HORZ && raydir.y > 0)
			texX = P->cfg->texWidth - texX - 1;
		if (side == VERT && raydir.x < 0)
			texX = P->cfg->texWidth - texX - 1;
		// printf("hit %s side, wallhit: %f tex.X : %d\n", side ? "horz" : "vert", wall_hit, texX);

		// How much to increase the texture coordinate perscreen pixel

		//전체 그릴 높이 : LineHeight
		double texstep =  (double)P->cfg->texHeight / (double)lineHeight;

		//tesPos => drawStart 일때 0, drawEnd 일때 P->cfg->texHeight 되도록
		double texPos = 0.0;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (P->cfg->texHeight - 1) in case of overflow
			int texY = (int)texPos & (P->cfg->texHeight - 1);
			texPos += texstep;
			int color = P->texture[texNum][texY * P->cfg->texHeight + texX];
			// P->buf2D[row][col] = P->texture[0][row * P->cfg->texWidth + col];


			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			P->buf3D[y][pixel_x] = color;
		}

		// fill floor and ceiling
		verLine(pixel_x, 0, drawStart, 0x000044, P);
		verLine(pixel_x, drawEnd, P->cfg->screenHeight - 1, 0x446600, P);
	}

	return (VECTOR){1.0, 1.0};
}
