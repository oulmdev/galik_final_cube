/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMiniMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:02:16 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 20:03:41 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

void	draw_background(t_stock *stock)
{
	int	i;
	int	j;
	
	
	i = 0;
	while (i < WIDTH / 4)
	{
		j = 0;
		while (j < WIDTH / 4)
		{
			my_mlx_pixel_put(stock->img, j, i, WHITE);
			j++;
		}
		i++;
	}
}

void	draw_the_player(t_stock *stock)
{
	int	y;
	int	x;
	
	y = (MINI_MAP_BOX_ZIZE * 2);
	while (y <=(MINI_MAP_BOX_ZIZE * 4))
	{
		x = (MINI_MAP_BOX_ZIZE * 3);
		while (x <= (MINI_MAP_BOX_ZIZE * 4))
		{
			if (sqrt(pow((x - ((MINI_MAP_BOX_ZIZE * 3) + (MINI_MAP_BOX_ZIZE / 2))), 2) + pow((y - ((MINI_MAP_BOX_ZIZE * 3) + (MINI_MAP_BOX_ZIZE / 2))), 2)) <  20)
				my_mlx_pixel_put(stock->img, x, y, RED);
			x++;
		}
		y++;
	}
}

void	draw_profile_box(t_stock *stock)
{
	
	
}

void	draw_mini_map(t_stock *stock)
{
	draw_background(stock);
	// draw_profile_box(stock);
	draw_the_player(stock);
}