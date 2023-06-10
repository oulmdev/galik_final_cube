/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startTheGame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:45:34 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/09 22:43:25 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"



bool	allocate_ray(t_stock *stock)
{
	int	number_of_rays;
	int	i;
	
	i = 0;
	number_of_rays = (WIDTH / WALL_STRIP_WIDTH);
	stock->rays = (t_ray **) malloc(sizeof(t_ray *) * (number_of_rays + 1));
	if (!stock->rays)
		return (false);
	stock->rays[number_of_rays] = NULL;
	while (i < number_of_rays)
	{
		stock->rays[i] = (t_ray *) malloc(sizeof(t_ray));
		if (!stock->rays[i])
			return (false);
		stock->rays[i]->ray_angle = 0;
		stock->rays[i]->vertical_wall_hit_x = 0;
		stock->rays[i]->vertical_wall_hit_y = 0;
		stock->rays[i]->horizontal_wall_hit_x = 0;
		stock->rays[i]->horizontal_wall_hit_y = 0;
		stock->rays[i]->distance = 0;
		stock->rays[i]->was_hit_vertical = false;
		stock->rays[i]->is_ray_facing_up = false;
		stock->rays[i]->is_ray_facing_down = false;
		stock->rays[i]->is_ray_facing_left = false;
		stock->rays[i]->is_ray_facing_right = false;
		stock->rays[i]->was_hit_horizontal = false;
		stock->rays[i]->wall_hit_content = 0;
		i++;
	}
	return (true);
}

bool	set_mlx(t_stock *stock)
{
	stock->img = malloc(sizeof(t_img));
	if (!stock->img)
		return (false);
	stock->mlx_ptr = mlx_init();
	if (!stock->mlx_ptr)
		return (false);
	stock->win_ptr = mlx_new_window(stock->mlx_ptr, WIDTH,HIGTH, "Cube3D");
	if (!stock->win_ptr)
		return (false);
	stock->img->img = mlx_new_image(stock->mlx_ptr, WIDTH, HIGTH);
	if (!stock->img->img)
		return (false);
	stock->img->addr = mlx_get_data_addr(stock->img->img, 
		&stock->img->bits_per_pixel, &stock->img->line_length, 
		&stock->img->endian);
	if (!stock->img->addr)
		return (false);
	if (!allocate_ray(stock))
		return (false);
	return (true);
}


char	get_player_charachter(t_stock *stock)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (stock->ex_map[i])
	{
		j = 0;
		while (stock->ex_map[i][j])
		{
			if (stock->ex_map[i][j] == 'N' || stock->ex_map[i][j] == 'S' 
				|| stock->ex_map[i][j] == 'E' || stock->ex_map[i][j] == 'W')
			{
				stock->player->player_pos_x = j * MINI_MAP_BOX_ZIZE 
					+ (MINI_MAP_BOX_ZIZE / 2);
				stock->player->player_pos_y = i * MINI_MAP_BOX_ZIZE 
					+ (MINI_MAP_BOX_ZIZE / 2);
				c = stock->ex_map[i][j] , stock->ex_map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (stock->map_height = i, stock->map_width = j, c);
}

bool	set_player(t_stock *stock)
{
	char	player;
	stock->player = malloc(sizeof(t_player));
	if (!stock->player)
		return (false);
	player = get_player_charachter(stock);
	if (player == 'N')
		stock->player->player_direction = 270;
	else if (player == 'S')
		stock->player->player_direction = 90;
	else if (player == 'E')
		stock->player->player_direction = 0;
	else if (player == 'W')
		stock->player->player_direction = 180;
	stock->player->rotate_speed = TURNSPEED;
	stock->player->walk_direction = 0;
	stock->player->turn_direction = 0;
	stock->player->sideways = 0;
	stock->player->walk_speed = SPEED;
	return (true);
}

int	exit_the_game(int key, t_stock *stock)
{
	exit(0);
}

bool	set_textures(t_stock *stock)
{
	stock->texture = (t_texture **)malloc(sizeof(t_texture *) * 5);
	if (!stock->texture)
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[4] = NULL;
	stock->texture[0] = malloc(sizeof(t_texture));
	if (!stock->texture[0])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[0]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->no, &stock->texture[0]->width, 
		&stock->texture[0]->height);
	if (!stock->texture[0]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[0]->addr = mlx_get_data_addr(stock->texture[0]->img, 
		&stock->texture[0]->bits_per_pixel, &stock->texture[0]->line_length, 
		&stock->texture[0]->endian);
	if (!stock->texture[0]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	
	stock->texture[1] = malloc(sizeof(t_texture));
	if (!stock->texture[1])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[1]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->we, &stock->texture[1]->width, 
		&stock->texture[1]->height);
	if (!stock->texture[1]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[1]->addr = mlx_get_data_addr(stock->texture[1]->img, 
		&stock->texture[1]->bits_per_pixel, &stock->texture[1]->line_length, 
		&stock->texture[1]->endian);
	if (!stock->texture[1]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	
	stock->texture[2] = malloc(sizeof(t_texture));
	if (!stock->texture[2])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[2]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->so, &stock->texture[2]->width, 
		&stock->texture[2]->height);
	if (!stock->texture[2]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[2]->addr = mlx_get_data_addr(stock->texture[2]->img, 
		&stock->texture[2]->bits_per_pixel, &stock->texture[2]->line_length, 
		&stock->texture[2]->endian);
	if (!stock->texture[2]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);

	stock->texture[3] = malloc(sizeof(t_texture));
	if (!stock->texture[3])
		return (print("Error\nFailed to allocate memory for texture\n", 2), false);
	stock->texture[3]->img = mlx_xpm_file_to_image(stock->mlx_ptr, 
		stock->ea, &stock->texture[3]->width, 
		&stock->texture[3]->height);
	if (!stock->texture[3]->img)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	stock->texture[3]->addr = mlx_get_data_addr(stock->texture[3]->img, 
		&stock->texture[3]->bits_per_pixel, &stock->texture[3]->line_length, 
		&stock->texture[3]->endian);
	if (!stock->texture[3]->addr)
		return (print("Error\nFailed to load `NO' texture\n", 2), false);
	
	


	return (true);
}

bool	start_the_game(t_stock *stock)
{
	if (!set_mlx(stock))
		return (false);
	if (!set_player(stock))
		return (false);
	if (!set_textures(stock))
		return (false);
	mlx_hook(stock->win_ptr, 2, 0, key_press, stock);
	mlx_hook(stock->win_ptr, 3, 0, key_release, stock);
	mlx_hook(stock->win_ptr, 17, 0, exit_the_game, stock);
	mlx_loop_hook(stock->mlx_ptr, update, stock);
	mlx_put_image_to_window(stock->mlx_ptr, stock->win_ptr, stock->img->img, 0, 0);
	mlx_loop(stock->mlx_ptr);
	return true;
}
