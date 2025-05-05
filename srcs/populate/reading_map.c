/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:24:20 by bkwamme           #+#    #+#             */
/*   Updated: 2025/05/04 20:38:25 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	line_empty(char *map_info)
{
	int	i;

	i = 0;
	while (map_info[i] != '\0')
	{
		if (!ft_isspace(map_info[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	verify_entering(int flag, char *map_input)
{
	if (flag == 0 && (map_input &&
		(ft_strnstr(map_input, "NO", ft_strlen(map_input)) != NULL
			|| ft_strnstr(map_input, "SO", ft_strlen(map_input)) != NULL
				|| ft_strnstr(map_input, "WE", ft_strlen(map_input)) != NULL
					|| ft_strnstr(map_input, "EA", ft_strlen(map_input)) != NULL
						|| ft_strnstr(map_input, "F", ft_strlen(map_input)) != NULL
							|| ft_strnstr(map_input, "C", ft_strlen(map_input)) != NULL)))
		return (1);
	return (0);
}

static int read_basic_info(int fd, t_instance *inst)
{
	char 	*map_info;
	int		flag;

	flag = 0;
	map_info = get_next_line(fd);
	while (map_info)
	{
		if (verify_entering(flag, map_info))
			populate_textures(&(inst)->texture, map_info);
		flag += is_map_filled(&(inst)->texture, flag);
		if (flag > 0)
		{
			free_str(&map_info);
			return (1);
		}
		free_str(&map_info);
		map_info = get_next_line(fd);
	}
	free_str(&map_info);
	return (0);
}

static int	read_map_info(int fd, t_map *map)
{
	char	*map_info;

	map_info = get_next_line(fd);
	while (map_info && line_empty(map_info))
	{
		free_str(&map_info);
		map_info = get_next_line(fd);
	}
	while (map_info && !(line_empty(map_info)))
	{
		// printf("PRINTING MAP INFORMATION -> %s\n", map_info);
		if (map_allocation(map, map_info) == 0)
		{
			free_str(&map_info);
			return (0);
		}
		free_str(&map_info);
		map_info = get_next_line(fd);
	}
	free_str(&map_info);
	turn_map_in_sqr(map);
	return (1);
}

int	read_document(char *argv, t_instance *inst)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (put_error("BAD FD"));
	if (read_basic_info(fd, inst) == 0 || read_map_info(fd, &(inst->map)) == 0)
			return (validation_error(fd, inst));

	if (flood_fill(&(inst->map)) == -1)
	{
		put_error("MAP DIDN't passed flood fill");
		free_map(&(inst->map));
		close(fd);
		return (0);
	}
	close(fd);
	printf("passed basic info\n");
	return (1);
}
