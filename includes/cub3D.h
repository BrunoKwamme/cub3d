/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 23:07:29 by gabrfern          #+#    #+#             */
/*   Updated: 2025/06/12 20:02:24 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "libft/includes/libft.h"
# include "../minilibx/mlx.h"

#define RESET   "\033[0m";
#define RED     "\033[31m";
#define GREEN	"\033[0;32m"

#ifndef LIMIT_INT_STD
#define LIMIT_INT_STD -100
# endif

#ifndef WIN_HEIGHT
#define WIN_HEIGHT 960
# endif

#ifndef WIN_WIDTH
#define WIN_WIDTH 960
# endif


#ifndef TEXTURE_SIZE
#define TEXTURE_SIZE 32
# endif


#ifndef MOVE_SPEED
#define MOVE_SPEED 0.06
# endif


#ifndef ROT_SPEED
#define ROT_SPEED 0.02
# endif


typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_texture
{
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	int				floor[4];
	int				ceiling[4];
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}				t_texture;

typedef struct s_map
{
	int		**map_layout;
	int		person_pos[2];
	int		horizontal_size;
	int		vertical_size;
}				t_map;

typedef struct s_flood
{
	int			vector[2];
	struct 	s_flood *head;
	struct 	s_flood *next;
}		t_flood;

typedef struct	s_scene
{
	void	*img;
	int		*int_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}				t_scene;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;


typedef struct	s_instance
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			**texts_buffer;
	int			**screen_pixels;
	t_map		map;
	t_scene		scene;
	t_texture	texture;
	t_player	player;
	t_ray		ray;


}				t_instance;


enum STAGING
{
	NOT_STAGING = 0,
	STAGING = 10,
};

enum MapLayout
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

enum TextureDirection
{
	NO_TEXTURE = 0,
	EA_TEXTURE,
	SO_TEXTURE,
	WE_TEXTURE
};

int		read_document(char *argv, t_instance *inst);
int		is_map_filled (t_texture *texture, int flag);
int		populate_textures(t_instance *inst, char *map_input, int fd);

//validation
int		validation_error(t_instance *inst, int cubfd);
int 	argument_val(char **argv);
void	validate_player_dir(t_instance *inst, int fd);

//map
int		map_allocation(t_map *map, char *map_info);
void	realloc_line(int *old_line, int **new_line);
void 	realloc_and_fill(t_map *map, int *new_lines);
int		int_arr_len(int *line, int delimiter);
int		get_size_map(int **element);
void	turn_map_in_sqr(t_map *map, int fd);

//flood fill algorithms
int		flood_fill(t_map *map);
int		verify_around(int **layout, int *vector, int max_vector, t_flood **new_vec);
int 	verify_vector(int **layout, int y, int x, t_flood **new_vec);
int 	is_new_vector(t_flood *new_vec, int y, int x);
int		do_flood_fill(int *first_pos, int **map_layout, int max_sz);
t_flood	*create_flood_vector(int *vector, t_flood *head);
void	new_node_flood(t_flood **new_vec, int *vector);

//utils
int				*get_position_vector(t_map *map, int is_staging);
int				map_max_hsize(int **arr);
int				put_error(char	*error_msg, t_instance **inst, int cubfd);
int				line_empty(char *map_info);
unsigned long	rgb_to_hex(int *rgb_tab);

//free utils
void	free_int_arr(int **arr);
void	free_str(char **str);
void	free_str_arr(char **arr);
void 	free_flood_vector(t_flood **erase);
void	free_map(t_map *map);
void	free_textures(t_texture *textures);
void	free_instance(t_instance *inst);
void	clean_exit(t_instance *inst, int exit_code);
//malloc utils
void	init_scene(t_scene *scene);
int		quit_application(t_instance *inst);
void	set_player_prop(t_instance *inst);
void	set_instance(t_instance *instance);

//debug functions to exclude
void	print_ray(t_ray *ray);
void	printing_arr(char **arr);
void	printing_nbr_arr(int *arr, int reading_limit);
void	printing_nbr_mult_arr(int **arr, int reading_limit);
void	display_map_visual(int **arr, int reading_limit);
void	printing_coordinates(t_flood *vectors);

//GRAPHIC SECTION
//TEXTURES
void	load_texture_buffer(t_instance *inst);
void	update_texture_pixels(t_instance *inst, t_texture *tex, t_ray *ray, int x);
int		*cub_xpm_to_img(t_instance *inst, char *path);
void	gen_img_info(t_scene *img, t_instance *inst, char *path);
void	set_new_img(t_instance *inst, t_scene *scene, int width, int height);
void	set_image_pixel(t_scene *scene, int x, int y, int color);

//RENDER EXECUTION
void	set_render_info(t_instance *instance);
int		render_images(t_instance *inst);
void	set_screen_pixels(t_instance *inst);
void	listen_for_input(t_instance *inst);
int		hook_render(t_instance *inst);

//RAYCAST FUNCTIONS
void	init_raycast(t_ray *ray);
void	render_raycast(t_instance *inst);
int		raycast_apply(t_player *player, t_instance *inst);

//MOVEMENT ARROUND THE MAP
int		move_player(t_instance *inst);
int		validate_move(t_instance *inst, double new_x, double new_y);
int		rotate_player(t_instance *inst, double rotdir);

//graphic displays of the map
// void	convert_arr_in_map(t_map **map, t_mlx_instance *mlx, t_scene *scene);
// int		my_mlx_close_window(int keycode, t_mlx_instance *mlx);
// t_scene	generate_image_info(t_mlx_instance *mlx, int img_width, int img_height, char *relative_path);
// void	generate_first_image(t_mlx_instance *mlx, t_map **map);
// void	my_mlx_create_main(t_map **map);
#endif

