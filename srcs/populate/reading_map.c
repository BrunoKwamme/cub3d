/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:24:20 by bkwamme           #+#    #+#             */
/*   Updated: 2025/03/08 16:39:14 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


t_map	*read_map(char *argv)
{
	int		fd;
	int		flag;
	char	*map_input;
	t_map	*map;

	malloc_map(&map);
	flag = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (put_error("BAD FD"), NULL);
	map_input = get_next_line(fd);
	while (map_input)
	{
		// printf("flag is: %d\n", flag);
		if (flag == 0 && (map_input &&
			(ft_strnstr(map_input, "NO", ft_strlen(map_input)) != NULL
				|| ft_strnstr(map_input, "SO", ft_strlen(map_input)) != NULL
					|| ft_strnstr(map_input, "WE", ft_strlen(map_input)) != NULL
						|| ft_strnstr(map_input, "EA", ft_strlen(map_input)) != NULL
							|| ft_strnstr(map_input, "F", ft_strlen(map_input)) != NULL
								|| ft_strnstr(map_input, "C", ft_strlen(map_input)) != NULL)))
				flag += populate_textures(&map, map_input);
		else
			flag += is_map_filled(&map, flag);
		free_str(&map_input);
		map_input = get_next_line(fd);
	}
	close(fd);
	free_str(&map_input);
	if (flag == 0)
		return (validation_error(&map), NULL);
	return (map);
}
