/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:47:11 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/16 17:29:58 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_instance	instance;
	t_map		*map;

	if (argc != 2 || argument_val(argv) != 0)
		return (put_error("BAD INPUT", NULL, -1), 2);
	set_instance(&instance);
	if (read_document(argv[1], &instance) == 0)
		return (0);
	map = &instance.map;
	if (map != NULL)
	{
		display_map_visual((map)->map_layout, LIMIT_INT_STD);
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
