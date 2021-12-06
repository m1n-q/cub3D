#include "cub3D.h"

void verLine(int x, int drawStart, int drawEnd, int color, PARAM *P)
{
	for (int x2 = x; x2 < x + SCALE; x2++)
	{
		for (int y = drawStart; y <= drawEnd; y++)
		{
			P->buf3D[y][x2] = color;
		}
	}
}

void verLine2(int x, int drawStart, int drawEnd, int color, PARAM *P)
{
	for (int y = drawStart; y <= drawEnd; y++)
		// P->buf3D[y][x2] = color
		;
}
