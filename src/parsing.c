/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:19:26 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 20:23:10 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

char	*read_the_map(char *path)
{
	char		*buffer;
	ssize_t		r;
	int			fd;
	char		*save;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print("Error\nFailed to open the map.\n", 2), NULL);
	save = ft_strdup("");
	if (!save)
		return (close(fd), print(ERROR_MALLOC, 2), NULL);
	buffer = malloc(1 + 1 * sizeof(char));
	if (!buffer)
		return (close(fd), print(ERROR_MALLOC, 2), NULL);
	r = 1;
	while (r != 0)
	{
		r = read(fd, buffer, 1);
		if (r < 0)
			return (print("Error\nread () function Failed.\n", 2), NULL);
		buffer[r] = '\0';
		save = ft_strjoin_pro(save, buffer, 1, 0);
	}
	return (close(fd), free(buffer), save);
}

bool	map_checker(char **tab, t_stock *stock)
{
	char	**new_tab;
	int		y_len;
	int		x_len;
	int		max_len;

	y_len = 6;
	x_len = 0;
	max_len = 0;
	if (!tab[6])
		return (print("Error\nThe map is empty.\n", 2), false);
	while (tab[y_len])
	{
		x_len = 0;
		while (tab[y_len][x_len])
			x_len++;
		if (x_len > max_len)
			max_len = x_len;
		y_len++;
	}
	y_len = y_len - 6;
	new_tab = realloc_map(tab, y_len, max_len);
	if (!new_tab || !check_close(new_tab))
		return (false);
	return (stock->ex_map = new_tab, true);
}

bool	texture_checker(t_tools *pars, t_stock *stock)
{
	char	**line;

	while (pars->map[pars->i] && pars->i < 6)
	{
		line = ft_split(pars->map[pars->i], ' ');
		pars->len = ft_strlen(line[0]);
		if (pars->len == 1)
		{
			if (!ceiling_and_floor(line, pars, stock))
				return (ft_free(line), false);
		}
		else if (pars->len == 2)
		{
			if (!handle_texture(line, pars, stock))
				return (ft_free(line), false);
		}
		else
			return (ft_free(line), print(ERROR_TEXTURE_COLORS, 2), false);
		pars->i++;
		ft_free(line);
	}
	if (pars->no == 1 && pars->so == 1 && pars->we == 1
		&& pars->ea == 1 && pars->c == 1 && pars->f == 1)
		return (true);
	return (print(ERROR_TEXTURE_COLORS, 2), false);
}

bool	map_new_lines(char *path)
{
	char	**map;
	int		index;
	int		len;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print("Error\nFailed to open the map.\n", 2), false);
	len = get_lenght(path);
	if (len == -1)
		return (false);
	map = malloc((len + 1) * sizeof(char *));
	if (!map)
		return (print(ERROR_MALLOC, 2), false);
	map[len] = NULL;
	index = 0;
	while (index < len)
		map[index++] = get_next_line(fd);
	return (close(fd), check_new_lines(map));
}

bool	parsing(char *path, t_stock *stock)
{
	t_tools	pars;

	ft_memset(&pars, 0, sizeof (pars));
	if (check_path(path) == false)
		return (false);
	pars.str = read_the_map(path);
	if (!pars.str)
		return (false);
	pars.map = ft_split(pars.str, '\n');
	if (!pars.map)
		return (print(ERROR_MALLOC, 2), free(pars.str), false);
	free(pars.str);
	if (!texture_checker(&pars, stock))
		return (ft_free(pars.map), false);
	if (!map_new_lines(path))
		return (ft_free(pars.map), false);
	if (!map_checker(pars.map, stock))
		return (ft_free(pars.map), false);
	if (check_for_valid_keys(stock->ex_map) == 1)
		return (false);
	return (true);
}
