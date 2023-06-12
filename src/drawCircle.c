/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawCircle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:11:58 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 22:12:10 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void draw_circle(t_stock *stock, int x_x, int y_y, int wall, int color)
{
	int x;
	int y;

	x = 0;
	while (x < wall)
	{
		y = 0;
		while (y < wall)
		{
			if (sqrt((pow(((wall / 2) - x), 2)) 
				+ (pow(((wall / 2) - y), 2))) < wall / 2)
				my_mlx_pixel_put(stock->img, x + x_x, y + y_y, color);
			y++;
		}
		x++;
	}
}