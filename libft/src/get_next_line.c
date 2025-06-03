/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:22:25 by machouba          #+#    #+#             */
/*   Updated: 2024/05/09 12:30:28 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *str, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(str, buff);
	return (tmp);
}

char	*ft_get_next(char *str)
{
	int		i;
	int		j;
	char	*stock;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	stock = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (str[i])
		stock[j++] = str[i++];
	free(str);
	return (stock);
}

char	*ft_get_line(char	*str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *str)
{
	char	*buff;
	int		i;

	if (!str)
		str = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	i = 1;
	while (i > 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		str = ft_free(str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	buffer = ft_get_next(buffer);
	return (line);
}
