/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMiniMap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:02:16 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/19 17:02:26 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "cube3d.h"

void	draw_background(t_stock *stock)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH / 4)
	{
		j = 0;
		while (j < WIDTH / 4)
		{
			my_mlx_pixel_put(stock->img, j, i, GREY);
			j++;
		}
		my_mlx_pixel_put(stock->img, 0, i, BLACK);
		my_mlx_pixel_put(stock->img, 1, i, BLACK);
		my_mlx_pixel_put(stock->img, j - 1, i, BLACK);
		i++;
	}
	j = 0;
	while (j < (WIDTH / 4))
	{
		my_mlx_pixel_put(stock->img, j, i, BLACK);
		j++;
	}
}

void draw_line_using_angle(t_stock *stock, int len, int color)
{
	int		x;
	int		y;
	double	angle;
	
	angle = to_radians(stock->player->player_direction);
	x = (MINI_MAP_BOX_ZIZE * 2) + (MINI_MAP_BOX_ZIZE / 2);
	y = (MINI_MAP_BOX_ZIZE * 2) + (MINI_MAP_BOX_ZIZE / 2);
	while (len > 0)
	{
		my_mlx_pixel_put(stock->img, x, y, color);
		x = x + cos(angle) * stock->player->turn_direction;
		y = y + sin(angle) * stock->player->turn_direction;
		len--;
	}
}



void	draw_the_player(t_stock *stock)
{
	int		y;
	int		x;
	int		ct;
	double	angle;
	double	increment;
	
	increment = (double)FOV / (double)WIDTH;
	angle = normalize_angle(stock->player->player_direction - (double)(FOV / 2));
	ct = (MINI_MAP_BOX_ZIZE * 2) + (MINI_MAP_BOX_ZIZE / 2);
	y = (MINI_MAP_BOX_ZIZE * 2);
	while (y <=(MINI_MAP_BOX_ZIZE * 4))
	{
		x = (MINI_MAP_BOX_ZIZE * 2);
		while (x <= (MINI_MAP_BOX_ZIZE * 3))
		{
			if (sqrt(pow((x - ct), 2) + pow((y - ct), 2)) < 10)
				my_mlx_pixel_put(stock->img, x, y, RED);
			x++;
		}
		y++;
	}
	x = 0;
	while (x++ < 60)
	{
		dda_line(stock,ct + cos(to_radians(angle)) * 40, ct + sin(to_radians(angle)) * 40, RED);
		angle += 1;
	}
}

void	draw_profile_mini_map(t_stock *stock)
{
	int	x;
	int	y;
	int	max_x;
	int	max_y;
	int area;
	
	area = ((MINI_MAP_BOX_ZIZE / 2) + (2 * MINI_MAP_BOX_ZIZE));
	max_x = stock->player->player_pos_x + area;
	if (max_x > (stock->map_width * MINI_MAP_BOX_ZIZE))
		max_x = (stock->map_width * MINI_MAP_BOX_ZIZE);
	max_y = stock->player->player_pos_y + area;
	if (max_y > (stock->map_height * MINI_MAP_BOX_ZIZE))
		max_y = (stock->map_height * MINI_MAP_BOX_ZIZE);
	y = stock->player->player_pos_y - area;
	if (y < 0)
		y = 0;
	int i = 0;
	int j = 0;
	while (y < max_y)
	{
		x = stock->player->player_pos_x - area;
		if (x < 0)
			x = 0;
		j = 0;
		while (x < max_x)
		{
			if (stock->ex_map[y / MINI_MAP_BOX_ZIZE][x / MINI_MAP_BOX_ZIZE] == '1')
				my_mlx_pixel_put(stock->img, j, i, BLACK);
			// if (stock->ex_map[y / MINI_MAP_BOX_ZIZE][x / MINI_MAP_BOX_ZIZE] == '0')
			// 	my_mlx_pixel_put(stock->img, j, i, WHITE);
			x++;
			j++;
		}
		i++;
		y++;
	}
}

void	draw_border(t_stock *stock)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 6)
	{
		x = 0;
		while (x < (WIDTH / 4))
			my_mlx_pixel_put(stock->img, x++, y, 0x36544c);
	}
	y = (WIDTH / 4) - 6;
	while (++y <=  (WIDTH / 4))
	{
		x = 0;
		while (x < (WIDTH / 4))
			my_mlx_pixel_put(stock->img, x++, y, 0x36544c);
	}
	y = 0;
	while (y < (WIDTH / 4))
	{
		x = 0;
		while (x < 6)
			my_mlx_pixel_put(stock->img, x++, y, 0x36544c);
		x = (WIDTH / 4) - 6;
		while (x < (WIDTH / 4))
			my_mlx_pixel_put(stock->img, x++, y, 0x36544c);
		y++;
	}
	
}





