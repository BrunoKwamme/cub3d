/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:26:23 by gabrfern          #+#    #+#             */
/*   Updated: 2025/05/05 03:41:24 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	init_raycast(ray);
	printf("1\n");
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	printf("2\n");
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	printf("3\n");
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	printf("4\n");
	ray->map_x = (int)player->pos_x;
	printf("5\n");
	ray->map_y = (int)player->pos_y;
	printf("6\n");
	ray->deltadist_x = fabs(1 / ray->dir_x);
	printf("7\n");
	ray->deltadist_y = fabs(1 / ray->dir_y);

}

static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

static void	perform_dda(t_instance *inst, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > inst->map.vertical_size - 0.25
			|| ray->map_x > inst->map.horizontal_size - 1.25)
			break ;
		else if (inst->map.map_layout[ray->map_y][ray->map_x] > GROUND)
			hit = 1;
	}
}

static void	calculate_line_height(t_ray *ray, t_instance *inst, t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(inst->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + inst->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + inst->win_height / 2;
	if (ray->draw_end >= inst->win_height)
		ray->draw_end = inst->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int		raycast_apply(t_player *player, t_instance *inst)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = inst->ray;
	printf("X is -> %d and win_width -> %d\n", x, inst->win_width);
	while (x < inst->win_width)
	{
		printf("X is -> %d and win_width -> %d\n", x, inst->win_width);
		init_raycasting_info(x, &ray, player);
		// printf("INIT RAYCAST ✅\n");
		set_dda(&ray, player);
		// printf("SET DDA ✅\n");
		perform_dda(inst, &ray);
		// printf("PERFORM DDA ✅\n");
		calculate_line_height(&ray, inst, player);
		// printf("PERFORM CALCULATE LINE HEIGHT ✅\n");
		update_texture_pixels(inst, &inst->texture, &ray, x);
		// printf("UPDATE TEXTURE PIXELS ✅\n");
		// printf("*****************PRINT RAY IS*****************\n");
		// print_ray(&ray);
		// printf("********************************************\n");
		x++;
	}
	printf("FINISHED RAYCAST APPLY\n");
	return (1);
}
