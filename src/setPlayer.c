/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setPlayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:18:10 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 11:52:04 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

/*****************************************************************************
**		get_player_charachter: get the player charachter from the map

		HOW: 1- loop through the map
			 2- if the current charachter is a player charachter save his
			 position and return his charachter
*****************************************************************************/
char	get_player_charachter(t_stock *stock)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (stock->ex_map[i])
	{
		j = 0;
		while (stock->ex_map[i][j])
		{
			if (stock->ex_map[i][j] == 'N' || stock->ex_map[i][j] == 'S'
				|| stock->ex_map[i][j] == 'E' || stock->ex_map[i][j] == 'W')
			{
				stock->player->player_pos_x = j * MINI_MAP_BOX_ZIZE
					+ (MINI_MAP_BOX_ZIZE / 2);
				stock->player->player_pos_y = i * MINI_MAP_BOX_ZIZE
					+ (MINI_MAP_BOX_ZIZE / 2);
				c = stock->ex_map[i][j];
				stock->ex_map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (stock->map_height = i, stock->map_width = j, c);
}

/*****************************************************************************
**		set_player: set the player position and direction

		HOW: 1- get the player charachter from the map
			 2- set the player position and direction according to the
			 charachter
			 3- set the player speed and rotation speed				
*****************************************************************************/
bool	set_player(t_stock *stock)
{
	char	player;

	stock->player = malloc(sizeof(t_player));
	if (!stock->player)
		return (false);
	player = get_player_charachter(stock);
	if (player == 'N')
		stock->player->player_direction = 270;
	else if (player == 'S')
		stock->player->player_direction = 90;
	else if (player == 'E')
		stock->player->player_direction = 0;
	else if (player == 'W')
		stock->player->player_direction = 180;
	stock->player->rotate_speed = TURNSPEED;
	stock->player->walk_direction = 0;
	stock->player->turn_direction = 0;
	stock->player->sideways = 0;
	stock->player->walk_speed = SPEED;
	return (true);
}
