/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_val.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:58:00 by bkwamme           #+#    #+#             */
/*   Updated: 2024/12/03 12:54:10 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	dot_count(char	*argv)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '.')
			flag++;
		i++;
	}
	return (flag);
}

int argument_val(char **argv)
{
	char	*str;
	int		dot_num;

	dot_num = dot_count(argv[1]);
	if (ft_strncmp(argv[1], "./", 2) != 0 && dot_num != 1)
		return (1);
	str = ft_strdup(ft_strrchr(argv[1], '.'));
	if (str == NULL)
		return (1);
	if (ft_strcmp(str, ".cub") != 0)
	{
		free_str(&str);
		return (1);
	}
	free_str(&str);
	return (0);
}
