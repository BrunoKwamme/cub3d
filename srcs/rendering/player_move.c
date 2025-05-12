/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:39:56 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/07 22:44:08 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

static int	move_player_forward(t_instance *inst)
{
	double	new_x;
	double	new_y;

	new_x = inst->player.pos_x + inst->player.dir_x * MOVE_SPEED;
	new_y = inst->player.pos_y + inst->player.dir_y * MOVE_SPEED;
	return (validate_move(inst, new_x, new_y));
}

static int	move_player_backward(t_instance *inst)
{
	double	new_x;
	double	new_y;

	new_x = inst->player.pos_x - inst->player.dir_x * MOVE_SPEED;
	new_y = inst->player.pos_y - inst->player.dir_y * MOVE_SPEED;
	return (validate_move(inst, new_x, new_y));
}

static int	move_player_left(t_instance *inst)
{
	double	new_x;
	double	new_y;

	new_x = inst->player.pos_x + inst->player.dir_y * MOVE_SPEED;
	new_y = inst->player.pos_y - inst->player.dir_x * MOVE_SPEED;
	return (validate_move(inst, new_x, new_y));
}

static int	move_player_right(t_instance *inst)
{
	double	new_x;
	double	new_y;

	new_x = inst->player.pos_x - inst->player.dir_y * MOVE_SPEED;
	new_y = inst->player.pos_y + inst->player.dir_x * MOVE_SPEED;
	return (validate_move(inst, new_x, new_y));
}

int	move_player(t_instance *inst)
{
	int	moved;

	moved = 0;
	if (inst->player.move_y == 1)
		moved += move_player_forward(inst);
	if (inst->player.move_y == -1)
		moved += move_player_backward(inst);
	if (inst->player.move_x == -1)
		moved += move_player_left(inst);
	if (inst->player.move_x == 1)
		moved += move_player_right(inst);
	if (inst->player.rotate != 0)
		moved += rotate_player(inst, inst->player.rotate);
	return (moved);
}
