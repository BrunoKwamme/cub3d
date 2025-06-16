/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:13:34 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/16 16:26:53 by bkwamme          ###   ########.fr       */
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
