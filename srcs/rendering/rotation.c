/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:52:52 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/16 16:16:25 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	rotate_left_right(t_instance *inst, double rotspeed)
{
	t_player	*p;
	double		tmp_x;

	p = &inst->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}

int	rotate_player(t_instance *inst, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROT_SPEED * rotdir;
	moved += rotate_left_right(inst, rotspeed);
	return (moved);
}
