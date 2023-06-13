/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:11:43 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 13:34:24 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

/*	EXPLAIN:
	--	We use this function to put a pixel in the image.
	--	We use the address of the image and we add the offset of the pixel.
	--	We use the color to put the pixel.
	
	--> img->addr is declared as a char*. This is because the pixel data
	in memory is stored as a sequence of bytes. Each byte can store
	a value from 0 to 255
	--> The offset of the pixel is calculated by multiplying the y cordinate
	by the line length and adding the x coordinate multiplied by the number
	of bytes per pixel.
	
	-> It's like you store the image in a one dimension array and you access
	it with the cords of the 2D array.
*/
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;
	
	if (x > WIDTH || y > HIGTH || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}