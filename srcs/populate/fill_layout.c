/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_layout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:23:48 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/17 21:39:07 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_max_hsize(int **arr)
{
	int	i;
	int	max_v;
	int	temp_v;

	i = 0;
	max_v = 0;
	temp_v = 0;
	while (i < get_size_map(arr))
	{
		temp_v = int_arr_len(arr[i], LIMIT_INT_STD);
		if (temp_v > max_v)
			max_v = temp_v;
		i++;
	}
	return (max_v);
}

static void	check_temp(int **line, int max_sz, int *temp)
{
	int	i;

	i = 0;
	while (temp[i] != LIMIT_INT_STD)
	{
		(*line)[i] = temp[i];
		i++;
	}
	free(temp);
	while (i < max_sz - 1)
	{
		(*line)[i] = EMPTY;
		i++;
	}
	(*line)[i] = LIMIT_INT_STD;
}

static void	fill_with_empty(int **line, int max_sz)
{
	int	*temp;
	int	i;

	i = 0;
	temp = (int *)malloc(sizeof(int) * (max_sz + 1));
	while ((*line)[i] != LIMIT_INT_STD)
	{
		temp[i] = (*line)[i];
		i++;
	}
	temp[i] = LIMIT_INT_STD;
	free(*line);
	*line = NULL;
	(*line) = (int *)malloc(sizeof(int) * (max_sz));
	check_temp(line, max_sz, temp);
}

void	turn_map_in_sqr(t_map *map, int fd)
{
	int		i;
	int		max_sz;

	(void)fd;
	max_sz = map_max_hsize((map)->map_layout);
	(map)->hor_size = max_sz;
	if (!(map)->map_layout)
		put_error("MAP IS NULL", NULL, fd);
	i = 0;
	while ((map)->map_layout[i] != NULL)
	{
		if (int_arr_len((map)->map_layout[i], LIMIT_INT_STD) < max_sz)
			fill_with_empty(&(map)->map_layout[i], max_sz);
		i++;
	}
	(map)->ver_size = i;
}
