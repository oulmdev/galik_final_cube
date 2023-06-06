/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyPress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:03:40 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/06 23:27:29 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

int	key_press(int key, t_stock *stock)
{
	if (key == RIGHT_KEY)
		stock->player->turn_direction = 1;
	if (key == LEFT_KEY)
		stock->player->turn_direction = -1;
	if (key == DOWN_KEY)
		stock->player->walk_direction = -1;
	if (key == UP_KEY)
		stock->player->walk_direction = 1;
	if (key == ESC_KEY)
		exit(1);
	return (0);
} 