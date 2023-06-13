/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMiniMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:02:16 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 18:11:45 by moulmoud         ###   ########.fr       */
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

	y = (WIDTH / 10);
	while (y < (WIDTH / 4))
	{
		x = (WIDTH / 10);
		while (x < (WIDTH / 4))
		{
			if (sqrt(pow((x - ((WIDTH /4) - (WIDTH / 8))), 2) + pow((y - ((WIDTH /4) - (WIDTH / 8))), 2)) <  20)
			{
				my_mlx_pixel_put(stock->img, x, y, RED);
			}
			x++;
		}
		y++;
	}
}

void	draw_mini_map(t_stock *stock)
{
	// draw_background(stock);
	int	y;
	int	x;
	int	max_y;
	int	max_x;
	
	max_y = stock->player->player_pos_y + ((WIDTH / 8));
	if (max_y > HIGTH)
		max_y = HIGTH;
	max_x = stock->player->player_pos_x + ((WIDTH / 8));
	if (max_x > WIDTH)
		max_x = WIDTH;
	y = stock->player->player_pos_y - (WIDTH / 8);
	if (y < 0)
		y = 0;
	int y_draw = 0;
	int x_draw;
	y = 0;
	while (y < max_y)
	{
		
		x = 0;
		x_draw = 0;
		while (x < max_x)
		{
			if (sqrt(pow((x - stock->player->player_pos_x), 2) + pow((y - stock->player->player_pos_y), 2)) <= (WIDTH / 4))// you might have a problem here corect this line like if x is greater than player_pos_x
			{
				if ((x / MINI_MAP_BOX_ZIZE) < stock->map_width && (x / MINI_MAP_BOX_ZIZE) > 0 && (y / MINI_MAP_BOX_ZIZE) < stock->map_height && (y / MINI_MAP_BOX_ZIZE) > 0)
				{
					if (stock->ex_map[(y / MINI_MAP_BOX_ZIZE)][(x / MINI_MAP_BOX_ZIZE)] == '0')
					{
						// if (x_draw < (WIDTH / 4))
							my_mlx_pixel_put(stock->img, x_draw++, y_draw, WHITE);
					}
					else if (stock->ex_map[(y / MINI_MAP_BOX_ZIZE)][(x / MINI_MAP_BOX_ZIZE)] == '1')
					{
						// if (x_draw < (WIDTH / 4))
							my_mlx_pixel_put(stock->img, x_draw++, y_draw, BLACK);
					}
					else if (stock->ex_map[(y / MINI_MAP_BOX_ZIZE)][(x / MINI_MAP_BOX_ZIZE)] == '#')
					{
						// if (x_draw < (WIDTH / 4))
							my_mlx_pixel_put(stock->img, x_draw++, y_draw, BLACK);
					}
					
				}
			}
			x++;
		}
		// if (x_draw - 1 % MINI_MAP_BOX_ZIZE == 0)
			y_draw++;
		y++;
	}
	draw_the_player(stock);
}