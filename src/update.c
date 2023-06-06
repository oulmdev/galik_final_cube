/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:46:17 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/07 00:54:32 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"


void	rotate_the_player(t_stock *stock)
{
	double	new_player_angle;
	
	new_player_angle = stock->player->player_angle 
		+ (stock->player->turn_direction * stock->player->rotate_speed);
	if (new_player_angle <= 0)
		new_player_angle += 360;
	if (new_player_angle > 360)
		new_player_angle -= 360;
	stock->player->player_angle = new_player_angle;
}

void	move_the_player(t_stock *stock)
{
	double	new_player_x;
	double	new_player_y;
	
	new_player_x = stock->player->player_pos_x + 
		cos(to_radians(stock->player->player_angle)) * (stock->player->walk_direction * stock->player->walk_speed);
	new_player_y = stock->player->player_pos_y 
		+ sin(to_radians(stock->player->player_angle)) * (stock->player->walk_direction * stock->player->walk_speed);
	if (stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x / MINI_MAP_BOX_ZIZE] != '1' && 
		stock->ex_map[(int)new_player_y / MINI_MAP_BOX_ZIZE][(int)new_player_x / MINI_MAP_BOX_ZIZE] != '#')
	{
		stock->player->player_pos_x = new_player_x;
		stock->player->player_pos_y = new_player_y;
	}	
}


void	draw_square(t_stock *stock, t_pars draw, int color)
{
	int	i;
	int	j;
	
	i = 0;
	while (i <= MINI_MAP_BOX_ZIZE)
	{
		j = 0;
		while (j <= MINI_MAP_BOX_ZIZE)
		{
			my_mlx_pixel_put(stock->img, (draw.j * MINI_MAP_BOX_ZIZE) + j, (draw.i * MINI_MAP_BOX_ZIZE) + i, color);
			j++;
		}
		i++;
	}
}

void	draw_mini_map(t_stock *stock)
{
	t_pars	draw;

	draw.i = 0;
	while (stock->ex_map[draw.i])
	{
		draw.j = 0;
		while (stock->ex_map[draw.i][draw.j])
		{
			if (stock->ex_map[draw.i][draw.j] == '1')
				draw_square(stock, draw, GREY);
			if (stock->ex_map[draw.i][draw.j] == '0')
				draw_square(stock, draw, WHITE);
			draw.j++;
		}
		draw.i++;
	}
}

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

void	draw_every_thing(t_stock *stock)
{
	draw_mini_map(stock);
	draw_circle(stock, stock->player->player_pos_x - MINI_MAP_BOX_ZIZE / 4, stock->player->player_pos_y - MINI_MAP_BOX_ZIZE / 4, MINI_MAP_BOX_ZIZE / 2, RED);
	my_mlx_pixel_put(stock->img, stock->player->player_pos_x, stock->player->player_pos_y, RED);
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

	if (stock->player->walk_direction != 0)
		move_the_player(stock);
		
	draw_every_thing(stock);
	mlx_put_image_to_window(stock->mlx_ptr, stock->win_ptr,
		stock->img->img, 0, 0);
	return 0;
}