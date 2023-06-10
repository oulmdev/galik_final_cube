/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:46:17 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/10 14:05:00 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"

double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	return (angle);
}

void	rotate_the_player(t_stock *stock)
{
	double	new_player_direction;
	
	new_player_direction = stock->player->player_direction 
		+ (stock->player->turn_direction * stock->player->rotate_speed);
	stock->player->player_direction = normalize_angle(new_player_direction);
}

void	move_the_player(t_stock *stock)
{
	double	new_player_x;
	double	new_player_y;
	double	new_player_direction;
	
	if (!stock->player->sideways)
	{	
		new_player_x = stock->player->player_pos_x + 
			cos(to_radians(stock->player->player_direction)) * (stock->player->walk_direction * stock->player->walk_speed);
		new_player_y = stock->player->player_pos_y 
			+ sin(to_radians(stock->player->player_direction)) * (stock->player->walk_direction * stock->player->walk_speed);
	}
	else if (stock->player->sideways != 0)
	{
		new_player_direction = stock->player->player_direction + 90;
		if (new_player_direction <= 0)
			new_player_direction += 360;
		if (new_player_direction > 360)
			new_player_direction -= 360;
		new_player_x = stock->player->player_pos_x + 
			cos(to_radians(new_player_direction)) * (stock->player->sideways * stock->player->walk_speed);
		new_player_y = stock->player->player_pos_y 
			+ sin(to_radians(new_player_direction)) * (stock->player->sideways * stock->player->walk_speed);
	}
	if ((stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x / MINI_MAP_BOX_ZIZE] != '1' && 
		stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x / MINI_MAP_BOX_ZIZE] != '#'))
	{
		stock->player->player_pos_x = new_player_x;
		stock->player->player_pos_y = new_player_y;
	}	
}


void	draw_mini_map_background(t_stock *stock)
{
	int	i;
	int	j;

	i = 0;
	while (i < (MINI_MAP_BOX_ZIZE * MINI_MAP_SIZE))
	{
		j = 0;
		while (j < (MINI_MAP_BOX_ZIZE * (MINI_MAP_SIZE)))
			my_mlx_pixel_put(stock->img, i, j++, WHITE);
		i++;
	}
}

// int	resize_the_map(t_stock *stock, int	resize, int flag)
// {
// 	int	factor;

// 	factor = 0;
// 	if (flag)
// 	{
// 		while ()
// 		{
			
// 		}
// 	}
// }

// void	draw_mini_map(t_stock *stock)
// {
// 	t_pars	draw;
	
// 	draw_mini_map_background(stock);
// 	draw.x = ((int)stock->player->player_pos_x / MINI_MAP_BOX_ZIZE);
// 	draw.y = ((int)stock->player->player_pos_y / MINI_MAP_BOX_ZIZE);
// 	draw.i = draw.x - resize_the_map(stock);
// }

