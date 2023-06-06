/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureChecker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:55:44 by moulmoud          #+#    #+#             */
/*   Updated: 2023/05/16 21:20:59 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

bool	check_valid_rgb(char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j] && tmp[i][j] == ' ')
			j++;
		while (tmp[i][j])
		{
			if (!is_digit(tmp[i][j]))
				return (ft_free(tmp), false);
			j++;
		}
		if (ft_atoi(tmp[i]) > 255)
			return (ft_free(tmp), false);
		i++;
	}
	if (i != 3)
		return (ft_free(tmp), false);
	return (true);
}

bool	fill_the_stock_colors(char *str, t_stock *stock, int flag)
{
	char	**tmp;

	tmp = NULL;
	if (flag == 0)
	{
		tmp = ft_split(str, ',');
		if (!tmp || !check_valid_rgb(tmp))
			return (false);
		stock->c[0] = ft_atoi(tmp[0]);
		stock->c[1] = ft_atoi(tmp[1]);
		stock->c[2] = ft_atoi(tmp[2]);
		ft_free(tmp);
	}
	if (flag == 1)
	{
		tmp = ft_split(str, ',');
		if (!tmp || !check_valid_rgb(tmp))
			return (false);
		stock->f[0] = ft_atoi(tmp[0]);
		stock->f[1] = ft_atoi(tmp[1]);
		stock->f[2] = ft_atoi(tmp[2]);
		ft_free(tmp);
	}
	return (true);
}

bool	fill_the_stock_textures(char **str, char *texture, t_stock *stock)
{
	if (ft_strcmp("NO", texture, 0) == 0)
	{
		stock->no = ft_strdup(str[1]);
		if (!stock->no)
			return (print(ERROR_MALLOC, 2), false);
	}
	else if (ft_strcmp("SO", texture, 0) == 0)
	{
		stock->so = ft_strdup(str[1]);
		if (!stock->so)
			return (print(ERROR_MALLOC, 2), false);
	}
	else if (ft_strcmp("WE", texture, 0) == 0)
	{
		stock->we = ft_strdup(str[1]);
		if (!stock->we)
			return (print(ERROR_MALLOC, 2), false);
	}
	else if (ft_strcmp("EA", texture, 0) == 0)
	{
		stock->ea = ft_strdup(str[1]);
		if (!stock->ea)
			return (print(ERROR_MALLOC, 2), false);
	}
	return (true);
}

bool	handle_texture(char **str, t_pars *pars, t_stock *stock)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i != 2)
		return (print(ERROR_TEXTURE_COLORS, 2), false);
	if (ft_strcmp(str[0], "NO", 0) == 0)
		return (pars->no++, fill_the_stock_textures(str, "NO", stock));
	else if (ft_strcmp(str[0], "SO", 0) == 0)
		return (pars->so++, fill_the_stock_textures(str, "SO", stock));
	else if (ft_strcmp(str[0], "WE", 0) == 0)
		return (pars->we++, fill_the_stock_textures(str, "WE", stock));
	else if (ft_strcmp(str[0], "EA", 0) == 0)
		return (pars->ea++, fill_the_stock_textures(str, "EA", stock));
	return (print(ERROR_TEXTURE_COLORS, 2), false);
}

bool	ceiling_and_floor(char **line, t_pars *pars, t_stock *stock)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	if (i != 2)
		return (print(ERROR_TEXTURE_COLORS, 2), false);
	if (ft_strcmp(line[0], "C", 0) == 0)
	{
		if (!fill_the_stock_colors(line[1], stock, 0))
			return (print(ERROR_TEXTURE_COLORS, 2), false);
		pars->c++;
	}
	else if (ft_strcmp(line[0], "F", 0) == 0)
	{
		if (!fill_the_stock_colors(line[1], stock, 1))
			return (print(ERROR_TEXTURE_COLORS, 2), false);
		pars->f++;
	}
	else
		return (print(ERROR_TEXTURE_COLORS, 2), false);
	return (true);
}
