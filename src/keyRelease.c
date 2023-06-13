/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyRelease.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:28:27 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 12:00:45 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/*****************************************************************************
**		key_release:
		HOW IT WORKS:
**		1)	We check if the key released is one of the keys we need to stop the
**			player.
		EXAMPLE: when we release the right key, we set the player's 
		turn_direction to 0, and this will stop the player from turning. 
		because in the update function, we check if the player's turn_direction
		is 0 or not, if it is 0, we don't update the player's direction.
		it's the same for the other keys.
*****************************************************************************/
int	key_release(int key, t_stock *stock)
{
	if (key == RIGHT_KEY)
		stock->player->turn_direction = 0;
	if (key == LEFT_KEY)
		stock->player->turn_direction = 0;
	if (key == S_KEY)
		stock->player->walk_direction = 0;
	if (key == W_KEY)
		stock->player->walk_direction = 0;
	if (key == D_KEY)
		stock->player->sideways = 0;
	if (key == A_KEY)
		stock->player->sideways = 0;
	if (key == ESC_KEY)
		exit(1);
	return (0);
}