void draw_circle(t_stock *stock, int x_x, int y_y, int wall, int color)
{
	int x;
	int y;

	x = 0;
	while (x < wall)
	{
		y = 0;
		while (y < wall)
		{
			if (sqrt((pow(((wall / 2) - x), 2)) + (pow(((wall / 2) - y), 2))) < wall / 2)
				my_mlx_pixel_put(stock->img, x + x_x, y + y_y, color);
			y++;
		}
		x++;
	}
}
/*	TODO:
**	you have to fully understand this function and how it works.
*/
void ddaLine(t_stock *stock, int x2, int y2, int color) {
	// int length = fabs(x2 - stock->player->player_pos_x) > fabs(y2 - stock->player->player_pos_y) ? fabs(x2 - stock->player->player_pos_x) : fabs(y2 - stock->player->player_pos_y);

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

void ray_intersept(t_stock *stock){
	double	yintercept_hori;
	double	xintercept_hori;
	double	xstep;
	

	yintercept_hori = sqrt((pow(floor(stock->player->player_pos_y / (double)MINI_MAP_BOX_ZIZE) * (double)MINI_MAP_BOX_ZIZE,2)));
	xintercept_hori = sqrt(pow(floor(stock->player->player_pos_x + (stock->player->player_pos_y - yintercept_hori) / tan(to_radians(stock->player->player_direction))),2));
	xstep = MINI_MAP_BOX_ZIZE / tan(to_radians(stock->player->player_direction));
	while (xintercept_hori >= 0 && xintercept_hori <= WIDTH && yintercept_hori >= 0 && yintercept_hori <= HIGTH)
	{
		if (stock->ex_map[(int)(yintercept_hori / MINI_MAP_BOX_ZIZE)][(int)(xintercept_hori / MINI_MAP_BOX_ZIZE)] == '1')
			break;
		xintercept_hori += xstep;
		yintercept_hori += MINI_MAP_BOX_ZIZE;
	}
	ddaLine(stock, xintercept_hori, yintercept_hori, RED);
}
/*
	TODO:
	You have to to fix the texture problem.
*/
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

void	fill_ray_data(t_stock *stock, double ray_angle, int ray_index)
{
	stock->rays[ray_index]->ray_angle = ray_angle;
	stock->rays[ray_index]->is_ray_facing_down = (ray_angle > 0 && ray_angle < 180);
	stock->rays[ray_index]->is_ray_facing_up = (!stock->rays[ray_index]->is_ray_facing_down);
	stock->rays[ray_index]->is_ray_facing_left = (ray_angle > 90 && ray_angle < 270);
	stock->rays[ray_index]->is_ray_facing_right = (!stock->rays[ray_index]->is_ray_facing_left);
	
}

double	get_vertical_distance(t_stock *stock, double ray_angle, int ray_index)
{
	double	yintercept_verti;
	double	xintercept_verti;
	double	xstep;
	double	ystep;
	double	next_verti_touch_x;
	double	next_verti_touch_y;

	xintercept_verti = floor(stock->player->player_pos_x / (double)MINI_MAP_BOX_ZIZE) * (double)MINI_MAP_BOX_ZIZE;
	if (stock->rays[ray_index]->is_ray_facing_right)
		xintercept_verti += MINI_MAP_BOX_ZIZE;

	yintercept_verti = stock->player->player_pos_y + (xintercept_verti - stock->player->player_pos_x) * tan(to_radians(ray_angle));
	xstep = MINI_MAP_BOX_ZIZE;
	if (stock->rays[ray_index]->is_ray_facing_left)
		xstep *= -1;

	ystep = MINI_MAP_BOX_ZIZE * tan(to_radians(ray_angle));
	if (stock->rays[ray_index]->is_ray_facing_up && ystep > 0)
		ystep *= -1;
	if (stock->rays[ray_index]->is_ray_facing_down && ystep < 0)
		ystep *= -1;

	next_verti_touch_x = xintercept_verti;
	next_verti_touch_y = yintercept_verti;
	while (next_verti_touch_x >= 0 && next_verti_touch_x <= (WIDTH * MINI_MAP_BOX_ZIZE) && next_verti_touch_y >= 0 && next_verti_touch_y <= (HIGTH * MINI_MAP_BOX_ZIZE))
	{
		if ((int)(next_verti_touch_y / MINI_MAP_BOX_ZIZE) >= stock->map_height || (int)((next_verti_touch_x - stock->rays[ray_index]->is_ray_facing_left) / MINI_MAP_BOX_ZIZE) >= stock->map_width)
			break;
		if (stock->ex_map[(int)(next_verti_touch_y / MINI_MAP_BOX_ZIZE)][(int)((next_verti_touch_x - stock->rays[ray_index]->is_ray_facing_left) / MINI_MAP_BOX_ZIZE)] == '1' || stock->ex_map[(int)(next_verti_touch_y / MINI_MAP_BOX_ZIZE)][(int)(next_verti_touch_x / MINI_MAP_BOX_ZIZE)] == '#')
		{
			stock->rays[ray_index]->was_hit_vertical = true;
			stock->rays[ray_index]->vertical_wall_hit_x = next_verti_touch_x;
			stock->rays[ray_index]->vertical_wall_hit_y = next_verti_touch_y;
			stock->rays[ray_index]->wall_hit_content = (stock->ex_map[(int)(next_verti_touch_y / MINI_MAP_BOX_ZIZE)][(int)(next_verti_touch_x / MINI_MAP_BOX_ZIZE)]);
			break;
		}
		next_verti_touch_x += xstep;
		next_verti_touch_y += ystep;
	}
	if (stock->rays[ray_index]->was_hit_vertical)
		return (sqrt(pow((next_verti_touch_x - stock->player->player_pos_x), 2) + pow((next_verti_touch_y - stock->player->player_pos_y), 2)));
	return (INFINITY);
}

/*	TODO: you have a litle problem in the y if it's negative you have to know whay.
	and x in the horisontal,
*/

int	get_xpm_color(t_stock *stock, t_texture *texture, int texture_offset_x, int texture_offset_y)
{
	int	color;
	color = *(int*)(texture->addr + (texture_offset_y * texture->line_length + texture_offset_x * (texture->bits_per_pixel / 8)));
	return (color);
}

void	draw_3d_projection(t_stock *stock)
{
	int		texture_offset_x;
	int		texture_offset_y;
	int		color;
	int 	texture_index;
	
	
	for (int i =0; i < WIDTH; i++)
	{
		if (stock->rays[i]->was_hit_horizontal && stock->rays[i]->is_ray_facing_down)
			texture_index = 0;
		else if (stock->rays[i]->was_hit_horizontal && stock->rays[i]->is_ray_facing_up)
			texture_index = 1;
		else if (stock->rays[i]->was_hit_vertical && stock->rays[i]->is_ray_facing_left)
			texture_index = 2;
		else if (stock->rays[i]->was_hit_vertical && stock->rays[i]->is_ray_facing_right)
			texture_index = 3;
		if (stock->rays[i]->was_hit_vertical)
			texture_offset_x = (int)stock->rays[i]->vertical_wall_hit_y % MINI_MAP_BOX_ZIZE; 
		else if (stock->rays[i]->was_hit_horizontal)
			texture_offset_x = (int)stock->rays[i]->horizontal_wall_hit_x % MINI_MAP_BOX_ZIZE;
		for (int j = (HIGTH / 2) - (stock->rays[i]->projection_distance / 2); j < (HIGTH / 2) + (stock->rays[i]->projection_distance / 2); j++)
		{
			texture_offset_y = (j - (stock->rays[i]->projection_distance / 2) - (HIGTH / 2)) * ((double)MINI_MAP_BOX_ZIZE / stock->rays[i]->projection_distance);// TODO: here you have to change the MINI_MAP_BOX_ZIZE to the real size of the texture height
			if (texture_offset_y < 0)
				texture_offset_y *= -1;
			if (stock->rays[i]->was_hit_vertical)
			{
				color = get_xpm_color(stock, stock->texture[texture_index], texture_offset_x, texture_offset_y);
				my_mlx_pixel_put(stock->img, i, j, color);
				
			}
			else if (stock->rays[i]->was_hit_horizontal)
			{
				color = get_xpm_color(stock, stock->texture[texture_index], texture_offset_x, texture_offset_y);
				my_mlx_pixel_put(stock->img, i, j, color);
			}
		}
	}
}

void	ray_casting(t_stock *stock)
{
	double		horizontal_distance;
	double		vertical_distance;
	double		increment;
	double		ray_angle;
	int			num_of_rays;
	int			ray_index;
	
	ray_index = 0;
	increment = (double)FOV / (double)WIDTH;
	ray_angle = (stock->player->player_direction - (double)(FOV / 2));
	while (ray_index < WIDTH)
	{
		ray_angle = normalize_angle(ray_angle);
		fill_ray_data(stock, ray_angle, ray_index);
		horizontal_distance = (get_horizontal_distance(stock, (ray_angle), ray_index));
		vertical_distance = (get_vertical_distance(stock, (ray_angle), ray_index));
		if (horizontal_distance < vertical_distance)
		{
			stock->rays[ray_index]->distance = horizontal_distance * cos(to_radians((stock->player->player_direction - ray_angle)));
			stock->rays[ray_index]->was_hit_horizontal = true;
			stock->rays[ray_index]->was_hit_vertical = false;
			stock->rays[ray_index]->projection_distance = ((MINI_MAP_BOX_ZIZE) / (stock->rays[ray_index]->distance)) * ((double)WIDTH / 2) / tan(to_radians((double)FOV / 2));
			if (stock->rays[ray_index]->projection_distance > HIGTH)
				stock->rays[ray_index]->projection_distance = HIGTH;
			else if (stock->rays[ray_index]->projection_distance < 0)
				stock->rays[ray_index]->projection_distance = 0;
		}
		else
		{
			stock->rays[ray_index]->distance = vertical_distance * cos(to_radians((stock->player->player_direction - ray_angle)));
			stock->rays[ray_index]->was_hit_horizontal = false;
			stock->rays[ray_index]->was_hit_vertical = true;
			stock->rays[ray_index]->projection_distance = ((MINI_MAP_BOX_ZIZE) / (stock->rays[ray_index]->distance)) * ((double)WIDTH / 2) / tan(to_radians((double)FOV / 2));
			if (stock->rays[ray_index]->projection_distance > HIGTH)
				stock->rays[ray_index]->projection_distance = HIGTH;
			else if (stock->rays[ray_index]->projection_distance < 0)
				stock->rays[ray_index]->projection_distance = 0;
		}
		ray_angle = (ray_angle + increment);
		ray_index++;
	}
	draw_3d_projection(stock);
}

void draw_floor_and_ceiling(t_stock *stock)
{
	int i;
	int j;

	i = 0;
	while (i < HIGTH / 2)
	{
		j = 0;
		while (j < WIDTH)
			my_mlx_pixel_put(stock->img, j++, i, CYAN);
		i++;
	}
	while (i < HIGTH)
	{
		j = 0;
		while (j < WIDTH)
			my_mlx_pixel_put(stock->img, j++, i, BROWN);
		i++;
	}
}

void	draw_every_thing(t_stock *stock)
{
	draw_floor_and_ceiling(stock);
	ray_casting(stock);
}

int	update(t_stock *stock)
{
	mlx_clear_window(stock->mlx_ptr, stock->win_ptr);
	mlx_destroy_image(stock->mlx_ptr, stock->img->img);
	stock->img->img = mlx_new_image(stock->mlx_ptr, WIDTH, HIGTH);
	stock->img->addr = mlx_get_data_addr(stock->img->img,
		&stock->img->bits_per_pixel,
		&stock->img->line_length, &stock->img->endian);
	if (stock->player->turn_direction != 0)
		rotate_the_player(stock);
	if (stock->player->walk_direction != 0 || stock->player->sideways != 0)
		move_the_player(stock);

	draw_every_thing(stock);
	mlx_put_image_to_window(stock->mlx_ptr, stock->win_ptr,
		stock->img->img, 0, 0);
	return 0;
}