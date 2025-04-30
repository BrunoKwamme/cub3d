/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:47:11 by bkwamme           #+#    #+#             */
/*   Updated: 2025/04/30 00:58:32 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	img;

	if (argc != 2 || argument_val(argv) != 0)
		return (put_error("BAD INPUT"), 2);
	map = read_document(argv[1]);
	if (map != NULL)
	{
		printf("north -> %s\nsouth ->%s\nweast -> %s\neast -> %s\n", map->no_texture, map->so_texture, map->we_texture, map->ea_texture);
		printf("printing ceiling:\n");
		printing_nbr_arr(map->ceiling, LIMIT_INT_STD);
		printf("printing floor:\n");
		printing_nbr_arr(map->floor, LIMIT_INT_STD);
		printf("MAJOR SCOPE\n");
		display_map_visual((map)->map_layout, LIMIT_INT_STD);
		// start_mlx(&map); //OFICIAL
		my_mlx_start(&map, &img); //DEBUG
	}
	else
		printf("An error occurred\n");
	if (map)
		free_map(&map);
	mlx_loop(img.mlx);
	return (0);
}
