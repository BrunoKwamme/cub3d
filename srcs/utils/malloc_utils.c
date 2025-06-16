/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:47:42 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/16 16:25:09 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_scene(t_scene *scene)
{
	scene->bits_per_pixel = 0;
	scene->size_line = 0;
	scene->endian = 0;
	scene->int_addr = NULL;
	scene->img = NULL;
}

static void	init_map(t_map *map)
{
	map->map_layout = NULL;
	map->person_pos[0] = -1;
	map->person_pos[1] = -1;
	map->horizontal_size = 0;
	map->vertical_size = 0;
}

static void	set_player(t_player *player)
{
	player->dir = 0;
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}

static void	init_texture(t_texture *texture)
{
	texture->north_path = NULL;
	texture->south_path = NULL;
	texture->west_path = NULL;
	texture->east_path = NULL;
	texture->floor[0] = -1;
	texture->floor[1] = -1;
	texture->floor[2] = -1;
	texture->floor[3] = LIMIT_INT_STD;
	texture->ceiling[0] = -1;
	texture->ceiling[1] = -1;
	texture->ceiling[2] = -1;
	texture->ceiling[3] = LIMIT_INT_STD;
	texture->hex_floor = 0x0;
	texture->hex_ceiling = 0x0;
	texture->size = TEXTURE_SIZE;
	texture->step = 0;
	texture->pos = 0;
	texture->x = 0;
	texture->y = 0;
}

void	set_instance(t_instance *instance)
{
	instance->mlx = NULL;
	instance->win = NULL;
	instance->win_height = WIN_HEIGHT;
	instance->win_width = WIN_WIDTH;
	instance->texts_buffer = NULL;
	instance->screen_pixels = NULL;
	init_map(&instance->map);
	init_scene(&instance->scene);
	init_texture(&instance->texture);
	set_player(&instance->player);
}
