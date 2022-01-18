/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:13:36 by mishin            #+#    #+#             */
/*   Updated: 2022/01/18 16:51:00 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	keymap(int keycode, t_param *P)
{
	if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		return (rotate(keycode, P));
	else if (keycode == KEY_W || keycode == KEY_A || \
			keycode == KEY_S || keycode == KEY_D)
		return (move(keycode, P));
	else if (keycode == KEY_ESC)
		return (quit(keycode, P));
	else
		return (0);
}

int	bye(t_param *P)
{
	printf("Bye!\n");
	mlx_destroy_window(P->mlx, P->win);
	exit(0);
	return (0);
}
