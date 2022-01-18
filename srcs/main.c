/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:01:13 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:51:00 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**========================================================================
 * @                              TODO
 *
 *	해상도 및 맵 크기 테스트
 *	구조체 이름
 *	평가지 체크
 *========================================================================**/
int main(int argc, char *argv[])
{
	t_param	P;
	t_config	C;

	if (argc != 2)
		err_exit("ERROR: CHECK t_paramETER", NULL);
	// -----------MAP parsing----------------
	ft_memset(&P, 0, sizeof(P));
	P.cfg = &C;

	parse_file(&P, argv[1]);
	check_worldMap(&P, &C);

	init(&P);

	mlx_hook(P.win, KeyPress, 0, keymap, &P);
	mlx_hook(P.win, DestroyNotify, 0, bye, &P);
	mlx_loop_hook(P.mlx, render, &P);
	mlx_loop(P.mlx);
}
