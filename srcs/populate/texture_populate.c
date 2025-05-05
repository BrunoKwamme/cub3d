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
	printf("GETTING %s of %s\n", dir, map_input);
	index_str = find_index(dir, map_input);
	if (index_str == -1)
		return NULL;
	processed_str = ft_substr(map_input, index_str, ft_strlen(map_input));
	printf("processed string is: %s\n", processed_str);
	return (processed_str);
}

static void	processe_numbers(char *dir, int (*element)[], char *map_input)
{
	char	*processed_str;
	char	**splited_nbs;
	int		i;

	printf("IN PROCESSE NUMBERS, map input is: %s\n", map_input);
	i = 0;
	processed_str = processe_str(dir, map_input);
	splited_nbs = ft_split(processed_str, ',');
	while (splited_nbs[i] != NULL && i < 3)
	{
		(*element)[i] = ft_atoi(splited_nbs[i]);
		printf("ELEMENT POSITION %d is: %d\n", i, (*element)[i]);

		i++;
	}
	(*element)[i] = LIMIT_INT_STD;
	free_str(&processed_str);
	free_str_arr(splited_nbs);
}

int	populate_textures(t_texture *texture, char *map_input)
{
	char *temp_str;

	temp_str = ft_strtrim(map_input, "\n\t\v\f\r\b ");
	if (!texture->north_path && ft_strncmp(temp_str, "NO", 2) == 0)
		texture->north_path = processe_str("NO", temp_str);
	else if (!texture->south_path  && ft_strncmp(temp_str, "SO", 2) == 0)
		texture->south_path = processe_str("SO", temp_str);
	else if (!texture->west_path && ft_strncmp(temp_str, "WE", 2) == 0)
		texture->west_path = processe_str("WE", temp_str);
	else if (!texture->east_path && ft_strncmp(temp_str, "EA", 2) == 0)
		texture->east_path = processe_str("EA", temp_str);
	else if (texture->floor[0] == -1 && ft_strncmp(temp_str, "F", 1) == 0)
		processe_numbers("F", &(texture->floor), temp_str);
	else if (texture->ceiling[0] == -1 && ft_strncmp(temp_str, "C", 1) == 0)
		processe_numbers("C", &(texture->ceiling), temp_str);
	else
	{
		free_str(&temp_str);
		return (1);
	}
	free_str(&temp_str);
	return (0);
}
