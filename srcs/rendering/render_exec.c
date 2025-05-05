/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:52:53 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/05 03:58:09 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_frame_image_pixel(t_instance *inst, t_scene *scene, int x, int y)
{
	if (inst->screen_pixels[y][x] > 0)
		set_image_pixel(scene, x, y, inst->screen_pixels[y][x]);
	else if (y < inst->win_height / 2)
		set_image_pixel(scene, x, y, inst->texture.hex_ceiling);
	else if (y < inst->win_height -1)
		set_image_pixel(scene, x, y, inst->texture.hex_floor);
}

static void	render_frame(t_instance *inst)
{
	t_scene	scene;
	int		x;
	int		y;

	scene.img = NULL;
	set_new_img(inst, &scene, inst->win_width, inst->win_height);
	y = 0;
	while (y < inst->win_height)
	{
		x = 0;
		while (x < inst->win_width)
		{
			set_frame_image_pixel(inst, &scene, x, y);
			x++;
		}
		y++;
	}
	printf("ENDING RENDER FRAME\n");
	mlx_put_image_to_window(inst->mlx, inst->win, scene.img, 0, 0);
	mlx_destroy_image(inst->mlx, scene.img);
	printf("IMAGE ON WINDOW\n");
}


void	set_render_info(t_instance *instance)
{
	instance->mlx = mlx_init();
	instance->win = mlx_new_window(instance->mlx, instance->win_width, instance->win_height, "Cub3d");

	printf("INITIATED MLX\n");
	load_texture_buffer(instance);
}

void	render_raycast(t_instance *inst)
{
	set_screen_pixels(inst);
	init_raycast(&inst->ray);
	printf("RENDER RAYCAST\n");
	printf("WIDTH: %d | HEIGTH: %d\n", inst->win_width, inst->win_height);
	raycast_apply(&inst->player, inst);
	render_frame(inst);

}

void	render_images(t_instance *inst)
{
	render_raycast(inst);
}


