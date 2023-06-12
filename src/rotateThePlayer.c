/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotateThePlayer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:11:06 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 22:11:09 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void	rotate_the_player(t_stock *stock)
{
	double	new_player_direction;
	
	new_player_direction = stock->player->player_direction 
		+ (stock->player->turn_direction * stock->player->rotate_speed);
	stock->player->player_direction = normalize_angle(new_player_direction);
}