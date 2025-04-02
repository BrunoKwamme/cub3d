/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:47:42 by bkwamme           #+#    #+#             */
/*   Updated: 2025/03/13 10:31:57 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	malloc_map(t_map **map)
{
	*map = malloc(sizeof(t_map) * 1);
	(*map)->map_layout = NULL;
	(*map)->no_texture = NULL;
	(*map)->so_texture = NULL;
	(*map)->we_texture = NULL;
	(*map)->ea_texture = NULL;
	(*map)->floor[0] = -1;
	(*map)->floor[1] = -1;
	(*map)->floor[2] = -1;
	(*map)->ceiling[0] = -1;
	(*map)->ceiling[1] = -1;
	(*map)->ceiling[2] = -1;
	(*map)->person_pos[0] = -1;
	(*map)->person_pos[1] = -1;

}

void	free_str(char **str)
{
	if (!str)
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

void	free_colors_args(int (*arr)[3])
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

void	free_map(t_map **map)
{
	free_str(&(*map)->no_texture);
	free_str(&(*map)->so_texture);
	free_str(&(*map)->we_texture);
	free_str(&(*map)->ea_texture);
	free_int_arr((*map)->map_layout);
	free(*map);
	*map = NULL;
}
