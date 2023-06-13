/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:34:46 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 11:35:20 by moulmoud         ###   ########.fr       */
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
	mlx_put_image_to_window(stock->mlx_ptr, stock->win_ptr,
		stock->img->img, 0, 0);
	return (0);
}
