/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setMlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:19:02 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 11:54:03 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*****************************************************************************
**		allocate_ray: allocate the rays structs
		WHY: we need to allocate the rays structs to be able to use them
		when we will cast the rays and when we will draw the walls.
*****************************************************************************/
bool	allocate_ray(t_stock *stock)
{
	int	number_of_rays;
	int	i;
	
	i = 0;
	number_of_rays = (WIDTH);
	stock->rays = (t_ray **) malloc(sizeof(t_ray *) * (number_of_rays + 1));
	if (!stock->rays)
		return (false);
	stock->rays[number_of_rays] = NULL;
	while (i < number_of_rays)
	{
		stock->rays[i] = (t_ray *) malloc(sizeof(t_ray));
		if (!stock->rays[i])
			return (false);
		ft_memset(stock->rays[i], 0, sizeof(t_ray));
		i++;
	}
	return (true);
}

/* **************************************************************************
*	This function is used to set the mlx and the window and the image		*
*	also it will allocate the rays structs									*
*****************************************************************************/
bool	set_mlx(t_stock *stock)
{
	stock->img = malloc(sizeof(t_img));
	if (!stock->img)
		return (false);
	stock->mlx_ptr = mlx_init();
	if (!stock->mlx_ptr)
		return (false);
	stock->win_ptr = mlx_new_window(stock->mlx_ptr, WIDTH,HIGTH, "Cube3D");
	if (!stock->win_ptr)
		return (false);
	stock->img->img = mlx_new_image(stock->mlx_ptr, WIDTH, HIGTH);
	if (!stock->img->img)
		return (false);
	stock->img->addr = mlx_get_data_addr(stock->img->img, 
		&stock->img->bits_per_pixel, &stock->img->line_length, 
		&stock->img->endian);
	if (!stock->img->addr)
		return (false);
	if (!allocate_ray(stock))
		return (false);
	return (true);
}