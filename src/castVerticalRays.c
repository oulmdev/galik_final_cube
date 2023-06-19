/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castVerticalRays.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:32:00 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/18 18:19:30 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

double	get_vertical_distance(t_stock *stock, double ray_angle, int ray_index)
{
	double	yintercept_verti;
	double	xintercept_verti;
	double	xstep;
	double	ystep;
	double	next_verti_touch_x;
	double	next_verti_touch_y;

	xintercept_verti = floor(stock->player->player_pos_x 
		/ (double)MINI_MAP_BOX_ZIZE) * (double)MINI_MAP_BOX_ZIZE;
	if (stock->rays[ray_index]->is_ray_facing_right)
		xintercept_verti += MINI_MAP_BOX_ZIZE;
	yintercept_verti = stock->player->player_pos_y 
		+ (xintercept_verti - stock->player->player_pos_x)
		* tan(to_radians(ray_angle));
	
	xstep = MINI_MAP_BOX_ZIZE;
	if (stock->rays[ray_index]->is_ray_facing_left)
		xstep *= -1;
	ystep = xstep * tan(to_radians(ray_angle));
	next_verti_touch_x = xintercept_verti;
	next_verti_touch_y = yintercept_verti;
	while (next_verti_touch_x >= 0 && next_verti_touch_x 
		<= (WIDTH * MINI_MAP_BOX_ZIZE) && next_verti_touch_y
		>= 0 && next_verti_touch_y <= (HIGTH * MINI_MAP_BOX_ZIZE))
	{
		if ((int)(next_verti_touch_y / MINI_MAP_BOX_ZIZE)
			>= stock->map_height || (int)((next_verti_touch_x
			- stock->rays[ray_index]->is_ray_facing_left)
			/ MINI_MAP_BOX_ZIZE) >= stock->map_width)
			break;
		if (stock->ex_map[(int)(next_verti_touch_y
			/ MINI_MAP_BOX_ZIZE)][(int)((next_verti_touch_x
			- stock->rays[ray_index]->is_ray_facing_left)
			/ MINI_MAP_BOX_ZIZE)] == '1'
			|| stock->ex_map[(int)(next_verti_touch_y
			/ MINI_MAP_BOX_ZIZE)][(int)(next_verti_touch_x
			/ MINI_MAP_BOX_ZIZE)] == '#')
		{
			stock->rays[ray_index]->was_hit_vertical = true;
			stock->rays[ray_index]->vertical_wall_hit_x = next_verti_touch_x;
			stock->rays[ray_index]->vertical_wall_hit_y = next_verti_touch_y;
			stock->rays[ray_index]->wall_hit_content =
				(stock->ex_map[(int)(next_verti_touch_y
				/ MINI_MAP_BOX_ZIZE)][(int)(next_verti_touch_x
				/ MINI_MAP_BOX_ZIZE)]);
			break;
		}
		next_verti_touch_x += xstep;
		next_verti_touch_y += ystep;
	}
	if (stock->rays[ray_index]->was_hit_vertical)
		return (sqrt(pow((next_verti_touch_x - stock->player->player_pos_x), 2)
			+ pow((next_verti_touch_y - stock->player->player_pos_y), 2)));
	return (INFINITY);
}