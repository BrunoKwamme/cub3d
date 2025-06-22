/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_flood_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:53 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/17 19:54:27 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_flood	*set_error_vector(t_flood **v_head)
{
	t_flood	*new_vector;
	int		return_negative[2];

	return_negative[0] = -1;
	return_negative[1] = -1;
	new_vector = create_flood_vector((int *)return_negative, NULL);
	free_flood_vector(v_head);
	return (new_vector);
}

t_flood	*process_spaces(t_flood *vectors, int **layout, int max_vector)
{
	t_flood	*new_zeros;
	t_flood	*head;
	int		verify_value;

	new_zeros = NULL;
	head = vectors;
	if (!vectors)
		return (NULL);
	while (vectors)
	{
		verify_value = verify_around(layout,
				vectors->vector, max_vector, &new_zeros);
		if (verify_value < 0)
		{
			free_flood_vector(&new_zeros);
			new_zeros = NULL;
			return (set_error_vector(&head));
		}
		vectors = vectors->next;
	}
	free_flood_vector(&head);
	return (new_zeros);
}

int	do_flood_fill(int *first_pos, int **map_layout, int max_sz)
{
	t_flood	*vectors;

	(void)max_sz;
	vectors = create_flood_vector(first_pos, NULL);
	while (vectors)
	{
		vectors = process_spaces(vectors, map_layout, max_sz);
		if (vectors && vectors->vector[0] < 0)
		{
			free_flood_vector(&vectors);
			return (-1);
		}
	}
	free_flood_vector(&vectors);
	return (1);
}
