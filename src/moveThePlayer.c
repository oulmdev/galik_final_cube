/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveThePlayer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:10:09 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 00:18:50 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void	move_the_player(t_stock *stock)
{
	double	new_player_x;
	double	new_player_y;
	
	new_player_x = 0;
	new_player_y = 0;
	if (!stock->player->sideways)
	{	
		new_player_x = stock->player->player_pos_x + 
			cos(to_radians(stock->player->player_direction)) * (stock->player->walk_direction * stock->player->walk_speed);
		new_player_y = stock->player->player_pos_y 
			+ sin(to_radians(stock->player->player_direction)) * (stock->player->walk_direction * stock->player->walk_speed);
	}
	else if (stock->player->sideways != 0)
	{
		// new_player_direction = stock->player->player_direction + 90;
		// if (new_player_direction <= 0)
		// 	new_player_direction += 360;
		// if (new_player_direction > 360)
		// 	new_player_direction -= 360;
		new_player_x = stock->player->player_pos_x + 
			cos(to_radians(normalize_angle(stock->player->player_direction + 90))) * (stock->player->sideways * stock->player->walk_speed);
		new_player_y = stock->player->player_pos_y 
			+ sin(to_radians(normalize_angle(stock->player->player_direction + 90))) * (stock->player->sideways * stock->player->walk_speed);
	}
	if ((stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x / MINI_MAP_BOX_ZIZE] != '1' && 
		stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x / MINI_MAP_BOX_ZIZE] != '#'))
	{
		stock->player->player_pos_x = new_player_x;
		stock->player->player_pos_y = new_player_y;
	}	
}