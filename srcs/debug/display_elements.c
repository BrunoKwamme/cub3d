#include "cub3D.h"

void	printing_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("arr element is: %s\n",arr[i]);
		i++;
	}

}

void	display_map_visual(int **arr, int reading_limit)
{
	int	i_arr;
	int i;

	i_arr = 0;
	while (arr[i_arr] != NULL)
	{
		i = 0;
		while (arr[i_arr][i] != reading_limit)
		{
			if (arr[i_arr][i] == 1)
				printf("\033[31m");
			if (arr[i_arr][i] >= NORTH && arr[i_arr][i] <= WEST)
				printf("\033[0;32m");
			if(arr[i_arr][i] < 10 && arr[i_arr][i] > -1)
				printf("%d   ", arr[i_arr][i]);
			else
				printf("%d  ", arr[i_arr][i]);
			i++;
			printf("\033[0m");
		}
		printf("\n");
		i_arr++;
	}

}

void	printing_coordinates(t_flood *vectors)
{
	// int i;

	// i = 0;
	while (vectors != NULL)
	{
		// printf("iter nbr: %d | x : %d and y: %d\n", i, vectors->vector[1], vectors->vector[0]);
		vectors = vectors->next;
	}

}

void	printing_nbr_mult_arr(int **arr, int reading_limit)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("PRINTING VECTOR >> %d\n------------------------------\n", i);
		printing_nbr_arr(arr[i], reading_limit);
		i++;
		printf("------------------------------\n");
	}

}

void	printing_nbr_arr(int *arr, int reading_limit)
{
	int	i;

	i = 0;
	while (arr[i] != reading_limit)
	{
		printf("arr element is: %d\n",arr[i]);
		i++;
	}

}

void	print_ray(t_ray *ray)
{
	printf("INITIATING PRINT RAYCAST\n");
	printf("Camera_x  : %lf\ndeltadistX : %lf\ndeltadistY : %lf\ndir_X : %lf\ndir_Y : %lf\nDraw_end : %d\nDraw_start : %d\nLineHeight : %d\nMap_X : %d\nMap_Y : %d\nSide : %d\nSideDist_X : %lf\nSideDist_Y : %lf\nStep_X : %d\nStep_Y : %d\nWall_DIST : %lf\nWall_X : %lf\n",
		ray->camera_x,
		ray->deltadist_x,
		ray->deltadist_y,
		ray->dir_x,
		ray->dir_y,
		ray->draw_end,
		ray->draw_start,
		ray->line_height,
		ray->map_x,
		ray->map_y,
		ray->side,
		ray->sidedist_x,
		ray->sidedist_y,
		ray->step_x,
		ray->step_y,
		ray->wall_dist,
		ray->wall_x);
}
