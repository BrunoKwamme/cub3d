/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout_populate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 21:44:23 by gabrfern          #+#    #+#             */
/*   Updated: 2025/03/10 02:24:15 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


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
		if (ft_isspace(line_fill[i]))
			(*temp)[i] = EMPTY;
		else if (line_fill[i] == 'S')
			(*temp)[i] = SOUTH;
		else if (line_fill[i] == 'N')
			(*temp)[i] = NORTH;
		else if (line_fill[i] == 'E')
			(*temp)[i] = EAST;
		else if (line_fill[i] == 'W')
			(*temp)[i] = WEST;
		else if ((int)line_fill[i] - 48 != WALL && (int)line_fill[i] - 48 != GROUND)
			return (0);
		else
			(*temp)[i] = (int)line_fill[i] - 48;
		i++;
	}
	(*temp)[i] = LIMIT_INT_STD;
	return (1);
}

static int	get_size_map(int **element)
{
	int	i;

	i = 0;
	// printf("ENTERING ON GETSIZEMAP\n");
	if (!element)
		return (2);
	// printf("ELEMENT IS NOT NULL\n");
	while (element[i] != NULL)
		i++;
	return (i + 2);
}

static int	int_len(int *line, int delimiter)
{
	int	i;

	i = 0;
	while (line[i] != delimiter)
		i++;
	return i + 1;
}

static void	realloc_line(int *old_line, int **new_line)
{
	int	i;

	i = 0;
	(*new_line) = (int *)malloc(sizeof(int) * int_len(old_line, LIMIT_INT_STD));
	while (old_line[i] != LIMIT_INT_STD)
	{
		(*new_line)[i] = old_line[i];
		i++;
	}
	(*new_line)[i] = LIMIT_INT_STD;
}

static void realloc_and_fill(t_map **map, int *new_lines)
{
	int	**temp_int;
	int	i;
	int	new_map;
	// printf("entering on get_size_map\n");
	new_map = get_size_map((*map)->map_layout);
	// printf("OUT OF GET_SIZE_MAP, value is: %d\n", new_map);
	temp_int = (int **)malloc(sizeof(int *) * (new_map + 1));
	i = 0;
	while ((*map)->map_layout && (*map)->map_layout[i] != NULL)
	{
		// printf("function realloc line\n");
		realloc_line((*map)->map_layout[i], &temp_int[i]);
		i++;
	}
	// printf("realloc outside while, i is: %d\n", i);
	realloc_line(new_lines, &temp_int[i]);
	temp_int[i + 1] = NULL;
	free_int_arr((*map)->map_layout);
	(*map)->map_layout = (int **)malloc(sizeof(int *) * new_map);
	i = 0;
	while (temp_int[i] != NULL)
	{
		// printf("realloc on real line\n");
		realloc_line(temp_int[i], &(*map)->map_layout[i]);
		i++;
	}
	(*map)->map_layout[i] = NULL;
	free_int_arr(temp_int);
}

int	map_allocation(t_map **map, char *map_info)
{
	int		*temp_convert;

	if (line_empty(map_info))
		return (0);
	fill_line(&temp_convert, map_info);
	realloc_and_fill(map, temp_convert);
	free(temp_convert);

	return (1);

}
