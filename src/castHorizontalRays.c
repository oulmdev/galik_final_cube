/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castHorizontalRays.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:31:20 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/14 13:50:32 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

/*****************************************************************************
 * 						CAST HORIZONTAL RAYS FUNCTION
 * 		cast_horizontal_rays: cast the horizontal rays.
 * 		HOW IT WORKS:
 * 		1)	We calculate the first horizontal intersection.
 * 		2)	We calculate the horizontal step and the vertical step.
 * 		3)	We calculate the next horizontal touch x and y.
 * 		NOTE: the ray_angle is the angle of the player + the angle of the ray
 * 		we are casting it works because the tan of the angle of the ray is the
 * 		slope of the ray, and the slope of the ray is the same as the slope of
 * 		the line that goes from the player to the intersection point.
*****************************************************************************/
double	get_horizontal_distance(t_stock *stock, double ray_angle, int ray_index)
{
	double	yintercept_hori;
	double	xintercept_hori;
	double	xstep;
	double	ystep;
	double	next_hori_touch_x;
	double	next_hori_touch_y;

	yintercept_hori = floor(stock->player->player_pos_y / (double)MINI_MAP_BOX_ZIZE) * (double)MINI_MAP_BOX_ZIZE;
	if (stock->rays[ray_index]->is_ray_facing_down)
		yintercept_hori += MINI_MAP_BOX_ZIZE;
	xintercept_hori = stock->player->player_pos_x + (yintercept_hori - stock->player->player_pos_y) / tan(to_radians(ray_angle));
	ystep = MINI_MAP_BOX_ZIZE;
	if (stock->rays[ray_index]->is_ray_facing_up)
		ystep *= -1;
	
	xstep = MINI_MAP_BOX_ZIZE / tan(to_radians(ray_angle));
	if (stock->rays[ray_index]->is_ray_facing_left && xstep > 0)
		xstep *= -1;
	if (stock->rays[ray_index]->is_ray_facing_right && xstep < 0)
		xstep *= -1;

	next_hori_touch_x = xintercept_hori;
	next_hori_touch_y = yintercept_hori;
	while (next_hori_touch_x >= 0 && next_hori_touch_x <= (WIDTH * MINI_MAP_BOX_ZIZE) && next_hori_touch_y >= 0 && next_hori_touch_y <= (HIGTH * MINI_MAP_BOX_ZIZE))
	{
		if ((int)((next_hori_touch_y - stock->rays[ray_index]->is_ray_facing_up) / (MINI_MAP_BOX_ZIZE)) >= stock->map_height || (int)(next_hori_touch_x / MINI_MAP_BOX_ZIZE) >= stock->map_width)
			break;
		if (stock->ex_map[(int)((next_hori_touch_y - stock->rays[ray_index]->is_ray_facing_up) / (MINI_MAP_BOX_ZIZE))][(int)(next_hori_touch_x / (MINI_MAP_BOX_ZIZE))] == '1' || stock->ex_map[(int)(next_hori_touch_y / (MINI_MAP_BOX_ZIZE))][(int)(next_hori_touch_x / (MINI_MAP_BOX_ZIZE))] == '#')
		{
			stock->rays[ray_index]->was_hit_horizontal = true;
			stock->rays[ray_index]->horizontal_wall_hit_x = next_hori_touch_x;
			stock->rays[ray_index]->horizontal_wall_hit_y = next_hori_touch_y;
			stock->rays[ray_index]->wall_hit_content = stock->ex_map[(int)(next_hori_touch_y / (MINI_MAP_BOX_ZIZE))][(int)(next_hori_touch_x / (MINI_MAP_BOX_ZIZE))];
			break;
		}
		next_hori_touch_x += xstep;
		next_hori_touch_y += ystep;
	}
	if (stock->rays[ray_index]->was_hit_horizontal)
		return (sqrt(pow((next_hori_touch_x - stock->player->player_pos_x), 2) + pow((next_hori_touch_y - stock->player->player_pos_y), 2)));
	return (INFINITY);
}