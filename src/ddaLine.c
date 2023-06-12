/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddaLine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:08:13 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/12 22:08:17 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void dda_line(t_stock *stock, int x2, int y2, int color) 
{
	int		length;
	double	dy;
	double	dx;
	double	y;
	double	x;
	int		i;
	
	if (fabs(x2 - stock->player->player_pos_x) > fabs(y2 - stock->player->player_pos_y))
		length = fabs(x2 - stock->player->player_pos_x);
	else
		length = fabs(y2 - stock->player->player_pos_y);
	
	dx = (x2 - stock->player->player_pos_x) / (double)length;
	dy = (y2 - stock->player->player_pos_y) / (double)length;

	x = stock->player->player_pos_x;
	y = stock->player->player_pos_y;
	i = 0;
	while (i <= length)
	{
		my_mlx_pixel_put(stock->img, x, y, color);
		i++;
		x = x + dx;
		y = y + dy;
	}
}