/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwamme <bkwamme@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:05:24 by bkwamme           #+#    #+#             */
/*   Updated: 2024/02/05 10:26:52 by bkwamme          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*put_rest(char *line, char *rest, int i)
{
	int	x;

	x = 0;
	while (line[i] != '\0')
	{
		rest[x] = line[i];
		x++;
		i++;
	}
	rest[x] = '\0';
	free(line);
	return (rest);
}

static char	*get_rest(char *line)
{
	int		i;
	int		length;
	char	*rest;

	if (!line)
		return (0);
	length = ft_strlen(line);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	rest = malloc(sizeof(char) * (length - i + 1));
	if (!rest)
		return (NULL);
	return (put_rest(line, rest, i));
}

static char	*get_line(char *line)
{
	char	*str;
	int		i;
	int		x;

	x = 0;
	i = 0;
	if (!line)
		return (0);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (x < i)
	{
		str[x] = line[x];
		x++;
	}
	str[x] = '\0';
	return (str);
}

static char	*search_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*rest;
	int			end;

	end = 1;
	buffer = malloc(sizeof(char) * (1 + BUFFER_SIZE));
	if (!buffer)
		return (NULL);
	while (end > 0 && (!rest || !ft_strchr(rest, '\n')))
	{
		end = read(fd, buffer, BUFFER_SIZE);
		if (end == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[end] = '\0';
		rest = ft_strjoin(rest, buffer);
	}
	free(buffer);
	line = get_line(rest);
	rest = get_rest(rest);
	return (line);
}

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (search_line(fd));
}
