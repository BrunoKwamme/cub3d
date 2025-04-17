/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:14:04 by gabrfern          #+#    #+#             */
/*   Updated: 2025/04/09 01:10:02 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"



static void add_vector_to_node(t_flood **new_vec, int y, int x)
{
	int	vector[2];
	int	*ptr;

	printf("\n\nFUNCTION ADD VECTOR TO NODE WAS CALLED:\n");
	vector[0] = y;
	vector[1] = x;
	ptr = &vector[0];
	printf("POINTER IN 0: %d and POINTER IN 1: %d\n", ptr[0], ptr[1]);
	if (!is_new_vector(*new_vec, y, x))
		return ;
	if (!(*new_vec))
	{
		printf("I Entered in create a new vector with coordenates\n");
		*new_vec = create_flood_vector(ptr, NULL);
	}
	else
	{
		printf("I Entered in make a new node at the end\n");
		new_node_flood(new_vec, ptr);
	}
	printf("PRINTING VECTOR STRUCT TO VALIDATION\n");
	printing_coordinates(*new_vec);
	printf("EXECUTION ENDL\n----------------------------------\n");
}

int verify_vector(int **layout, int y, int x, t_flood **new_vec)
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
	(void)max_vector;
	int count;

	count = 0;
	count += verify_vector(layout, vector[0], vector[1], new_vec);
	count += verify_vector(layout, vector[0], vector[1] - 1, new_vec);
	count += verify_vector(layout, vector[0], vector[1] + 1, new_vec);
	count += verify_vector(layout, vector[0] + 1, vector[1], new_vec);
	count += verify_vector(layout, vector[0] - 1, vector[1], new_vec);
	count += verify_vector(layout, vector[0] - 1, vector[1] - 1, new_vec);
	count += verify_vector(layout, vector[0] + 1, vector[1] + 1, new_vec);
	count += verify_vector(layout, vector[0] + 1, vector[1] - 1, new_vec);
	count += verify_vector(layout, vector[0] - 1, vector[1] + 1, new_vec);
	printf("COUNT IS: %d\n", count);
	if (count < 9)
		return (-1);
	if ((*new_vec) != NULL)
		return (1);
	return (0);
}



int	flood_fill(t_map *map)
{
	int	*pos;
	int max_sz;
	int res;

	max_sz = map_max_hsize(map->map_layout);
	pos = get_position_vector(map, STAGING);
	printf("PRINTING POS VECTOR\n");
	printing_nbr_arr(pos, LIMIT_INT_STD);
	// display_map_visual(map->map_layout, LIMIT_INT_STD);
	res = do_flood_fill(pos, map->map_layout, max_sz);

	free(pos);
	pos = NULL;
	return res;
}
