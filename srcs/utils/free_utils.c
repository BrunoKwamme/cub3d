/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:13:34 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/04 19:41:34 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_str(char **str)
{
	if (!str)
		return ;
	if (!(*str))
		return ;
	free(*str);
	*str = NULL;
}

void	free_int(int *i)
{
	if (!i)
		return ;
	free(i);
}

void	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free_str(&arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_int_arr(int **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free_int(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_textures(t_texture *textures)
{
	free_str(&(textures->north_path));
	free_str(&(textures->south_path));
	free_str(&(textures->east_path));
	free_str(&(textures->west_path));
	textures = NULL;
}

void	free_map(t_map *map)
{
	free_int_arr((map)->map_layout);
	map = NULL;
}

void	free_instance(t_instance *inst)
{
	if (&(inst->map))
		free_map(&(inst->map));
	if (&(inst->texture))
		free_textures(&(inst->texture));
	free_int_arr(inst->texts_buffer);
}
