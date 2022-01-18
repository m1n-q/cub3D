/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:01:13 by mishin            #+#    #+#             */
/*   Updated: 2022/01/19 00:16:37 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/**========================================================================
 * @                              TODO
 *
 *	해상도 및 맵 크기 테스트
 *	평가지 체크
 *	img2D 지운 뒤 성능 보고, buf 삭제할지 결정
 *	get_next_line ㄱㅊ?
 *========================================================================**/
int	main(int argc, char *argv[])
{
	t_param		p;
	t_config	cfg;

	if (argc != 2)
		err_exit("ERROR: CHECK ARGUMENTS", NULL);
	ft_memset(&p, 0, sizeof(p));
	p.cfg = &cfg;
	parse_file(&p, argv[1]);
	check_worldmap(&p, &cfg);
	init(&p);
	mlx_hook(p.win, KeyPress, 0, keymap, &p);
	mlx_hook(p.win, DestroyNotify, 0, bye, &p);
	mlx_loop_hook(p.mlx, render, &p);
	mlx_loop(p.mlx);
}
