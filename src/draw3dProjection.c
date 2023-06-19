/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3dProjection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:36:59 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/19 22:20:50 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "cube3d.h"

/* ************************************************************************** 
 * this function is used to get the color of a pixel from a texture
 * the offset_x and offset_y are the coordinates of the pixel in the texture
 * texture->addr is the address of the first pixel of the texture 
 	it's a 1d array so we have to convert the 2d coordinates to 1d to access 
	the pixel we want then we cast it to an int to get the color of the pixel
	because the color is stored in an int									
*****************************************************************************/
int	get_xpm_color(t_texture *texture, int offset_x,
	int offset_y)
{
	int	color;
	if (offset_x < 0 || offset_x >= texture->width || offset_y < 0
		|| offset_y >= texture->height)
		return (0);
	color = *(int*)(texture->addr + (offset_y* texture->line_length + offset_x
		* (texture->bits_per_pixel / 8)));
	return (color);
}

/****************************************************************************
 * 							FIND TEXTURE AND OFFSET
 * this function is used to find the texture and the offset of the texture
 * we will use to draw the wall
 * we will use the texture_index to get the texture from the array of textures
 * we will use the texture_offset_x to get the offset of the texture

 * 	WHAT IS THE OFFSET: the offset is the coordinate of the pixel in the texture
 * 	if the hit was vertical we will use the y coordinate of the hit to get the 
 * 	offset of the texture and if the hit was horizontal we will use the x 
 * 	coordinate of the hit to get the offset of the texture
****************************************************************************/
void	find_texture_and_offset(t_stock *stock, int *texture_index,
	int *texture_offset_x, int i)
{
	int tmp;
	if (stock->rays[i]->was_hit_horizontal
			&& stock->rays[i]->is_ray_facing_down)
		*texture_index = 0;
	else if (stock->rays[i]->was_hit_horizontal
			&& stock->rays[i]->is_ray_facing_up)
		*texture_index = 1;
	else if (stock->rays[i]->was_hit_vertical 
			&& stock->rays[i]->is_ray_facing_left)
		*texture_index = 2;
	else if (stock->rays[i]->was_hit_vertical
			&& stock->rays[i]->is_ray_facing_right)
		*texture_index = 3;
	if (stock->rays[i]->was_hit_vertical)
	{
		*texture_offset_x = (int)stock->rays[i]->vertical_wall_hit_y
			% MINI_MAP_BOX_ZIZE;
		tmp = *texture_offset_x;
		*texture_offset_x = (tmp * stock->texture[*texture_index]->width) / MINI_MAP_BOX_ZIZE;
	}
	else if (stock->rays[i]->was_hit_horizontal)
	{
		*texture_offset_x = (int)stock->rays[i]->horizontal_wall_hit_x
			% MINI_MAP_BOX_ZIZE;
		tmp = *texture_offset_x;
		*texture_offset_x = (tmp * stock->texture[*texture_index]->width) / MINI_MAP_BOX_ZIZE;
	}
}

/*****************************************************************************

*****************************************************************************/
void	draw_3d_projection(t_stock *stock)
{
	int		texture_offset_x;
	int		texture_offset_y;
	int		color;
	int		texture_index;
	int		i;
	int		j;

	texture_index = 0;
	texture_offset_x = 0;
	texture_offset_y = 0;
	i = 0;
	int tmp;
	while  (i < WIDTH)
	{
		find_texture_and_offset(stock, &texture_index, &texture_offset_x, i);
		if (stock->rays[i]->projection_distance >= HIGTH)
			j = 0;
		else
			j = (HIGTH / 2) - (stock->rays[i]->projection_distance / 2);
		while (j < (HIGTH / 2) + (stock->rays[i]->projection_distance / 2) && j < HIGTH)
		{
			texture_offset_y = (stock->texture[texture_index]->height * (j + (stock->rays[i]->projection_distance / 2) 
				- (HIGTH / 2))) / stock->rays[i]->projection_distance;
			if (texture_offset_y < 0)
				texture_offset_y *= 0;
			color = get_xpm_color(stock->texture[texture_index],
				texture_offset_x, texture_offset_y);
			my_mlx_pixel_put(stock->img, i, j, color);
			j++;
		}
		i++;
	}
}

