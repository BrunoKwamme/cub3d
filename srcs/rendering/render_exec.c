/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:52:53 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/04 20:21:44 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_render_info(t_instance *instance)
{
	instance->mlx = mlx_init();
	instance->win = mlx_new_window(instance->mlx, instance->win_width, instance->win_height, "Cub3d");

	load_texture_buffer(instance);
}
