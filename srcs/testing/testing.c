/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 01:18:24 by gabrfern          #+#    #+#             */
/*   Updated: 2025/04/30 01:25:17 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Create Image");
	void *image = mlx_new_image(mlx, 640, 360);
	int pixel_bits;
	int line_bytes;
	int endian;
	int *buffer = (int *)mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);
	line_bytes /= 4;
	int x = 0;
	int y = 0;
	int color = 0xFF0000;
	while (y <= 32)
	{
		x = 0;
		while (x <= 32)
		{
			buffer[(y * line_bytes) + x] = color;
			x++;
		}
		y++;
	}
	// The following code goes here.
	mlx_put_image_to_window(mlx, win, image, 32, 32);
	mlx_loop(mlx);
}
