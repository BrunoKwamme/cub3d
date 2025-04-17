/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:47:11 by bkwamme           #+#    #+#             */
/*   Updated: 2025/04/17 20:53:27 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close_window(int keycode, t_data *img)
{
	printf("key pressed -> %d\n", keycode);
	if (keycode == 65307)
		mlx_destroy_window(img->mlx, img->mlx_win);
	return (0);
}

void convert_arr_in_map(t_map **map, t_data *img)
{
	int	i_arr;
	int i;
	int j = 0;
	int k = 0;

	i_arr = 0;
	while ((*map)->map_layout[i_arr] != NULL)
	{
		j = 0;
		i = 0;
		while ((*map)->map_layout[i_arr][i] != LIMIT_INT_STD)
		{
			if((*map)->map_layout[i_arr][i] < 10 && (*map)->map_layout[i_arr][i] > -1)
			{
				if((*map)->map_layout[i_arr][i] == 1)
					mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, j,k);
				j = j + 32;
			}
			i++;
		}
		k = k + 32;
		i_arr++;
	}
}

void start_mlx (t_map **map)
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
	mlx_hook(img.mlx_win, 2, 1L<<0, close_window, &img);
	mlx_loop(img.mlx);
}


int	main(int argc, char **argv)
{
	t_map	*map;
	//t_data img;

	//img.mlx = mlx_init();
	//img.img = mlx_new_image(img.mlx, 1920, 1080);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (argc != 2 || argument_val(argv) != 0)
		return (put_error("BAD INPUT"), 2);
	map = read_document(argv[1]);
	start_mlx(&map);
	if (map != NULL)
	{
		printf("north -> %s\nsouth ->%s\nweast -> %s\neast -> %s\n", map->no_texture, map->so_texture, map->we_texture, map->ea_texture);
		printf("printing ceiling:\n");
		printing_nbr_arr(map->ceiling, LIMIT_INT_STD);
		printf("printing floor:\n");
		printing_nbr_arr(map->floor, LIMIT_INT_STD);
		printf("MAJOR SCOPE\n");
		display_map_visual((map)->map_layout, LIMIT_INT_STD);
	}
	else
		printf("An error occurred\n");
	if (map)
		free_map(&map);
	return (0);
}
