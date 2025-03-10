#include "cub3D.h"

static int	find_index(char *inner, char *str)
{
	char	*pos;
	int		i;

	i = 0;
	pos = ft_strnstr(str, inner, ft_strlen(str));
	if (pos != NULL)
	{
		i = (pos - str + ft_strlen(inner));
		while (str[i] != '\0' && ft_isspace(str[i]))
			i++;
		return (i);
	}

	return (-1);
}

static char *processe_str(char *dir, char *map_input)
{
	char *processed_str;
	int index_str;

	processed_str = NULL;
	index_str = find_index(dir, map_input);
	if (index_str == -1)
		return NULL;
	processed_str = ft_substr(map_input, index_str, ft_strlen(map_input));
	return (processed_str);
}

static void	processe_numbers(char *dir, int (*element)[], char *map_input)
{
	char	*processed_str;
	char	**splited_nbs;
	int		i;

	i = 0;
	processed_str = processe_str(dir, map_input);
	splited_nbs = ft_split(processed_str, ',');
	while (splited_nbs[i] != NULL)
	{
		(*element)[i] = ft_atoi(splited_nbs[i]);
		i++;
	}
	(*element)[i] = LIMIT_INT_STD;
	free_str(&processed_str);
	free_str_arr(splited_nbs);
}

int	populate_textures(t_map **map, char *map_input)
{
	char *temp_str;

	temp_str = ft_strtrim(map_input, "\n\t\v\f\r\b ");
	if (!(*map)->no_texture && ft_strncmp(temp_str, "NO", 2) == 0)
		(*map)->no_texture = processe_str("NO", temp_str);
	else if (!(*map)->so_texture  && ft_strncmp(temp_str, "SO", 2) == 0)
		(*map)->so_texture = processe_str("SO", temp_str);
	else if (!(*map)->we_texture && ft_strncmp(temp_str, "WE", 2) == 0)
		(*map)->we_texture = processe_str("WE", temp_str);
	else if (!(*map)->ea_texture && ft_strncmp(temp_str, "EA", 2) == 0)
		(*map)->ea_texture = processe_str("EA", temp_str);
	else if ((*map)->floor[0] == -1 && ft_strncmp(temp_str, "F", 1) == 0)
		processe_numbers("F", &((*map)->floor), temp_str);
	else if ((*map)->ceiling[0] == -1 && ft_strncmp(temp_str, "C", 1) == 0)
		processe_numbers("C", &((*map)->ceiling), temp_str);
	else
	{
		free_str(&temp_str);
		return (1);
	}
	free_str(&temp_str);
	return (0);
}
