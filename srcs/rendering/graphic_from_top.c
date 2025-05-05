/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_from_top.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:58:25 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/04 19:54:20 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	my_mlx_close_window(int keycode, t_mlx_instance *mlx)
{
	printf("key pressed -> %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(mlx->instance, mlx->window);
		mlx_destroy_display(mlx->instance);
		free(mlx->instance);

		exit(1);
	}
	return (0);
}

void	convert_arr_in_map(t_map **map, t_mlx_instance *mlx, t_scene *scene)
{
	int	i_arr;
	int i;
	int x_mapping = 0;
	int y_mapping = 0;

	i_arr = 0;
	while ((*map)->map_layout[i_arr] != NULL)
	{
		x_mapping = 0;
		i = 0;
		while ((*map)->map_layout[i_arr][i] != LIMIT_INT_STD)
		{
			if((*map)->map_layout[i_arr][i] < 10 && (*map)->map_layout[i_arr][i] > -1)
			{
				if((*map)->map_layout[i_arr][i] == 1)
					mlx_put_image_to_window(mlx->instance, mlx->window, scene->img, x_mapping, y_mapping);
			}
			x_mapping = x_mapping + scene->img_width;
			i++;
		}
		y_mapping = y_mapping + scene->img_height;
		i_arr++;
	}
}

void texture_put(t_map **map, t_mlx_instance *mlx, t_scene *scene)
{
	int	i_arr;
	int i;
	int x_mapping = 0;
	int y_mapping = 0;

	i_arr = 0;
	while ((*map)->map_layout[i_arr] != NULL)
	{
		x_mapping = 0;
		i = 0;
		while ((*map)->map_layout[i_arr][i] != LIMIT_INT_STD)
		{
			if((*map)->map_layout[i_arr][i] < 10 && (*map)->map_layout[i_arr][i] > -1)
			{
				if((*map)->map_layout[i_arr][i] == 1)
					mlx_put_image_to_window(mlx->instance, mlx->window, scene->img, x_mapping, y_mapping);
			}
			x_mapping = x_mapping + scene->img_width;
			i++;
		}
		y_mapping = y_mapping + scene->img_height;
		i_arr++;
	}
}

t_scene	generate_image_info(t_mlx_instance *mlx, int img_width, int img_height, char *relative_path)
{
	t_scene	scene;

	printf("ENTERED ON GENERATE IMAGE INFO\n");
	scene.img_width= img_width;
	scene.img_height= img_height;
	scene.relative_path = relative_path;
	if (relative_path != NULL)
		scene.img = mlx_xpm_file_to_image(mlx->instance, scene.relative_path, &scene.img_width, &scene.img_height);
	else
		scene.img = mlx_new_image(mlx->instance, scene.img_width, scene.img_height);

	scene.ch_addr = mlx_get_data_addr(scene.img, &scene.bits_per_pixel, &scene.size_line, &scene.endian);
	scene.int_addr = (int *)scene.ch_addr;
	return scene;
}


void	generate_first_image(t_mlx_instance *mlx, t_map **map)
{
	t_scene	map_scene;
	t_scene	player;
	int		x;
	int		y;
	int color;

	y = 0;
	x = 0;
	color = 0xFF0000;

	map_scene = generate_image_info(mlx, WIN_WIDTH, WIN_HEIGHT, NULL);
	player = generate_image_info(mlx, (WIN_WIDTH/(*map)->horizontal_size)/2, (WIN_HEIGHT/(*map)->vertical_size)/2, NULL);
	convert_arr_in_map(map, mlx, &map_scene);
	while (y <= player.img_height)
	{
		x = 0;
		while (x <= player.img_width)
		{
			player.int_addr[(y * (player.size_line/4)) + x] = color;
			x++;
		}
		y++;
	}
	printf("person position x and y -> %d and %d\n", (*map)->person_pos[1], (*map)->person_pos[0]);
	printf("WITH OPERATIONS > x and y -> %d and %d\n", (*map)->person_pos[1] * 32, (*map)->person_pos[0] * 32);
	mlx_put_image_to_window(
		mlx->instance, mlx->window, player.img,
		(*map)->person_pos[1] * (player.img_width),
		(*map)->person_pos[0] * (player.img_height));
	mlx_hook(mlx->window, 2, 1L<<0, my_mlx_close_window, &map_scene);
}

void	my_mlx_create_main(t_map **map)
{
	t_mlx_instance	mlx;

	mlx.instance = mlx_init();
	mlx.window = mlx_new_window(mlx.instance, WIN_WIDTH, WIN_HEIGHT, "Hello, World!");

	generate_first_image(&mlx, map);
	mlx_loop(mlx.instance);
}
*/
