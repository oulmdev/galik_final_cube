/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotateThePlayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:11:06 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 12:06:55 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

/******************************************************************************
**		rotate_the_player: rotate the player's direction.
**		HOW IT WORKS:
**		1)	We calculate the new player's direction by adding the player's
**			direction to the turn_direction multiplied by the rotate_speed.
**		2)	We normalize the new player's direction.
**		3)	We set the player's direction to the new player's direction.
		EXAMPLE: if the player's direction is 0, and the turn_direction is 1,
		and the rotate_speed is 5, the new player's direction will be 
		0 + (1 * 5) = 5, and we normalize it to 5.
******************************************************************************/
void	rotate_the_player(t_stock *stock)
{
	double	new_player_direction;
	
	new_player_direction = stock->player->player_direction 
		+ (stock->player->turn_direction * stock->player->rotate_speed);
	stock->player->player_direction = normalize_angle(new_player_direction);
}