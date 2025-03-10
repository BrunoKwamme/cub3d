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

typedef struct s_map
{
	int		**map_layout;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor[4];
	int		ceiling[4];
}				t_map;

enum Layout
{
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
int argument_val(char **argv);

//map
int	map_allocation(t_map **map, char *map_info);


//utils
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
#endif

