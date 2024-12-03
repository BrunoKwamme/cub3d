/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:08:11 by gabrfern          #+#    #+#             */
/*   Updated: 2024/12/03 11:12:05 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char const *str, char const *cmp)
{
	int	i;

	i = 0;
	while ((str[i] != '\0' && cmp[i] != '\0') && str[i] == cmp[i])
		i++;
	return (str[i] - cmp[i]);
}
