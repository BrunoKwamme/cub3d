/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:58:00 by bkwamme           #+#    #+#             */
/*   Updated: 2025/05/04 19:24:10 by gabrfern         ###   ########.fr       */
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

int	validation_error(int fd, t_instance *inst)
{
	if (!(inst->texture).east_path)
		put_error("MISSING EAST TEXTURE");
	if (!(inst->texture).north_path)
		put_error("MISSING NORTH TEXTURE");
	if (!(inst->texture).west_path)
		put_error("MISSING WEST TEXTURE");
	if (!(inst->texture).south_path)
		put_error("MISSING SOUTH TEXTURE");
	if ((inst->texture).ceiling[0] == -1)
		put_error("MISSING CEILING COLOR");
	if ((inst->texture).floor[0] == -1)
		put_error("MISSING FLOOR COLOR");
	printf("VALIDATION COMPLETE!\n");
	close(fd);
	free_instance(inst);
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
