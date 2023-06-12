/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawCeilingAndFloor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:16:08 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 22:16:11 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void draw_floor_and_ceiling(t_stock *stock)
{
	int i;
	int j;

	i = 0;
	while (i < HIGTH / 2)
	{
		j = 0;
		while (j < WIDTH)
			my_mlx_pixel_put(stock->img, j++, i, CYAN);
		i++;
	}
	while (i < HIGTH)
	{
		j = 0;
		while (j < WIDTH)
			my_mlx_pixel_put(stock->img, j++, i, BROWN);
		i++;
	}
}