/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:01:13 by mishin            #+#    #+#             */
/*   Updated: 2022/01/14 17:08:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int argc, char *argv[])
{
  PARAM P;

// -----------MAP parsing----------------
	ft_memset(&P, 0, sizeof(P));

	if (argc != 2)
		err_exit("ERROR: CHECK PARAMETER", NULL);

	parse_file(&P, argv[1]);
	print_worldMap(&P);
  	//err_exit("test end", &P);

// -------------test line-------------


	P.pos.x = 10 * blockScale;
	P.pos.y = 11 * blockScale;
	P.dir.x = 0;
	P.dir.y = 1;
  printf("BLOCK SIZE=%d\n", blockScale);

	P.mlx = mlx_init();
	P.win = mlx_new_window(P.mlx, screenWidth, screenHeight, "Raycaster");
	init_mlx_image(&P);
	load_image(&P);
	make_block_image(&P);
	init_buffer(&P);
	init_texture(&P);
	render(&P);
	mlx_hook(P.win, KeyPress, 0, keymap, &P);
	mlx_loop_hook(P.mlx, render, &P);
	mlx_loop(P.mlx);
}
