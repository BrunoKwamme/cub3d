/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:33:45 by bkwamme           #+#    #+#             */
/*   Updated: 2025/06/12 20:12:31 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	put_error(char	*error_msg, t_instance **inst, int cubfd)
{
	if (cubfd != -1)
		close(cubfd);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_msg, 2);
	if (inst == NULL)
		clean_exit(NULL, 2);
	clean_exit(*inst, 2);
	return (0);
}
