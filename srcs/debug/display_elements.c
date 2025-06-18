/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern@student.42.rio <gabrfern@stude    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:44:45 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/17 22:47:36 by gabrfern@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	display_map_visual(int **arr, int reading_limit)
{
	int	i_arr;
	int	i;

	i_arr = 0;
	while (arr[i_arr] != NULL)
	{
		i = 0;
		while (arr[i_arr][i] != reading_limit)
		{
			if (arr[i_arr][i] == 1)
				printf("\033[31m");
			if (arr[i_arr][i] >= NORTH && arr[i_arr][i] <= WEST)
				printf("\033[0;32m");
			if (arr[i_arr][i] < 10 && arr[i_arr][i] > -1)
				printf("%d   ", arr[i_arr][i]);
			else
				printf("%d  ", arr[i_arr][i]);
			i++;
			printf("\033[0m");
		}
		printf("\n");
		i_arr++;
	}
}
