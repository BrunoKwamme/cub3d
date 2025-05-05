/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:35:19 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/05 03:17:41 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_screen_pixels(t_instance *inst)
{
	int	i;
	printf("SET SCREEN PIXELS\n");
	if (inst->screen_pixels)
		free_int_arr(inst->screen_pixels);
	inst->screen_pixels = ft_calloc(inst->win_height + 1,
			sizeof(inst->screen_pixels));
	if (!(inst->screen_pixels))
		return ; //CREATE ERROR EXIT
	i = 0;
	while (i < inst->win_height)
	{
		inst->screen_pixels[i] = ft_calloc(inst->win_width + 1,
				sizeof(inst->screen_pixels));
		if (!inst->screen_pixels[i])
			return ;//CREATE ERROR EXIT;
		i++;
	}
	printf("END OF FUNCTION\n*************************************\n");
}

static void	get_texture_index(t_instance *inst, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			inst->texture.index = WE_TEXTURE;
		else
			inst->texture.index = EA_TEXTURE;
	}
	else
	{
		if (ray->dir_y > 0)
			inst->texture.index = SO_TEXTURE;
		else
			inst->texture.index = NO_TEXTURE;
	}
}

void	update_texture_pixels(t_instance *inst, t_texture *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	get_texture_index(inst, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
	|| (ray->side == 1 && ray->dir_y > 0))
	tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - inst->win_height / 2
		+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;

	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = inst->texts_buffer[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			inst->screen_pixels[y][x] = color;
		y++;
	}
	printf("FINISHED UPDATE TEXTURE PIXELS\n");
}

void	set_image_pixel(t_scene *scene, int x, int y, int color)
{
	int	pixel;

	pixel = y * (scene->size_line / 4) + x;
	scene->int_addr[pixel] = color;
}
