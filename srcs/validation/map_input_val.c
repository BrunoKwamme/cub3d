/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:24:20 by bkwamme           #+#    #+#             */
/*   Updated: 2024/12/04 12:24:27 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


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

int	texture_id_condition(char *map_input, int flag)
{
	if (flag == 0 && (map_input &&
			(ft_strncmp(map_input, "NO", 2) == 0
				|| ft_strncmp(map_input, "SO", 2) == 0
					|| ft_strncmp(map_input, "WE", 2) == 0
						|| ft_strncmp(map_input, "EA", 2) == 0
							|| ft_strncmp(map_input, "F", 1) == 0
								|| ft_strncmp(map_input, "C", 1) == 0)))
		return (1);
	return (0);
}

int	read_file(int fd, int flag, t_map **map)
{
	char	*map_input;

	map_input = get_next_line(fd);
	while (map_input && is_element_filled(map, flag) == 1)
	{
		if (map_input[0] == '\n')
		{
			free_str(&map_input);
			map_input = get_next_line(fd);
			continue ;
		}
		if (texture_id_condition(map_input, flag) == 1)
			flag += populate_textures(map, map_input);
		else
			flag += is_element_filled(map, flag);
		free_str(&map_input);
		map_input = get_next_line(fd);
	}
	printf("%s", map_input);
	free_str(&map_input);
	return (flag);
}

t_map	*populate_map(char *argv)
{
	int		fd;
	int		flag;
	t_map	*map;

	malloc_map(&map);
	flag = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (put_error("BAD FD"), NULL);
	flag += read_file(fd, flag, &map);
	close(fd);
	if (flag != 0)
		return (validation_error(&map), NULL);
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
