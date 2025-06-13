/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:58:00 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/12 20:23:19 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	dot_count(char	*argv)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '.')
			flag++;
		i++;
	}
	return (flag);
}

int argument_val(char **argv)
{
	char	*str;
	int		dot_num;

	dot_num = dot_count(argv[1]);
	if (ft_strncmp(argv[1], "./", 2) != 0 && dot_num != 1)
		return (1);
	str = ft_strdup(ft_strrchr(argv[1], '.'));
	if (str == NULL)
		return (1);
	if (ft_strcmp(str, ".cub") != 0)
	{
		free_str(&str);
		return (1);
	}
	free_str(&str);
	return (0);
}

int validate_texture(t_instance *inst, int i, int fd)
{
	char	*str;

	if (fd != -1)
		close(fd);
	if (i == 0)
		str = ft_strnstr(inst->texture.east_path, ".xpm", ft_strlen(inst->texture.east_path));
	else if (i == 1)
		str = ft_strnstr(inst->texture.north_path, ".xpm", ft_strlen(inst->texture.north_path));
	else if (i == 2)
		str = ft_strnstr(inst->texture.west_path, ".xpm", ft_strlen(inst->texture.west_path));
	else if (i == 3)
		str = ft_strnstr(inst->texture.south_path, ".xpm", ft_strlen(inst->texture.south_path));
	if (ft_strlen(str) != 4)
			return (1);
	return (0);
}

int	validation_error(t_instance *inst, int cubfd)
{
	int	i;
	int	fd;

	fd = -1;
	i = 0;
	while (i < 4)
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
	printf("VALIDATION COMPLETE!\n");
	return (0);
}

int	is_map_filled(t_texture *texture, int flag)
{
	if (flag != 0)
		return (1);
	if (!texture->north_path || !texture->south_path
		|| !texture->west_path || !texture->east_path
			|| texture->floor[0] == -1 || texture->ceiling[0] == -1)
		return (0);
	return (1);
}
