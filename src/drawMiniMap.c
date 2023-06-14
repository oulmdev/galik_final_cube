/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMiniMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:02:16 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/14 14:16:02 by moulmoud         ###   ########.fr       */
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
		my_mlx_pixel_put(stock->img, 0, i, BLACK);
		my_mlx_pixel_put(stock->img, 1, i, BLACK);
		my_mlx_pixel_put(stock->img, j - 1, i, BLACK);
		i++;
	}
	j = 0;
	while (j < (WIDTH / 4))
	{
		my_mlx_pixel_put(stock->img, j, i, BLACK);
		j++;
	}
	
}

void	draw_the_player(t_stock *stock)
{
	int	y;
	int	x;
	
	y = (MINI_MAP_BOX_ZIZE * 2);
	while (y <=(MINI_MAP_BOX_ZIZE * 4))
	{
		x = (MINI_MAP_BOX_ZIZE * 2);
		while (x <= (MINI_MAP_BOX_ZIZE * 3))
		{
			if (sqrt(pow((x - ((MINI_MAP_BOX_ZIZE * 2) + (MINI_MAP_BOX_ZIZE / 2))), 2) + pow((y - ((MINI_MAP_BOX_ZIZE * 2) + (MINI_MAP_BOX_ZIZE / 2))), 2)) < 10)
				my_mlx_pixel_put(stock->img, x, y, RED);
			x++;
		}
		y++;
	}
}

void	draw_profile_mini_map(t_stock *stock)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;
	int area;
	
	area = ((MINI_MAP_BOX_ZIZE / 2) + (2 * MINI_MAP_BOX_ZIZE));
	max_x = stock->player->player_pos_x + area; // the max_x to search for the player.
	if (max_x > (stock->map_width * MINI_MAP_BOX_ZIZE))
		max_x = (stock->map_width * MINI_MAP_BOX_ZIZE);
	max_y = stock->player->player_pos_y + area; // the max_y to search for the player.
	if (max_y > (stock->map_height * MINI_MAP_BOX_ZIZE))
		max_y = (stock->map_height * MINI_MAP_BOX_ZIZE);
	
	y = stock->player->player_pos_y - area;
	if (y < 0)
		y = 0;
		
	int i = 0;
	int j = 0;
	while (y < max_y)
	{
		x = stock->player->player_pos_x - area;
		if (x < 0)
			x = 0;
		j = 0;
		while (x < max_x)
		{
			if (stock->ex_map[y / MINI_MAP_BOX_ZIZE][x / MINI_MAP_BOX_ZIZE] == '1')
				my_mlx_pixel_put(stock->img, j, i, GREEN);
			x++;
			j++;
		}
		i++;
		y++;
	}
	
	
}

void	draw_mini_map(t_stock *stock)
{
	draw_background(stock);
	draw_profile_mini_map(stock);
	draw_the_player(stock);
}