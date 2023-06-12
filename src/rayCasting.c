/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayCasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:20:18 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/13 00:19:34 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

void	horizontal_case(t_stock *stock, t_tools tools)
{
	stock->rays[tools.ray_index]->distance = tools.horizontal_distance 
		* cos(to_radians((stock->player->player_direction - tools.ray_angle)));
	stock->rays[tools.ray_index]->was_hit_horizontal = true;
	stock->rays[tools.ray_index]->was_hit_vertical = false;
	stock->rays[tools.ray_index]->projection_distance = ((MINI_MAP_BOX_ZIZE) 
		/ (stock->rays[tools.ray_index]->distance)) * ((double)WIDTH / 2) 
		/ tan(to_radians((double)FOV / 2));
	if (stock->rays[tools.ray_index]->projection_distance > HIGTH)
		stock->rays[tools.ray_index]->projection_distance = HIGTH;
	else if (stock->rays[tools.ray_index]->projection_distance < 0)
		stock->rays[tools.ray_index]->projection_distance = 0;
}

void	vertical_case(t_stock *stock, t_tools tools)
{
	stock->rays[tools.ray_index]->distance = tools.vertical_distance 
		* cos(to_radians((stock->player->player_direction - tools.ray_angle)));
	stock->rays[tools.ray_index]->was_hit_horizontal = false;
	stock->rays[tools.ray_index]->was_hit_vertical = true;
	stock->rays[tools.ray_index]->projection_distance = ((MINI_MAP_BOX_ZIZE)
		/ (stock->rays[tools.ray_index]->distance)) * ((double)WIDTH / 2)
		/ tan(to_radians((double)FOV / 2));
	if (stock->rays[tools.ray_index]->projection_distance > HIGTH)
		stock->rays[tools.ray_index]->projection_distance = HIGTH;
	else if (stock->rays[tools.ray_index]->projection_distance < 0)
		stock->rays[tools.ray_index]->projection_distance = 0;
}

void	fill_ray_data(t_stock *stock, double ray_angle, int i)
{
	stock->rays[i]->ray_angle = ray_angle;
	stock->rays[i]->is_ray_facing_down = (ray_angle > 0 && ray_angle < 180);
	stock->rays[i]->is_ray_facing_up = (!stock->rays[i]->is_ray_facing_down);
	stock->rays[i]->is_ray_facing_left = (ray_angle > 90 && ray_angle < 270);
	stock->rays[i]->is_ray_facing_right = (!stock->rays[i]->is_ray_facing_left);
}

void	ray_casting(t_stock *stock)
{
	t_tools	tools;
	
	tools.ray_index = 0;
	tools.increment = (double)FOV / (double)WIDTH;
	tools.ray_angle = (stock->player->player_direction - (double)(FOV / 2));
	while (tools.ray_index < WIDTH)
	{
		tools.ray_angle = normalize_angle(tools.ray_angle);
		fill_ray_data(stock, tools.ray_angle, tools.ray_index);
		tools.horizontal_distance = get_horizontal_distance(stock,
			tools.ray_angle, tools.ray_index);
		tools.vertical_distance = get_vertical_distance(stock,
			tools.ray_angle, tools.ray_index);
		if (tools.horizontal_distance < tools.vertical_distance)
			horizontal_case(stock, tools);
		else
			vertical_case(stock, tools);
		tools.ray_angle = (tools.ray_angle + tools.increment);
		tools.ray_index++;
	}
	draw_3d_projection(stock);
}
