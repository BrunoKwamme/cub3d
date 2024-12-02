/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:24:20 by bkwamme           #+#    #+#             */
/*   Updated: 2024/12/02 10:57:29 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


int	populate_textures(t_map **map, char *map_input)
{
	if (!(*map)->no_texture && ft_strncmp(map_input, "NO", 2) == 0)
		(*map)->no_texture = ft_strdup(map_input);
	else if (!(*map)->so_texture  && ft_strncmp(map_input, "SO", 2) == 0)
		(*map)->so_texture = ft_strdup(map_input);
	else if (!(*map)->we_texture && ft_strncmp(map_input, "WE", 2) == 0)
		(*map)->we_texture = ft_strdup(map_input);
	else if (!(*map)->ea_texture && ft_strncmp(map_input, "EA", 2) == 0)
		(*map)->ea_texture = ft_strdup(map_input);
	else if (!(*map)->floor && ft_strncmp(map_input, "F", 1) == 0)
		(*map)->floor = ft_atoi(map_input);
	else if (!(*map)->ceiling && ft_strncmp(map_input, "C", 1) == 0)
		(*map)->ceiling = ft_atoi(map_input);
	else
		return (1);
	return (0);
}

int	is_map_filled (t_map **map)
{
	if (!(*map)->no_texture || !(*map)->so_texture
		|| !(*map)->we_texture || !(*map)->ea_texture
			|| !(*map)->floor || !(*map)->ceiling)
		return (1);
	return (0);
}

void	malloc_map(t_map **map)
{
	*map = malloc(sizeof(t_map) * 1);
	(*map)->map_layout = NULL;
	(*map)->no_texture = NULL;
	(*map)->so_texture = NULL;
	(*map)->we_texture = NULL;
	(*map)->ea_texture = NULL;
	(*map)->floor = 0;
	(*map)->ceiling = 0;
}

t_map	*populate_map()
{
	int		fd;
	int		flag;
	char	*map_input;
	t_map	*map;

	malloc_map(&map);
	flag = 0;
	fd = open("./map1.cub", O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("FD: ERROR", 2), NULL);
	map_input = get_next_line(fd);
	while (map_input)
	{
		if (map_input && (ft_strncmp(map_input, "NO", 2) == 0
			|| ft_strncmp(map_input, "SO", 2) == 0
				|| ft_strncmp(map_input, "WE", 2) == 0
					|| ft_strncmp(map_input, "EA", 2) == 0
						|| ft_strncmp(map_input, "F", 1) == 0
							|| ft_strncmp(map_input, "C", 1) == 0))
			flag += populate_textures(&map, map_input);
		else
			flag += is_map_filled(&map);
		free_str(&map_input);
		map_input = get_next_line(fd);
	}
	close(fd);
	free_str(&map_input);
	return (map);
}

/*
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0
 */
