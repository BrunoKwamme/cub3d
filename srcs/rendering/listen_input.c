/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listen_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:14:28 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/07 23:59:41 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	key_press_handler(int key, t_instance *inst)
{
	if (key == XK_Escape)
		quit_application(inst);
	if (key == XK_Left)
		inst->player.rotate -= 1;
	if (key == XK_Right)
		inst->player.rotate += 1;
	if (key == XK_w)
		inst->player.move_y = 1;
	if (key == XK_a)
		inst->player.move_x = -1;
	if (key == XK_s)
		inst->player.move_y = -1;
	if (key == XK_d)
		inst->player.move_x = 1;
	return (0);
}

static int	key_release_handler(int key, t_instance *inst)
{
	if (key == XK_Escape)
		quit_application(inst);
	if (key == XK_w && inst->player.move_y == 1)
		inst->player.move_y = 0;
	if (key == XK_s && inst->player.move_y == -1)
		inst->player.move_y = 0;
	if (key == XK_a && inst->player.move_x == -1)
		inst->player.move_x += 1;
	if (key == XK_d && inst->player.move_x == 1)
		inst->player.move_x -= 1;
	if (key == XK_Left && inst->player.rotate <= 1)
		inst->player.rotate = 0;
	if (key == XK_Right && inst->player.rotate >= -1)
		inst->player.rotate = 0;
	return (0);
}

void	listen_for_input(t_instance *inst)
{
	mlx_hook(inst->win, ClientMessage, NoEventMask, quit_application, inst);
	mlx_hook(inst->win, KeyPress, KeyPressMask, key_press_handler, inst);
	mlx_hook(inst->win, KeyRelease, KeyReleaseMask, key_release_handler, inst);
}
