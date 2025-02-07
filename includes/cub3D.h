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

typedef struct s_map
{
	char	**map_layout;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor;
	int		ceiling;
}				t_map;

t_map	*populate_map(char *argv);
int		is_map_filled (t_map **map, int flag);
int		populate_textures(t_map **map, char *map_input);
//validation
int argument_val(char **argv);
int	populate_textures(t_map **map, char *map_input);
int	is_element_filled (t_map **map, int flag);
void	validation_error(t_map **map);

//utils
void	free_str(char **str);
void	free_str_arr(char **arr);
void	free_map(t_map **map);
void	put_error(char	*error_msg);

#endif
