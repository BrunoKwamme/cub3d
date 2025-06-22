/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern@student.42.rio <gabrfern@stude    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:14:04 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/17 22:47:12 by gabrfern@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	add_vector_to_node(t_flood **new_vec, int y, int x)
{
	int	vector[2];
	int	*ptr;

	vector[0] = y;
	vector[1] = x;
	ptr = &vector[0];
	if (!is_new_vector(*new_vec, y, x))
		return ;
	if (!(*new_vec))
		*new_vec = create_flood_vector(ptr, NULL);
	else
		new_node_flood(new_vec, ptr);
}

int	verify_vector(int **layout, int y, int x, t_flood **new_vec)
{
	if (layout[y][x] == GROUND || layout[y][x] == WALL ||
	(layout[y][x] >= 2 && layout[y][x] <= 5))
		return (1);
	else if (layout[y][x] == GROUND_STG || layout[y][x] == WALL_STG)
	{
		if (layout[y][x] == GROUND_STG)
			add_vector_to_node(new_vec, y, x);
		layout[y][x] = layout[y][x] - STAGING;
		return (1);
	}
	else if (layout[y][x] > 5)
	{
		layout[y][x] = layout[y][x] - STAGING;
		return (1);
	}
	return (0);
}

int	verify_around(int **layout, int *vector, int max_vector, t_flood **new_vec)
{
	int	count;

	(void)max_vector;
	count = 0;
	count += verify_vector(layout, vector[0], vector[1], new_vec);
	count += verify_vector(layout, vector[0] + 1, vector[1], new_vec);
	count += verify_vector(layout, vector[0] - 1, vector[1], new_vec);
	count += verify_vector(layout, vector[0], vector[1] + 1, new_vec);
	count += verify_vector(layout, vector[0], vector[1] - 1, new_vec);
	if (count < 5)
		return (-1);
	if ((*new_vec) != NULL)
		return (1);
	return (0);
}

int	flood_fill(t_map *map)
{
	int	*pos;
	int	max_sz;
	int	res;

	max_sz = map_max_hsize(map->map_layout);
	pos = get_position_vector(map, STAGING);
	map->person_pos[0] = pos[0];
	map->person_pos[1] = pos[1];
	res = do_flood_fill(pos, map->map_layout, max_sz);
	free(pos);
	pos = NULL;
	return (res);
}
