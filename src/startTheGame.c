/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startTheGame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:45:34 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/17 04:16:15 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

int	exit_the_game(int key, t_stock *stock)
{
	(void)key;
	(void)stock;
	exit(0);
}

int	mouse_move(int x, int y, t_stock *stock)
{
	if (stock->mouse_rotation == 0)
		return (0);
	if (x < (WIDTH / 3) && y > (WIDTH / 4))
		stock->player->turn_direction = -1;
	else if (x > (WIDTH / 3) * 2 && y > (WIDTH / 4))
		stock->player->turn_direction = 1;
	else
		stock->player->turn_direction = 0;
	stock->player->rotate_speed = 3;
	return (0);
}

int mouse_press(int button, int x, int y, t_stock *stock)
{
	if (button == 1 && x < (WIDTH / 4) && y < (WIDTH / 4))
	{
		stock->draw_the_map = 1;
	}
	else
		stock->draw_the_map = 0;
	if (button == 1 && x > (WIDTH / 4) && x < ((WIDTH / 4) + 68) && y < 64 && stock->mouse_rotation)
	{
		stock->mouse_rotation = 0;
	}
	else if (button == 1 && x > (WIDTH / 4) && x < ((WIDTH / 4) + 68) && y < 64 && !stock->mouse_rotation)
	{
		stock->mouse_rotation = 1;
	}
	
	if (button == 1 && x > (WIDTH / 4) && x < ((WIDTH / 4) + 68) && y > 64 && y < 128 && stock->player->walk_speed < 15)
	{
		stock->player->walk_speed += 1;
	}
	else if (button == 1 && x > (WIDTH / 4) && x < ((WIDTH / 4) + 68) && y > 64 && y < 128 && stock->player->walk_speed >= 15)
	{
		stock->player->walk_speed = 5;
	}
	
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
	mlx_hook(stock->win_ptr, 6, 0, mouse_move, stock);
	
	
	mlx_hook(stock->win_ptr, 4, 0, mouse_press, stock);
	mlx_loop_hook(stock->mlx_ptr, update, stock);
	mlx_loop(stock->mlx_ptr);
	return (true);
}
