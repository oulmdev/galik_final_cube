/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveThePlayer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:10:09 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/17 01:00:26 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/******************************************************************************
**		regular_move: move the player in the direction he is facing

		HOW: calculate the new position of the player by adding the cosinus of
		the angle he is facing to his current position in the x axis and the
		sinus of the angle he is facing to his current position in the y axis
******************************************************************************/
void	regular_move(t_stock *stock, double *new_player_x, double *new_player_y)
{
	*new_player_x = stock->player->player_pos_x
		+ cos(to_radians(stock->player->player_direction))
		* (stock->player->walk_direction * stock->player->walk_speed);
	*new_player_y = stock->player->player_pos_y
		+ sin(to_radians(stock->player->player_direction))
		* (stock->player->walk_direction * stock->player->walk_speed);
}

/******************************************************************************
**		sideways_move: move the player in the direction he is facing

		HOW: calculate the new position of the player by adding the cosinus of
		the angle he is facing + 90 to his current position in the x axis and
		the sinus of the angle he is facing + 90 to his current position in the
		y axis
******************************************************************************/
void	sideways_move(t_stock *stock, double *new_player_x
	, double *new_player_y)
{
	*new_player_x = stock->player->player_pos_x
		+ cos(to_radians(normalize_angle(stock->player->player_direction + 90)))
		* (stock->player->sideways * stock->player->walk_speed);
	*new_player_y = stock->player->player_pos_y
		+ sin(to_radians(normalize_angle(stock->player->player_direction + 90)))
		* (stock->player->sideways * stock->player->walk_speed);
}

/******************************************************************************
**		move_the_player: move the player in the direction he is facing

		HOW: check if the new position of the player is not a wall or a sprite
		before moving him to the new position also check if the player is
		moving sideways or not.
******************************************************************************/
void	move_the_player(t_stock *stock)
{
	double	new_player_x;
	double	new_player_y;

	new_player_x = 0;
	new_player_y = 0;
	if (!stock->player->sideways)
		regular_move(stock, &new_player_x, &new_player_y);
	else if (stock->player->sideways != 0)
		sideways_move(stock, &new_player_x, &new_player_y);
	if ((stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x
			/ MINI_MAP_BOX_ZIZE] != '1'
		&& stock->ex_map[(int)new_player_y
			/ MINI_MAP_BOX_ZIZE][(int)new_player_x
		/ MINI_MAP_BOX_ZIZE] != '#'))
	{
		stock->player->player_pos_x = new_player_x;
		stock->player->player_pos_y = new_player_y;
	}
	stock->draw_the_map = 0;
}
