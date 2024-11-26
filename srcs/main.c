/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:47:11 by bkwamme           #+#    #+#             */
/*   Updated: 2024/11/26 13:57:47 by bkwamme          ###   ########.fr       */
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

int main ()
{
	t_data	img;

	img.x = 5;
	img.y = 5;
	img.relative_path = "./assets/grass.xpm";
	printf("relative path -> %s\n", img.relative_path);
	img.color = 0x00FF0000;
	img.mlx = mlx_init();
	img.img = mlx_xpm_file_to_image(img.mlx, img.relative_path, &img.img_width, &img.img_height);
	img.mlx_win = mlx_new_window(img.mlx, 640, 480, "Hello, World!");
	//img.img = mlx_new_image(img.mlx, 640, 480);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, img.x, img.y, img.color);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 1L<<0, close_window, &img);
	mlx_loop(img.mlx);
	return (0);
}
