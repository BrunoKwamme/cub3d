/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabrfern <gabrfern@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:07:29 by gabrfern          #+#    #+#             */
/*   Updated: 2025/04/30 00:57:44 by gabrfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/includes/libft.h"
# include "../minilibx/mlx.h"

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
	int		color;
	char	*relative_path;
	int		img_width;
	int		img_height;
}				t_data;

#ifndef LIMIT_INT_STD
#define LIMIT_INT_STD -100
# endif

#define RESET   "\033[0m";
#define RED     "\033[31m";

typedef struct s_map
{
	int		**map_layout;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		person_pos[2];
	int		floor[4];
	int		ceiling[4];
}				t_map;

typedef struct s_flood
{
	int			vector[2];
	struct 	s_flood *head;
	struct 	s_flood *next;
}		t_flood;

enum STAGING
{
	NOT_STAGING = 0,
	STAGING = 10,
};

enum Direction
{
	MOVE_LEFT = 10,
	MOVE_UP,
	MOVE_RIGHT,
	MOVE_DOWN,
};

enum Layout
{
	GROUND_STG = 10,
	WALL_STG = 11,
	EMPTY = -1,
	GROUND = 0,
	WALL = 1,
	NORTH = 2,
	SOUTH = 3,
	EAST = 4,
	WEST = 5
};

t_map	*read_document(char *argv);
int		is_map_filled (t_map **map, int flag);
int		populate_textures(t_map **map, char *map_input);

//validation
void	validation_error(int fd, t_map **map);
int 	argument_val(char **argv);

//map
int		map_allocation(t_map **map, char *map_info);
void	realloc_line(int *old_line, int **new_line);
void 	realloc_and_fill(t_map **map, int *new_lines);
int		int_arr_len(int *line, int delimiter);
int		get_size_map(int **element);
void	turn_map_in_sqr(t_map **map);

//flood fill algorithms
int		flood_fill(t_map *map);
int		verify_around(int **layout, int *vector, int max_vector, t_flood **new_vec);
int 	verify_vector(int **layout, int y, int x, t_flood **new_vec);
int 	is_new_vector(t_flood *new_vec, int y, int x);
int		do_flood_fill(int *first_pos, int **map_layout, int max_sz);
t_flood	*create_flood_vector(int *vector, t_flood *head);
void	new_node_flood(t_flood **new_vec, int *vector);
void 	free_flood_vector(t_flood **erase);

//utils
int		*get_position_vector(t_map *map, int is_staging);
int		map_max_hsize(int **arr);
void	free_int_arr(int **arr);
void	free_str(char **str);
void	free_str_arr(char **arr);
void	free_map(t_map **map);
void	put_error(char	*error_msg);
void	malloc_map(t_map **map);
int		line_empty(char *map_info);

//debug functions to exclude
void	printing_arr(char **arr);
void	printing_nbr_arr(int *arr, int reading_limit);
void	printing_nbr_mult_arr(int **arr, int reading_limit);
void	display_map_visual(int **arr, int reading_limit);
void	printing_coordinates(t_flood *vectors);

//graphic displays of the map
void	old_start_mlx (t_map **map);
void	convert_arr_in_map(t_map **map, t_data *img);
int		my_mlx_close_window(int keycode, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_start(t_map **map, t_data *img);
#endif

