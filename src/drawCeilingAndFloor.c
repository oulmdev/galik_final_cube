/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawCeilingAndFloor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:16:08 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 12:09:10 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/******************************************************************************
**		draw_floor_and_ceiling: draw the floor and the ceiling.
**		HOW IT WORKS:
**		1)	We draw the ceiling by drawing a line of pixels from the top
**			of the screen to the middle of the screen.
**		2)	We draw the floor by drawing a line of pixels from the middle
**			of the screen to the bottom of the screen.
******************************************************************************/
void	draw_floor_and_ceiling(t_stock *stock)
{
	int	i;
	int	j;

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
