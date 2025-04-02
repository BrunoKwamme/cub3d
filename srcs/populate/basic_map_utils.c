/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:33:15 by gabrfern          #+#    #+#             */
/*   Updated: 2025/03/20 00:53:35 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_size_map(int **element)
{
	int	i;

	i = 0;
	// printf("ENTERING ON GETSIZEMAP\n");
	if (!element)
		return (0);
	// printf("ELEMENT IS NOT NULL\n");
	while (element[i] != NULL)
		i++;
	return (i);
}

int	int_arr_len(int *line, int delimiter)
{
	int	i;

	i = 0;
	while (line[i] != delimiter)
		i++;
	return i + 1;
}

void	realloc_line(int *old_line, int **new_line)
{
	int	i;

	i = 0;
	(*new_line) = (int *)malloc(sizeof(int) * int_arr_len(old_line, LIMIT_INT_STD));
	while (old_line[i] != LIMIT_INT_STD)
	{
		(*new_line)[i] = old_line[i];
		i++;
	}
	(*new_line)[i] = LIMIT_INT_STD;
}

void realloc_and_fill(t_map **map, int *new_lines)
{
	int	**temp_int;
	int	i;
	int	new_map;

	new_map = get_size_map((*map)->map_layout) + 2;
	temp_int = (int **)malloc(sizeof(int *) * (new_map + 1));
	i = 0;
	while ((*map)->map_layout && (*map)->map_layout[i] != NULL)
	{
		realloc_line((*map)->map_layout[i], &temp_int[i]);
		i++;
	}
	realloc_line(new_lines, &temp_int[i]);
	temp_int[i + 1] = NULL;
	free_int_arr((*map)->map_layout);
	(*map)->map_layout = (int **)malloc(sizeof(int *) * new_map);
	i = 0;
	while (temp_int[i] != NULL)
	{
		realloc_line(temp_int[i], &(*map)->map_layout[i]);
		i++;
	}
	(*map)->map_layout[i] = NULL;
	free_int_arr(temp_int);
}

int	*get_position_vector(t_map *map, int is_staging)
{
	int pos_y;
	int	pos_x;
	int	**vector_cp;
	int	*result;

	result = (int *)malloc(3 * sizeof(int));
	vector_cp = map->map_layout;
	pos_y = -1;
	while(vector_cp[++pos_y] != NULL)
	{
		pos_x = 0;
		while (vector_cp[pos_y][pos_x] != LIMIT_INT_STD)
		{
			if (vector_cp[pos_y][pos_x] > is_staging + 1)
			{
				printf("MAJOR THAN ONE - pos x is: %d and pos y is: %d\n", pos_x, pos_y);
				result[0] = pos_y;
				result[1] = pos_x;
				result[2] = LIMIT_INT_STD;
				return (result);
			}
			pos_x++;
		}
	}
	return (int *)(0);
}
