/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapNewLines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:58:42 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/16 21:41:50 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

bool	count_new_lines(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i])
	{
		j = 0;
		while (i != 0 && map[i][j] == ' ')
			j++;
		if (map[i][j] == '\n')
			return (ft_free(map),
				print("Error\nThe map is separated by new lines.\n", 2), false);
		i++;
	}
	return (ft_free(map), true);
}

bool	check_new_lines(char **map)
{
	int		alpha;
	int		i;
	int		j;

	i = 0;
	j = 0;
	alpha = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] && map[i][j] != '\n' && map[i][j] != ' ')
			{
				alpha++;
				break ;
			}
			j++;
		}
		if (alpha == 7)
			break ;
		i++;
	}
	return (count_new_lines(map, i));
}

int	get_lenght(char *path)
{
	char	*str;
	int		fd;
	int		len;

	len = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print("Error\nFailed to open the map.\n", 2), -1);
	str = get_next_line(fd);
	while (str)
	{
		len++;
		free(str);
		str = get_next_line(fd);
	}
	return (close(fd), len);
}
