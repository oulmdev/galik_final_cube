/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3dProjection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:36:59 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 22:20:06 by moulmoud         ###   ########.fr       */
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
	color = *(int*)(texture->addr + (offset_y * texture->line_length + offset_x
		* (texture->bits_per_pixel / 8)));
	return (color);
}

void	draw_3d_projection(t_stock *stock)
{
	int		texture_offset_x;
	int		texture_offset_y;
	int		color;
	int 	texture_index;
	
	for (int i =0; i < WIDTH; i++)
	{
		if (stock->rays[i]->was_hit_horizontal && stock->rays[i]->is_ray_facing_down)
			texture_index = 0;
		else if (stock->rays[i]->was_hit_horizontal && stock->rays[i]->is_ray_facing_up)
			texture_index = 1;
		else if (stock->rays[i]->was_hit_vertical && stock->rays[i]->is_ray_facing_left)
			texture_index = 2;
		else if (stock->rays[i]->was_hit_vertical && stock->rays[i]->is_ray_facing_right)
			texture_index = 3;
		if (stock->rays[i]->was_hit_vertical)
			texture_offset_x = (int)stock->rays[i]->vertical_wall_hit_y % MINI_MAP_BOX_ZIZE; 
		else if (stock->rays[i]->was_hit_horizontal)
			texture_offset_x = (int)stock->rays[i]->horizontal_wall_hit_x % MINI_MAP_BOX_ZIZE;
		for (int j = (HIGTH / 2) - (stock->rays[i]->projection_distance / 2); j < (HIGTH / 2) + (stock->rays[i]->projection_distance / 2); j++)
		{
			texture_offset_y = (j - (stock->rays[i]->projection_distance / 2) - (HIGTH / 2)) * (stock->texture[texture_index]->height / stock->rays[i]->projection_distance);
			if (texture_offset_y < 0)
				texture_offset_y *= -1;
			if (stock->rays[i]->was_hit_vertical)
			{
				color = get_xpm_color(stock->texture[texture_index], texture_offset_x, texture_offset_y);
				my_mlx_pixel_put(stock->img, i, j, color);
				
			}
			else if (stock->rays[i]->was_hit_horizontal)
			{
				color = get_xpm_color(stock->texture[texture_index], texture_offset_x, texture_offset_y);
				my_mlx_pixel_put(stock->img, i, j, color);
			}
		}
	}
}