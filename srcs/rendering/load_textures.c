/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:47:45 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/16 16:21:44 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gen_img_info(t_scene *img, t_instance *inst, char *path)
{
	init_scene(img);
	if (path != NULL)
		img->img = mlx_xpm_file_to_image(inst->mlx,
				path, &inst->texture.size, &inst->texture.size);
	if (img->img == NULL)
		quit_application(inst);
	img->int_addr = (int *)mlx_get_data_addr(img->img,
			&img->bits_per_pixel, &img->size_line, &img->endian);
	return ;
}

void	set_new_img(t_instance *inst, t_scene *scene, int width, int height)
{
	init_scene(scene);
	scene->img = mlx_new_image(inst->mlx, width, height);
	if (scene->img == NULL)
		quit_application(inst);
	scene->int_addr = (int *)mlx_get_data_addr(scene->img,
			&scene->bits_per_pixel, &scene->size_line, &scene->endian);
	return ;
}

int	*cub_xpm_to_img(t_instance *inst, char *path)
{
	t_scene	txt_img;
	int		*buff_result;
	int		x;
	int		y;

	gen_img_info(&txt_img, inst, path);
	buff_result = ft_calloc(1,
			sizeof * buff_result * (inst)->texture.size * (inst)->texture.size);
	if (!buff_result)
		quit_application(inst);
	y = 0;
	while (y < inst->texture.size)
	{
		x = 0;
		while (x < inst->texture.size)
		{
			buff_result[y * inst->texture.size + x]
				= txt_img.int_addr[y * inst->texture.size + x];
			++x;
		}
		y++;
	}
	mlx_destroy_image(inst->mlx, txt_img.img);
	return (buff_result);
}

void	load_texture_buffer(t_instance *inst)
{
	inst->texts_buffer = ft_calloc(5, sizeof(inst->texts_buffer));
	if (!inst->texts_buffer)
		return ;
	inst->texts_buffer[NO_TEXTURE]
		= cub_xpm_to_img(inst, inst->texture.north_path);
	inst->texts_buffer[SO_TEXTURE]
		= cub_xpm_to_img(inst, inst->texture.south_path);
	inst->texts_buffer[WE_TEXTURE]
		= cub_xpm_to_img(inst, inst->texture.west_path);
	inst->texts_buffer[EA_TEXTURE]
		= cub_xpm_to_img(inst, inst->texture.east_path);
}

void	set_render_info(t_instance *instance)
{
	instance->mlx = mlx_init();
	instance->win = mlx_new_window(instance->mlx,
			instance->win_width, instance->win_height, "Cub3d");
	load_texture_buffer(instance);
}
