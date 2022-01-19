/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:13:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 17:56:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	keymap(int keycode, t_param *p)
{
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		return (rotate(keycode, p));
	else if (keycode == KEY_W || keycode == KEY_A || \
			keycode == KEY_S || keycode == KEY_D)
		return (move(keycode, p));
	else if (keycode == KEY_ESC)
		return (quit(keycode, p));
	else
		return (0);
}

int	bye(t_param *p)
{
	printf("Bye!\n");
	mlx_destroy_window(p->mlx, p->win);
	system("leaks cub3D &> res; cat res | grep leaked > res1; cat res1; rm res res1");
	exit(0);
	return (0);
}
