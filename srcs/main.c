/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:47:11 by bkwamme           #+#    #+#             */
/*   Updated: 2025/05/04 19:24:10 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_instance	instance;

	if (argc != 2 || argument_val(argv) != 0)
		return (put_error("BAD INPUT"), 2);

	set_instance(&instance);
	if (read_document(argv[1], &instance) == 0)
		return (0);

	// I declared the next variables only for debug, delete after
	t_map		*map = &instance.map;
	t_texture	*texture = &instance.texture;
	// Don't forget to exclude the lines that contains it's names.
	if (map != NULL)
	{
		printf("I'M HERE\n");
		printf("north_path -> %s\nsouth_path ->%s\nweast_path -> %s\neast_path -> %s\n", texture->north_path, texture->south_path, texture->west_path, texture->east_path);
		printf("printing ceiling:\n");
		printing_nbr_arr(*(&texture->ceiling), LIMIT_INT_STD);
		printf("printing floor:\n");
		printing_nbr_arr(*(&texture->floor), LIMIT_INT_STD);
		printf("MAP DISPLAYED\n");
		display_map_visual((map)->map_layout, LIMIT_INT_STD);
		// start_mlx(&map); //OFICIAL
		// my_mlx_create_main(&map); //DEBUG
		free_instance(&instance);
	}
	else
		printf("An error occurred\n");

	return (0);
}
