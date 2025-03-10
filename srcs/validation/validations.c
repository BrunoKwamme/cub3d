/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:58:00 by bkwamme           #+#    #+#             */
/*   Updated: 2025/03/08 18:40:03 by gabrfern         ###   ########.fr       */
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

void	validation_error(int fd, t_map **map)
{
	if (!(*map)->ea_texture)
		put_error("MISSING EAST TEXTURE");
	if (!(*map)->no_texture)
		put_error("MISSING NORTH TEXTURE");
	if (!(*map)->we_texture)
		put_error("MISSING WEST TEXTURE");
	if (!(*map)->so_texture)
		put_error("MISSING SOUTH TEXTURE");
	if ((*map)->ceiling[0] == -1)
		put_error("MISSING CEILING COLOR");
	if ((*map)->floor[0] == -1)
		put_error("MISSING FLOOR COLOR");
	printf("VALIDATION COMPLETE!\n");
	close(fd);
	free_map(map);
}

int	is_map_filled (t_map **map, int flag)
{
	if (flag != 0)
		return (1);
	if (!(*map)->no_texture || !(*map)->so_texture
		|| !(*map)->we_texture || !(*map)->ea_texture
			|| (*map)->floor[0] == -1 || (*map)->ceiling[0] == -1)
		return (0);
	return (1);
}
