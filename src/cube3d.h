/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:18:28 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/15 17:00:13 by moulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <mlx.h>

# define BUFFER_SIZE 1

# define RIGHT_KEY 124
# define LEFT_KEY 123
# define UP_KEY 126
# define DOWN_KEY 125
# define ESC_KEY 53
# define F_KEY 3
# define G_KEY 5
# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2



# define FOV 60
# define MINI_MAP_BOX_ZIZE 64
# define SPEED 10
# define TURNSPEED 2
# define WIDTH 1280
# define HIGTH 1024


/*        Will be removed: to make the work easy        */
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define GREY 0x00A9A9A9
# define BROWN 0x00A52A2A
/*                         ENd                          */


typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

/*----------------------->>> messages <<<------------------------------*/
# define ERROR_COLORS "Error\nNot a valid RGB color\nExample:\"F 220,100,0\" \
\nR,G,B colors in range [0,255]: 0, 255, 255\n"
# define ERROR_PLAYER "Error\nYou have more or less than one player.\n"
# define ERROR_TEXTURE_COLORS "Error\nThe map does not respect the rules.\n"
# define ERROR_MALLOC "Error\nmalloc() failed to allocate some memory\n"
# define ERROR_CLOSED_MAP "Error\nThe map is not closed by walls.\n"


typedef struct s_tools{
	int			i;
	int			j;
	int			k;
	int			l;
	int			box_size;
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
	char		**map;
	char		*str;
	int			len;
	int			x;
	int			y;
	int			player;
	int			ray_index;
	double		horizontal_distance;
	double		vertical_distance;
	double		increment;
	double		ray_angle;
}	t_tools;

typedef struct s_player{
	double		player_pos_x;
	double		player_pos_y;
	double		player_direction;
	int			turn_direction;
	int			walk_direction;
	int 		sideways;
	double		rotate_speed;
	double		walk_speed;

}	t_player;

typedef struct s_texture{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}	t_texture;

typedef struct s_ray{
	double		ray_angle;
	double		horizontal_wall_hit_x;
	double		horizontal_wall_hit_y;
	double		vertical_wall_hit_x;
	double		vertical_wall_hit_y;
	double		distance;
	double		projection_distance;
	int			was_hit_vertical;
	int			is_ray_facing_up;
	int			is_ray_facing_down;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
	char		wall_hit_content;
	int			was_hit_horizontal;
	double		horizontal_wall_hit_distance;
	double		vertical_wall_hit_distance;
}	t_ray;

typedef struct s_stock{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*we;
	char		*no;
	char		*so;
	char		*ea;
	int			window_width;
	int			window_height;
	int			map_width;
	int			map_height;
	int			do_direction_mini_map;
	double		fov;
	double		mini_map_size_box;
	char		**ex_map;
	int			c[3];
	int			f[3];
	t_ray		**rays;
	t_player	*player;
	t_img		*img;
	t_texture	**texture;
	t_texture	**mini_map;
	double		angle;
	int			drawer_x;
}	t_stock;



//---------->>> gnl <<<-----------------

void	*ft_calloc(size_t count, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

/*-------------------- start of parsing functions ----------------------*/

bool	ceiling_and_floor(char **line, t_tools *pars, t_stock *stock);
bool	handle_texture(char **str, t_tools *pars, t_stock *stock);
char	**realloc_map(char **tab, int y, int x);
bool	parsing(char *path, t_stock *stock);
char	*ft_strrchr(const char *s, int c);
int		check_for_valid_keys(char **str);
void	print(char *message, int fd);
bool	check_new_lines(char **map);
bool	check_close(char **tab);
int		get_lenght(char *path);
bool	check_path(char *path);

/*--------------------- end of parsing functions -----------------------*/

/*--------------------- start of libft functions -----------------------*/

char	*ft_strjoin_pro(char *s1, char *s2, int free1, int free2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strcmp(char *s1, char *s2, int free_it);
void	*ft_memset(void *b, int c, size_t len);
char	**ft_split(char *s, char c);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	ft_free(char **strs);
int		ft_atoi(char *str);
int		is_digit(char c);

/*--------------------- end or libft functions -------------------------*/

double	to_radians(double angle);
bool	set_textures(t_stock *stock);
bool	start_the_game(t_stock *stock);
int		key_release(int key, t_stock *stock);
int		key_press(int key, t_stock *stock);
int		update(t_stock *stock);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
bool	set_player(t_stock *stock);
bool	set_mlx(t_stock *stock);
double	get_horizontal_distance(t_stock *stock, double ray_angle, int ray_index);
double	get_vertical_distance(t_stock *stock, double ray_angle, int ray_index);
void	ray_casting(t_stock *stock);
double	normalize_angle(double angle);
void	draw_3d_projection(t_stock *stock);
double	distance(double x1, double y1, double x2, double y2);
void	dda_line(t_stock *stock , double x2, double y2, int color);
void	move_the_player(t_stock *stock);
void	rotate_the_player(t_stock *stock);
void	draw_circle(t_stock *stock, int x_x, int y_y, int wall, int color);
void	draw_floor_and_ceiling(t_stock *stock);
void	draw_mini_map(t_stock *stock);

#endif
