/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ddaLine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:08:13 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/15 16:27:00 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void	dda_line(t_stock *stock , double x2, double y2, int color)
{
	double	dx;
	double	dy;
	double	length;
	double	x;
	double	y;
	int		i;
	
	if (fabs(x2 - (2.5 * MINI_MAP_BOX_ZIZE)) > fabs(y2 - (2.5 * MINI_MAP_BOX_ZIZE)))
		length = fabs(x2 - (2.5 * MINI_MAP_BOX_ZIZE));
	else
		length = fabs(y2 - (2.5 * MINI_MAP_BOX_ZIZE));
	
	dx = (x2 - (2.5 * MINI_MAP_BOX_ZIZE)) / length;
	dy = (y2 - (2.5 * MINI_MAP_BOX_ZIZE)) / length;
	
	x = (2.5 * MINI_MAP_BOX_ZIZE);
	y = (2.5 * MINI_MAP_BOX_ZIZE);
	i = 0;
	while (i <= length)
	{
		my_mlx_pixel_put(stock->img, x, y, color);
		i++;
		x = x + dx;
		y = y + dy;
	}
}		