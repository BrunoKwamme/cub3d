/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_input_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:14:55 by bkwamme           #+#    #+#             */
/*   Updated: 2024/12/04 12:01:04 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*element_id_rm(char *map_input)
{
	char	*str;
	int		i;
	int		start;
	int		str_i;

	str_i = 0;
	i = 2;
	while (map_input[i] != '\0' && map_input[i] == ' ')
		i++;
	start = i;
	while (map_input[start] != '\0'
		&& (map_input[start] != ' ' || map_input[start] != '\n'))
		start++;
	str = ft_calloc(sizeof(char), (start - i));
	while (i != start)
	{
		str[str_i] = map_input[i];
		str_i++;
		i++;
	}
	str[--str_i] = '\0';
	return (str);
}

int	populate_textures(t_map **map, char *map_input)
{
	if (!(*map)->no_texture && ft_strncmp(map_input, "NO", 2) == 0)
		(*map)->no_texture = element_id_rm(map_input);
	else if (!(*map)->so_texture  && ft_strncmp(map_input, "SO", 2) == 0)
		(*map)->so_texture = element_id_rm(map_input);
	else if (!(*map)->we_texture && ft_strncmp(map_input, "WE", 2) == 0)
		(*map)->we_texture = element_id_rm(map_input);
	else if (!(*map)->ea_texture && ft_strncmp(map_input, "EA", 2) == 0)
		(*map)->ea_texture = element_id_rm(map_input);
	else if (!(*map)->floor && ft_strncmp(map_input, "F", 1) == 0)
		(*map)->floor = ft_atoi(map_input);
	else if (!(*map)->ceiling && ft_strncmp(map_input, "C", 1) == 0)
		(*map)->ceiling = ft_atoi(map_input);
	else
		return (1);
	return (0);
}

int	is_element_filled (t_map **map, int flag)
{
	if (flag != 0)
		return (1);
	if (!(*map)->no_texture || !(*map)->so_texture
		|| !(*map)->we_texture || !(*map)->ea_texture
			|| (*map)->floor != 0 || (*map)->ceiling != 0)
		return (1);
	return (0);
}

void	validation_error(t_map **map)
{
	if (!(*map)->ea_texture)
		put_error("MISSING EAST TEXTURE");
	if (!(*map)->no_texture)
		put_error("MISSING NORTH TEXTURE");
	if (!(*map)->we_texture)
		put_error("MISSING WEST TEXTURE");
	if (!(*map)->so_texture)
		put_error("MISSING SOUTH TEXTURE");
	if ((*map)->ceiling == 0)
		put_error("MISSING CEILING COLOR");
	if ((*map)->floor == 0)
		put_error("MISSING FLOOR COLOR");
	//free_map(map);
}
