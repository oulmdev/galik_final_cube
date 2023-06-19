/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:34:46 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/18 18:52:43 by moulmoud         ###   ########.fr       */
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
	int	size;
	
	size = HIGTH / stock->map_height;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(stock->img, x * size + i, y * size + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player_mini_map(t_stock *stock)
{
	int	i;
	int	j;
	int size;
	i = 0;
	size =  HIGTH / stock->map_height;
	
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(stock->img, stock->player->player_pos_x / MINI_MAP_BOX_ZIZE * size + i, stock->player->player_pos_y / MINI_MAP_BOX_ZIZE * size + j, 0xFF0000);
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
	mlx_clear_window(stock->mlx_ptr, stock->win_ptr);
	mlx_destroy_image(stock->mlx_ptr, stock->img->img);
	stock->img->img = mlx_new_image(stock->mlx_ptr, WIDTH, HIGTH);
	stock->img->addr = mlx_get_data_addr(stock->img->img,
			&stock->img->bits_per_pixel,
			&stock->img->line_length, &stock->img->endian);
	
	y = 0;
	while (stock->ex_map[y])
	{
		x = 0;
		while(stock->ex_map[y][x])
		{
			if (stock->ex_map[y][x] == '0')
				draw_square(stock, x, y, 0x000000);
			if (stock->ex_map[y][x] == '1')
				draw_square(stock, x, y, 0x00FF00);
			x++;
		}
		y++;
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
