/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:47:11 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/12 20:57:10 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_instance	instance;

	printf("map is -> %s\n", argv[1]);
	if (argc != 2 || argument_val(argv) != 0)
		return (put_error("BAD INPUT", NULL, -1), 2);
	set_instance(&instance);
	if (read_document(argv[1], &instance) == 0)
		return (0);
	// I declared the next variables only for debug, delete after
	t_map		*map = &instance.map;
	t_texture	texture = instance.texture;
	// Don't forget to exclude the lines that contains it's names.
	if (map != NULL)
	{
		printf("printing ceiling: hex is: %lx\n", texture.hex_ceiling);
		printing_nbr_arr(texture.ceiling, LIMIT_INT_STD);
		printf("printing floor: hex is: %lx\n", texture.hex_floor);
		printing_nbr_arr(texture.floor, LIMIT_INT_STD);
		printf("DOCUMENT COMPLETED THE READ✅\n*****************************************\n");
		printf("north_path -> %s\nsouth_path ->%s\nwest_path -> %s\neast_path -> %s\n",  texture.north_path, texture.south_path, texture.west_path, texture.east_path);
		printf("DISPLAYING MAP ARRAY:\n");
		display_map_visual((map)->map_layout, LIMIT_INT_STD);
		printf("WIN WIDTH : %d | WIN HEIGTH : %d\n", instance.win_width, instance.win_height);
		set_render_info(&instance);
		render_images(&instance);
		listen_for_input(&instance);
		mlx_loop_hook(instance.mlx, hook_render, &instance);
		mlx_loop(instance.mlx);
	}
	else
		printf("An error occurred\n");

	return (0);
}
