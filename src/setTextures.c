/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setTextures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:16:14 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 23:42:52 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

bool	set_north_texture(t_stock *stock)
{
	stock->texture[0] = malloc(sizeof(t_texture));
	if (!stock->texture[0])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[0]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->no, &stock->texture[0]->width, 
		&stock->texture[0]->height);
	if (!stock->texture[0]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[0]->addr = mlx_get_data_addr(stock->texture[0]->img, 
		&stock->texture[0]->bits_per_pixel, &stock->texture[0]->line_length, 
		&stock->texture[0]->endian);
	if (!stock->texture[0]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	return (true);
}

bool	set_south_texture(t_stock *stock)
{
	stock->texture[2] = malloc(sizeof(t_texture));
	if (!stock->texture[2])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[2]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->so, &stock->texture[2]->width, 
		&stock->texture[2]->height);
	if (!stock->texture[2]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[2]->addr = mlx_get_data_addr(stock->texture[2]->img, 
		&stock->texture[2]->bits_per_pixel, &stock->texture[2]->line_length, 
		&stock->texture[2]->endian);
	if (!stock->texture[2]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	return (true);
}

bool	set_west_texture(t_stock *stock)
{
	stock->texture[1] = malloc(sizeof(t_texture));
	if (!stock->texture[1])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[1]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->we, &stock->texture[1]->width, 
		&stock->texture[1]->height);
	if (!stock->texture[1]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[1]->addr = mlx_get_data_addr(stock->texture[1]->img, 
		&stock->texture[1]->bits_per_pixel, &stock->texture[1]->line_length, 
		&stock->texture[1]->endian);
	if (!stock->texture[1]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	return (true);
}

bool	set_east_texture(t_stock *stock)
{
	stock->texture[3] = malloc(sizeof(t_texture));
	if (!stock->texture[3])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[3]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->ea, &stock->texture[3]->width, 
		&stock->texture[3]->height);
	if (!stock->texture[3]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[3]->addr = mlx_get_data_addr(stock->texture[3]->img, 
		&stock->texture[3]->bits_per_pixel, &stock->texture[3]->line_length, 
		&stock->texture[3]->endian);
	if (!stock->texture[3]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	return (true);
}

bool	set_textures(t_stock *stock)
{
	stock->texture = (t_texture **)malloc(sizeof(t_texture *) * 5);
	if (!stock->texture)
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	if (!set_north_texture(stock))
		return (false);
	if (!set_south_texture(stock))
		return (false);
	if (!set_west_texture(stock))
		return (false);
	if (!set_east_texture(stock))
		return (false);
	stock->wall = malloc(sizeof(t_wall));
	if (!stock->wall)
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->wall->x = -1;
	stock->wall->y = -1;
	stock->texture[4] = NULL;
	return (true);
}