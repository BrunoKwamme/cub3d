/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_validations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:43:34 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/17 21:16:26 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// void	verify_map_conditions(t_instance *inst,
// 	int fd, int *player_encountered, int ver)
// {
// 	int	hor;
// 	int	encountered_dir;

// 	hor = 0;
// 	while (hor < inst->map.horizontal_size)
// 	{
// 		encountered_dir = inst->map.map_layout[ver][hor] >= NORTH &&
// 			inst->map.map_layout[ver][hor] <= WEST;
// 		 if ((encountered_dir >= 1
// 		 		|| inst->map.map_layout[ver][hor] == GROUND)
// 		 	&& (ver == 0 || hor == 0 || (ver + 1) == inst->map.vertical_size
// 		|| (hor + 1) == inst->map.horizontal_size))
// 		{
// 			put_error("MAP ERROR", &inst, fd);
// 		}

// 		if (encountered_dir && *player_encountered == 0)
// 			*player_encountered = 1;
// 		else if (encountered_dir && *player_encountered == 1)
// 			put_error("DUPLICATED PLAYER POSITION\n", &inst, fd);
// 		hor++;
// 	}
// }

void	verify_map_conditions(t_instance *inst, int fd)
{
	int	ver;
	int	player_encountered;
	int	encountered_dir;
	int	hor;

	player_encountered = 0;
	ver = 0;
	printf("VALIDATE MAP CONDITION\n");
	while (ver < inst->map.vertical_size)
	{
		hor = 0;
		while (hor < inst->map.horizontal_size)
		{
			encountered_dir = inst->map.map_layout[ver][hor] >= NORTH &&
				inst->map.map_layout[ver][hor] <= WEST;
			if ((encountered_dir >= 1
					|| inst->map.map_layout[ver][hor] == GROUND)
				&& (ver == 0 || hor == 0 || (ver + 1) == inst->map.vertical_size
			|| (hor + 1) == inst->map.horizontal_size))
				put_error("MAP ERROR", &inst, fd);
			hor++;
		}
		ver++;
	}
}


void	validate_player_dir(t_instance *inst, int fd)
{
	int	ver;
	int	player_encountered;
	int	encountered_dir;
	int	hor;

	player_encountered = 0;
	ver = 0;
	printf("VALIDATE PLAYER DIR\n");
	while (ver < inst->map.vertical_size)
	{
		hor = 0;
		while (hor < inst->map.horizontal_size)
		{
			encountered_dir = inst->map.map_layout[ver][hor] >= NORTH + STAGING;
			if (encountered_dir && player_encountered == 0)
				player_encountered = 1;
			else if (encountered_dir && player_encountered == 1)
				put_error("DUPLICATED PLAYER POSITION\n", &inst, fd);
			if (encountered_dir >= 1
				&& (ver == 0 || hor == 0 || (ver + 1) == inst->map.vertical_size
			|| (hor + 1) == inst->map.horizontal_size))
				put_error("EU NÃO AGUENTO MAIS\n", &inst, fd);
			hor++;
		}
		ver++;
	}
	if (player_encountered == 0)
		put_error("PLAYER NOT ENCOUNTERED", &inst, fd);
}

int	validate_texture(t_instance *inst, int i, int fd)
{
	char	*str;

	if (fd != -1)
		close(fd);
	if (i == 0)
		str = ft_strnstr(inst->texture.east_path,
				".xpm", ft_strlen(inst->texture.east_path));
	else if (i == 1)
		str = ft_strnstr(inst->texture.north_path,
				".xpm", ft_strlen(inst->texture.north_path));
	else if (i == 2)
		str = ft_strnstr(inst->texture.west_path,
				".xpm", ft_strlen(inst->texture.west_path));
	else if (i == 3)
		str = ft_strnstr(inst->texture.south_path,
				".xpm", ft_strlen(inst->texture.south_path));
	if (ft_strlen(str) != 4)
		return (1);
	return (0);
}

void	verify_inst_textures(t_instance *inst, int cubfd, int fd, int i)
{
	if (i == 0)
	{
		fd = open(inst->texture.east_path, O_RDONLY);
		if (fd == -1 || validate_texture(inst, i, fd) == 1)
			put_error("ERROR EAST TEXTURE", &inst, cubfd);
	}
	else if (i == 1)
	{
		fd = open(inst->texture.north_path, O_RDONLY);
		if (fd == -1 || validate_texture(inst, i, fd) == 1)
			put_error("ERROR NORTH TEXTURE", &inst, cubfd);
	}
	else if (i == 2)
	{
		fd = open(inst->texture.west_path, O_RDONLY);
		if (fd == -1 || validate_texture(inst, i, fd) == 1)
			put_error("ERROR WEST TEXTURE", &inst, cubfd);
	}
	else if (i == 3)
	{
		fd = open(inst->texture.south_path, O_RDONLY);
		if (fd == -1 || validate_texture(inst, i, fd) == 1)
			put_error("ERROR SOUTH TEXTURE", &inst, cubfd);
	}
}

int	validation_error(t_instance *inst, int cubfd)
{
	int	i;
	int	fd;

	fd = -1;
	i = 0;
	while (i < 4)
	{
		verify_inst_textures(inst, cubfd, fd, i);
		i++;
	}
	if ((inst->texture.ceiling[0] < 0 || inst->texture.ceiling[0] > 255)
		|| (inst->texture.ceiling[1] < 0 || inst->texture.ceiling[1] > 255)
		|| (inst->texture.ceiling[2] < 0 || inst->texture.ceiling[2] > 255))
		put_error("ERROR CEILING COLOR", &inst, cubfd);
	if ((inst->texture.floor[0] < 0 || inst->texture.floor[0] > 255)
		|| (inst->texture.floor[1] < 0 || inst->texture.floor[1] > 255)
		|| (inst->texture.floor[2] < 0 || inst->texture.floor[2] > 255))
		put_error("ERROR FLOOR COLOR", &inst, cubfd);
	return (0);
}
