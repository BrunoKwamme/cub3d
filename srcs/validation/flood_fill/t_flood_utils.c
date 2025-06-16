/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_flood_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:05:53 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/16 16:34:46 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_flood	*create_flood_vector(int *vector, t_flood *head)
{
	t_flood	*result;

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
		(*new_vec) = (*new_vec)->next;
	(*new_vec)->next = create_flood_vector(vector, head);
	*new_vec = head;
}

void	free_flood_vector(t_flood **erase)
{
	t_flood	*next;

	if (!(*erase))
		return ;
	while ((*erase))
	{
		next = (*erase)->next;
		free((*erase));
		*erase = next;
	}
}

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

int	is_new_vector(t_flood *new_vec, int y, int x)
{
	t_flood	*head;

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
