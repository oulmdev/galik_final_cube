/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyPress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:03:40 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 11:57:30 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/******************************************************************************
**		key_press:
		HOW IT WORKS:
**		1)	We check if the key pressed is one of the keys we need to move the
**			player.
**		2)	We set the player's direction to the right value.
**		3)	We return 0.

		EXAMPLE: when we press the right key, we set the player's turn_direction
		to 1, and when we press the left key, we set the player's turn_direction
		to -1.
		those values will be used in the update function to update the player's
		direction. based on the sign of those values, we will know if we need to
		turn the player to the right or to the left.
		it is the same for the other keys.
******************************************************************************/
int	key_press(int key, t_stock *stock)
{
	if (key == RIGHT_KEY)
		stock->player->turn_direction = 1;
	if (key == LEFT_KEY)
		stock->player->turn_direction = -1;
	if (key == S_KEY)
		stock->player->walk_direction = -1;
	if (key == W_KEY)
		stock->player->walk_direction = 1;
	if (key == D_KEY)
		stock->player->sideways = 1;
	if (key == A_KEY)
		stock->player->sideways = -1;
	if (key == ESC_KEY)
		exit(1);
	return (0);
}
