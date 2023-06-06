/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startTheGame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:45:34 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/06 23:45:11 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cube3d.h"


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
				return ( stock->player->player_pos_x = j * MINI_MAP_BOX_ZIZE 
					+ (MINI_MAP_BOX_ZIZE / 2),
				stock->player->player_pos_y = i * MINI_MAP_BOX_ZIZE 
					+ (MINI_MAP_BOX_ZIZE / 2),
				c = stock->ex_map[i][j] , stock->ex_map[i][j] = '0', c);
			j++;
		}
		i++;
	}
	return (0);
}

bool	set_player(t_stock *stock)
{
	char	player;
	stock->player = malloc(sizeof(t_player));
	if (!stock->player)
		return (false);
	player = get_player_charachter(stock);
	if (player == 'N')
		stock->player->player_angle = 90;
	else if (player == 'S')
		stock->player->player_angle = 270;
	else if (player == 'E')
		stock->player->player_angle = 0;
	else if (player == 'W')
		stock->player->player_angle = 180;
	stock->player->rotate_speed = 1;
	stock->player->walk_direction = 0;
	stock->player->turn_direction = 0;
	stock->player->walk_speed = 3;
	return (true);
}

bool	start_the_game(t_stock *stock)
{
	if (!set_mlx(stock))
		return (false);
	if (!set_player(stock))
		return (false);
	
	mlx_hook(stock->win_ptr, 2, 0, key_press, stock);
	mlx_hook(stock->win_ptr, 3, 0, key_release, stock);
	mlx_loop_hook(stock->mlx_ptr, update, stock);
	mlx_put_image_to_window(stock->mlx_ptr, stock->win_ptr, stock->img->img, 0, 0);
	mlx_loop(stock->mlx_ptr);
	return true;
}
