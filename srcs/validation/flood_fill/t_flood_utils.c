/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_flood_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:53 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/04 20:33:18 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


t_flood	*create_flood_vector(int *vector, t_flood *head)
{
	t_flood *result;

	result = malloc(sizeof(t_flood) * 1);
	if (!result)
	return (NULL);
	result->vector[0] = vector[0];
	result->vector[1] = vector[1];
	result->head = head;
	result->next = NULL;
	return (result);
}

void	new_node_flood(t_flood **new_vec, int *vector)
{
	t_flood	*head;

	head = *new_vec;
	while ((*new_vec)->next != NULL)
	{
		(*new_vec) = (*new_vec)->next;
		// printf("i went next\n");
	}
	(*new_vec)->next = create_flood_vector(vector, head);
	*new_vec = head;
}

void free_flood_vector(t_flood **erase)
{
	t_flood *next;
	if (!(*erase))
		return ;
	while ((*erase))
	{
		next = (*erase)->next;
		free((*erase));
		*erase = next;
	}
}


static t_flood *set_error_vector(t_flood **v_head)
{
	t_flood	*new_vector;
	int		return_negative[2];

	return_negative[0] = -1;
	return_negative[1] = -1;
	new_vector = create_flood_vector((int *)return_negative, NULL);
	free_flood_vector(v_head);
	return (new_vector);
}

int is_new_vector(t_flood *new_vec, int y, int x)
{
	t_flood *head;

	head = new_vec;
	while (new_vec)
	{
		if (new_vec->vector[0] == y && new_vec->vector[1] == x)
			return (0);
		new_vec = new_vec->next;
	}
	new_vec = head;
	return (1);
}

t_flood	*process_spaces(t_flood *vectors, int **layout, int max_vector)
{
	t_flood *new_zeros;
	t_flood *head;
	int		verify_value;

	new_zeros = NULL;
	head = vectors;
	if (!vectors)
		return (NULL);
	while (vectors)
	{
		verify_value = verify_around(layout, vectors->vector, max_vector, &new_zeros);
		if (verify_value < 0)
		{
			printf("ENTERING VERIFY MINOR THAN 0\n");
			free_flood_vector(&new_zeros);
			new_zeros = NULL;
			return (set_error_vector(&head));
		}
		vectors = vectors->next;
	}
	free_flood_vector(&head);
	printing_coordinates(new_zeros);
	return (new_zeros);
}

int	do_flood_fill(int *first_pos, int **map_layout, int max_sz)
{
	t_flood *vectors;
	// int		i;
	(void)max_sz;

	// i = 0;
	vectors = create_flood_vector(first_pos, NULL);
	// printf("OUT WHILE OF FLOOD_FILL - \n");
	while (vectors)
	{
		// printf("INSIDE WHILE OF FLOOD_FILL -\n");
		vectors = process_spaces(vectors, map_layout, max_sz);
		if (vectors && vectors->vector[0] < 0)
		{
			free_flood_vector(&vectors);
			return (-1);
		}
		// printf("SPACES PROCESSED - execution %d\n--------------------------------\n\n", i);
		// display_map_visual(map_layout, LIMIT_INT_STD);
		// printf("EXECUTION ENDL\n--------------------------------\n\n");
	}
	free_flood_vector(&vectors);
	return (1);
}

