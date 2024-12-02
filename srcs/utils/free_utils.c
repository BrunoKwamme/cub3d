/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:47:42 by bkwamme           #+#    #+#             */
/*   Updated: 2024/12/02 11:05:19 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_str(char **str)
{
	if (!str)
		return ;
	free(*str);
	*str = NULL;
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

void	free_map(t_map **map)
{
	free_str(&(*map)->no_texture);
	free_str(&(*map)->so_texture);
	free_str(&(*map)->we_texture);
	free_str(&(*map)->ea_texture);
	free_str_arr((*map)->map_layout);
	free(*map);
	*map = NULL;
}
