/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:18:24 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/04 19:54:20 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_scene	generate_image_info(t_mlx_instance *mlx, int img_width, int img_height, char *relative_path)
{
	t_scene	scene;

	printf("ENTERED ON GENERATE IMAGE INFO\n");
	scene.img_width= img_width;
	scene.img_height= img_height;
	scene.relative_path = relative_path;
	if (relative_path != NULL)
	{
		scene.img = mlx_xpm_file_to_image(mlx->instance, scene.relative_path, &scene.img_width, &scene.img_height);
		scene.ch_addr = mlx_get_data_addr(scene.img, &scene.bits_per_pixel, &scene.size_line, &scene.endian);
		scene.int_addr = (int *)scene.ch_addr;
	}
	else
	{
		scene.img = mlx_new_image(mlx->instance, scene.img_width, scene.img_height);
		scene.ch_addr = mlx_get_data_addr(scene.img, &scene.bits_per_pixel, &scene.size_line, &scene.endian);
		scene.int_addr = (int *)scene.ch_addr;
	}
	printf("ENDED GENERATE IMAGE INFO\n");
	return scene;
}


int main()
{

	t_mlx_instance	mlx;
	t_scene	map_scene;

	mlx.instance = mlx_init();
	mlx.window = mlx_new_window(mlx.instance, WIN_WIDTH, WIN_HEIGHT, "Hello, World!");

	map_scene = generate_image_info(&mlx, 64, 64, "./assets/grass.xpm");
	mlx_new_image(mlx.instance, map_scene.img_width, map_scene.img_height);
	// mlx_xpm_file_to_image()
	// mlx_put_image_to_window(mlx.instance, mlx.window, map_scene.img, WIN_WIDTH/2, WIN_HEIGHT/2);
	mlx_loop(mlx.instance);

}
