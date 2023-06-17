/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:34:46 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/17 01:12:02 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/* ***************************************************************************
**		draw_every_thing: draw the floor, ceiling then call the ray_casting
		function
******************************************************************************/
void	draw_every_thing(t_stock *stock)
{
	draw_floor_and_ceiling(stock);
	ray_casting(stock);
	draw_mini_map(stock);
}

void	draw_square(t_stock *stock, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(stock->img, x * 10 + i, y * 10 + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player_mini_map(t_stock *stock)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(stock->img, stock->player->player_pos_x / MINI_MAP_BOX_ZIZE * 10 + i, stock->player->player_pos_y / MINI_MAP_BOX_ZIZE * 10 + j, 0xFF0000);
			j++;
		}
		i++;
	}
}


void	draw_the_map(t_stock *stock)
{
	int	y;
	int	x;
	int	y_draw;
	
	// y = stock->player->player_pos_y / MINI_MAP_BOX_ZIZE - 5;
	// if (y < 0)
		y = 0;
	y_draw = 0;
	while (stock->ex_map[y])
	{
		// x = stock->player->player_pos_x / MINI_MAP_BOX_ZIZE - 20;
		// if (x < 0)
		x = 0;
		while(stock->ex_map[y][x])
		{
			if (stock->ex_map[y][x] == '0')
				draw_square(stock, x, y_draw, 0x000000);
			if (stock->ex_map[y][x] == '1')
				draw_square(stock, x, y_draw, 0x00FF00);
			x++;
		}
		y++;
		y_draw++;
	}
	draw_player_mini_map(stock);
}

/* ***************************************************************************
**		update: update the window

		HOW: clear the window, destroy the image, create a new image, get the
		address of the image, check if the player is turning or walking and
		move him if he is, draw everything and put the image to the window.
******************************************************************************/
int	update(t_stock *stock)
{
	mlx_clear_window(stock->mlx_ptr, stock->win_ptr);
	mlx_destroy_image(stock->mlx_ptr, stock->img->img);
	stock->img->img = mlx_new_image(stock->mlx_ptr, WIDTH, HIGTH);
	stock->img->addr = mlx_get_data_addr(stock->img->img,
			&stock->img->bits_per_pixel,
			&stock->img->line_length, &stock->img->endian);
	if (stock->player->turn_direction != 0)
		rotate_the_player(stock);
	if (stock->player->walk_direction != 0 || stock->player->sideways != 0)
		move_the_player(stock);
	draw_every_thing(stock);
	if (stock->draw_the_map == 1)
		draw_the_map(stock);
	mlx_put_image_to_window(stock->mlx_ptr, stock->win_ptr,
		stock->img->img, 0, 0);
	return (0);
}
