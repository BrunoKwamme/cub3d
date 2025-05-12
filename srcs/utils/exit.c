/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:24:52 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/07 23:58:58 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_exit(t_instance *inst, int exit_code)
{
	if (!inst)
		exit(exit_code);
	if (inst->win && inst->mlx)
		mlx_destroy_window(inst->mlx, inst->win);
	if (inst->mlx)
	{
		mlx_destroy_display(inst->mlx);
		mlx_loop_end(inst->mlx);
		free(inst->mlx);
	}
	free_instance(inst);
	exit(exit_code);
}

int	quit_application(t_instance *inst)
{
	clean_exit(inst, 0);
	return (0);
}