void	draw_icons(t_stock *stock)
{
	stock->icons = malloc(sizeof(t_texture *) * 5);
	if (!stock->icons)
		return ;
	
	stock->icons[0] = malloc(sizeof(t_texture));
	stock->icons[0]->img = mlx_xpm_file_to_image(stock->mlx_ptr,
			"./textures/icons/left.xpm", &(stock->icons[0]->width),
			&(stock->icons[0]->height));
	if (!stock->icons[0]->img)
		return ;
	stock->icons[0]->addr = mlx_get_data_addr(stock->icons[0]->img,
			&stock->icons[0]->bits_per_pixel, &stock->icons[0]->line_length,
			&stock->icons[0]->endian);
	if (!stock->icons[0]->addr)
		return ;

	stock->icons[1] = malloc(sizeof(t_texture));
	stock->icons[1]->img = mlx_xpm_file_to_image(stock->mlx_ptr,
			"./textures/icons/right.xpm", &(stock->icons[1]->width),
			&(stock->icons[1]->height));
	if (!stock->icons[1]->img)
		return ;
	stock->icons[1]->addr = mlx_get_data_addr(stock->icons[1]->img,
			&stock->icons[1]->bits_per_pixel, &stock->icons[1]->line_length,
			&stock->icons[1]->endian);
	if (!stock->icons[1]->addr)
		return ;
	
	stock->icons[2] = malloc(sizeof(t_texture));
	stock->icons[2]->img = mlx_xpm_file_to_image(stock->mlx_ptr,
			"./textures/icons/mouse.xpm", &(stock->icons[2]->width),
			&(stock->icons[2]->height));
	if (!stock->icons[2]->img)
		return ;
	stock->icons[2]->addr = mlx_get_data_addr(stock->icons[2]->img,
			&stock->icons[2]->bits_per_pixel, &stock->icons[2]->line_length,
			&stock->icons[2]->endian);
	if (!stock->icons[2]->addr)
		return ;
	
	stock->icons[3] = malloc(sizeof(t_texture));
	stock->icons[3]->img = mlx_xpm_file_to_image(stock->mlx_ptr,
			"./textures/player.xpm", &(stock->icons[3]->width),
			&(stock->icons[3]->height));
	if (!stock->icons[3]->img)
		return ;
	stock->icons[3]->addr = mlx_get_data_addr(stock->icons[3]->img,
			&stock->icons[3]->bits_per_pixel, &stock->icons[3]->line_length,
			&stock->icons[3]->endian);
	if (!stock->icons[3]->addr)
		return ;
	
	
	stock->icons[4] = NULL;

	

	int y = 0;
	int x;
	int color;
	while (y < (int)stock->icons[2]->height)
	{
		x = 0;
		while (x < (int)stock->icons[2]->width)
		{
			color = *(unsigned int *)(stock->icons[2]->addr + (y * stock->icons[2]->line_length + x * (stock->icons[2]->bits_per_pixel / 8)));
			if (color >= 0)
				my_mlx_pixel_put(stock->img, x + ((WIDTH / 4) + 5), y + 10, color);
		
			x++;
		}
		y++;
	}
	y = 0;	
	while (y < (int)stock->icons[0]->height)
	{
		x = 0;
		while (x < (int)stock->icons[0]->width)
		{
			color = *(unsigned int *)(stock->icons[0]->addr + (y * stock->icons[0]->line_length + x * (stock->icons[0]->bits_per_pixel / 8)));
			
			if (color >= 0)
				my_mlx_pixel_put(stock->img, x + ((WIDTH / 4) + 5), y + 65, color);
			x++;
		}
		y++;
	}
	y = 0;
	while (y < (int)stock->icons[1]->height)
	{
		x = 0;
		while (x < (int)stock->icons[1]->width)
		{
			color = *(unsigned int *)(stock->icons[1]->addr + (y * stock->icons[1]->line_length + x * (stock->icons[1]->bits_per_pixel / 8)));
			
			if (color >= 0)
				my_mlx_pixel_put(stock->img, x + ((WIDTH / 4) + 128), y + 65, color);
			x++;
		}
		y++;
	}
	y = HIGTH / 2 -  64;
	while (y < (int)stock->icons[3]->height)
	{
		x = 0;
		while (x < (int)stock->icons[3]->width)
		{
			color = *(unsigned int *)(stock->icons[3]->addr 
				+ (y * stock->icons[3]->line_length
				+ x * (stock->icons[3]->bits_per_pixel / 8)));
			if (color >= 0)
				my_mlx_pixel_put(stock->img, x , y , color);
			x++;
		}
		y++;
	}
	x = WIDTH / 2 - 10;
	while (x < WIDTH / 2 + 10)
	{
		my_mlx_pixel_put(stock->img, x , (HIGTH / 2) , GREEN);	
		x++;	
	}
	y = HIGTH / 2 -  10;
	while (y < HIGTH / 2 + 10)
	{
		my_mlx_pixel_put(stock->img, (WIDTH / 2) , y , GREEN);	
		y++;	
	}
}

void	draw_mini_map(t_stock *stock)
{
	// draw_background(stock);
	draw_profile_mini_map(stock);
	draw_the_player(stock);
	draw_border(stock);
	draw_icons(stock);
}