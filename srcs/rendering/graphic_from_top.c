/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_from_top.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:58:25 by gabrfern          #+#    #+#             */
/*   Updated: 2025/04/30 01:59:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	my_mlx_close_window(int keycode, t_data *img)
{
	printf("key pressed -> %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_image(img->mlx, img->img);
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);

		exit(1);
	}
	return (0);
}

void convert_arr_in_map(t_map **map, t_data *img)
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
					mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, x_mapping, y_mapping);
				}
			x_mapping = x_mapping + 32;
			i++;
		}
		y_mapping = y_mapping + 32;
		i_arr++;
	}
}

void	old_start_mlx (t_map **map)
{
	t_data	img;

	img.x = 31;
	img.y = 31;
	img.relative_path = "./assets/grass.xpm";
	printf("relative path -> %s\n", img.relative_path);
	img.color = 0x00FF0000;
	img.mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(img.mlx, img.relative_path, &img.img_width, &img.img_height);
	//img.img = mlx_new_image(img.mlx, 640, 480);
	img.mlx_win = mlx_new_window(img.mlx, 1920, 1080, "Hello, World!");
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, img.x, img.y, img.color);
	convert_arr_in_map(map, &img);
	//mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 40, 0);
	mlx_hook(img.mlx_win, 2, 1L<<0, my_mlx_close_window, &img);
	mlx_loop(img.mlx);
}

void my_mlx_start(t_map **map, t_data *img)
{
// 	img->x = 31;
// 	img->y = 31;
	img->relative_path = "./assets/grass.xpm";
	printf("relative path -> %s\n", img->relative_path);
	img->color = 0x00FF0000;
	img->mlx = mlx_init();
	img->img = mlx_xpm_file_to_image(img->mlx, img->relative_path, &img->img_width, &img->img_height);
	img->mlx_win = mlx_new_window(img->mlx, 1920, 1080, "Hello, World!");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	convert_arr_in_map(map, img);
	void *second_img = mlx_new_image(img->mlx, 16, 16);
	int *buffer = (int *)mlx_get_data_addr(second_img, &img->bits_per_pixel, &img->line_length, &img->endian);
	int line_bytes = img->line_length / 4;
	int x = 0;
	int y = 0;
	int color = 0xFF0000;
	while (y <= 16)
	{
		x = 0;
		while (x <= 16)
		{
			buffer[(y * line_bytes) + x] = color;
			x++;
		}
		y++;
	}
	printf("person position x and y -> %d and %d\n", (*map)->person_pos[1], (*map)->person_pos[0]);
	printf("WITH OPERATIONS > x and y -> %d and %d\n", (*map)->person_pos[1] * 32, (*map)->person_pos[0] * 32);
	mlx_put_image_to_window(img->mlx, img->mlx_win, second_img, ((*map)->person_pos[1] * 32) + 8, ((*map)->person_pos[0] * 32) + 8);
	mlx_hook(img->mlx_win, 2, 1L<<0, my_mlx_close_window, img);

}

