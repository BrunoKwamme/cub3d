/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 22:08:41 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/05 00:23:24 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	player_set_dir(t_player *player)
{
	if (player->dir == SOUTH)
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	else if (player->dir == NORTH)
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else if (player->dir == WEST)
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	else if (player->dir == EAST)
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else
		return ;
}

void	set_player_prop(t_instance *inst)
{
	int	pos_x;
	int	pos_y;

	pos_x = inst->map.person_pos[1];
	pos_y = inst->map.person_pos[0];
	inst->player.pos_x = inst->map.person_pos[1];
	inst->player.pos_y = inst->map.person_pos[0];
	inst->player.dir = inst->map.map_layout[pos_y][pos_x];
	player_set_dir(&inst->player);
	inst->map.map_layout[pos_y][pos_x] = 0;
}
