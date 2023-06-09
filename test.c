/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 23:38:09 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/09 18:16:37 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>



#include "mlx.h"
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_data;

typedef struct	s_texture {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}				t_texture;

void	draw_resized_image(t_data *data, t_texture *texture, int x, int y, int new_width, int new_height)
{
	float	scale_x = (float)new_width / texture->width;
	float	scale_y = (float)new_height / texture->height;

	for (int i = 0; i < new_height; i++)
	{
		// for (int j = 0; j < new_width; j++)
		// {
			int j = x % texture->width;
			int tex_x = j / scale_x;
			int tex_y = i / scale_y;
			int color = *(int *)(texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8)));
			*(int *)(data->addr + ((y + i) * data->line_len + (x + j) * (data->bpp / 8))) = color;
		// }
	}
}

int		main(void)
{
	t_data		data;
	t_texture	texture;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Resized Image");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &(data.bpp), &(data.line_len), &(data.endian));

	// Load texture image and retrieve pixel data
	texture.img = mlx_xpm_file_to_image(data.mlx, "wood.xpm", &(texture.width), &(texture.height));
	texture.addr = mlx_get_data_addr(texture.img, &(texture.bpp), &(texture.line_len), &(texture.endian));

	// Draw resized image
	int x = 100;
	int y = 100;
	int new_width = 400;
	int new_height = 300;
	draw_resized_image(&data, &texture, x, y, new_width, new_height);

	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
