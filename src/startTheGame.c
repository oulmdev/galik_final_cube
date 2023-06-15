/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startTheGame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:45:34 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/15 17:01:35 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

int	exit_the_game(int key, t_stock *stock)
{
	(void)key;
	(void)stock;
	exit(0);
}

int	mouse_press(int x, int y, t_stock *stock)
{
	if (x < (WIDTH / 3))
		stock->player->turn_direction = -1;
	else if (x > (WIDTH / 3) * 2)
		stock->player->turn_direction = 1;
	else
		stock->player->turn_direction = 0;
	stock->player->rotate_speed = 1;
	(void)stock;
	return (0);
}

bool	start_the_game(t_stock *stock)
{
	if (!set_mlx(stock))
		return (false);
	if (!set_player(stock))
		return (false);
	if (!set_textures(stock))
		return (false);
	mlx_hook(stock->win_ptr, 2, 0, key_press, stock);
	mlx_hook(stock->win_ptr, 3, 0, key_release, stock);
	mlx_hook(stock->win_ptr, 17, 0, exit_the_game, stock);
	mlx_hook(stock->win_ptr, 6, 0, mouse_press, stock);
	mlx_loop_hook(stock->mlx_ptr, update, stock);
	
	// mlx_mouse_hook(stock->win_ptr, mouse_press, stock);
	mlx_loop(stock->mlx_ptr);
	return (true);
}
