/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:47:08 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/07 22:49:27 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_pos_wall_collision(t_instance *inst, double x, double y)
{
	if (inst->map.map_layout[(int)y][(int)x] == '0')
		return (1);
	return (0);
}

static int	is_valid_pos_in_map(t_instance *inst, double x, double y)
{
	if (x < 0.25 || x >= inst->map.horizontal_size - 1.25)
		return (0);
	if (y < 0.25 || y >= inst->map.vertical_size - 0.25)
		return (0);
	return (1);
}

static int	is_valid_pos(t_instance *inst, double x, double y)
{
	if (is_valid_pos_in_map(inst, x, y))
		return (1);
	if (is_valid_pos_wall_collision(inst, x, y))
		return (1);
	return (0);
}

int	validate_move(t_instance *inst, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(inst, new_x, inst->player.pos_y))
	{
		inst->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(inst, inst->player.pos_x, new_y))
	{
		inst->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
