/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:44:23 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/04 22:33:28 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_map_vector(int **temp, char *line_fill, int i)
{
	if (ft_isspace(line_fill[i]))
		(*temp)[i] = EMPTY;
	else if (line_fill[i] == 'S')
		(*temp)[i] = SOUTH + STAGING;
	else if (line_fill[i] == 'N')
		(*temp)[i] = NORTH + STAGING;
	else if (line_fill[i] == 'E')
		(*temp)[i] = EAST + STAGING;
	else if (line_fill[i] == 'W')
		(*temp)[i] = WEST + STAGING;
	else if ((int)line_fill[i] - 48 != WALL && (int)line_fill[i] - 48 != GROUND)
		return (0);
	else
		(*temp)[i] = (int)line_fill[i] - 38;
	return (1);
}

static int	fill_line(int **temp, char *line_fill)
{
	int	size_all;
	int	i;

	size_all = 0;
	i = 0;
	while (line_fill[size_all] != '\n' && line_fill[size_all] != '\0')
		size_all++;
	(*temp) = (int *)malloc((size_all + 1) * sizeof(int));
	while (line_fill[i] != '\n' && line_fill[i] != '\0')
	{
		if (set_map_vector(temp, line_fill, i) == 0)
			return (0);
		i++;
	}
	(*temp)[i] = LIMIT_INT_STD;
	return (1);
}

int	map_allocation(t_map *map, char *map_info)
{
	int		*temp_convert;

	if (line_empty(map_info))
		return (0);
	if (fill_line(&temp_convert, map_info) == 0)
		return (0);
	realloc_and_fill(map, temp_convert);
	free(temp_convert);
	return (1);
}
