/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmoud <moulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:18:28 by moulmoud          #+#    #+#             */
/*   Updated: 2023/06/06 23:44:58 by moulmoud         ###   ########.fr       */
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
# define FOV 60 // field of view
# define WALL_STRIP_WITH 1 // this is the size of the rectangle.
# define MINI_MAP_BOX_ZIZE 64 // you can change this to what ever you want to controle the size of the mini map.
# define SPEED 7
# define TURNSPEED 1
/*        Will be removed: to make the work easy        */

# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define GREY 0x00A9A9A9

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

# define WIDTH 1024
# define HIGTH 1024

typedef struct s_pars{
	int		i;
	int		j;
	int		box_size;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
	char	**map;
	char	*str;
	int		len;
	int		x;
	int		y;
	int		player;
}	t_pars;

typedef struct s_player{
	double	player_pos_x;
	double	player_pos_y;
	double	player_angle;
	int		turn_direction;// 0; idle -1: turn left 1: turn right.
	int		walk_direction;// 0 : is not walking 1: walking right -1: walking left.
	double	rotate_speed;
	double	walk_speed;

}	t_player;

typedef struct s_stock{
	void		*mlx_ptr;
	void		*win_ptr;
	char		*we;
	char		*no;
	char		*so;
	char		*ea;
	int			window_width;
	int			window_height;
	double		fov;
	double		mini_map_size_box;
	char		**ex_map;
	int			c[3];
	int			f[3];
	t_player	*player;
	t_img		*img;
	double		angle;
	int			drawer_x;
}	t_stock;



//---------->>> gnl <<<-----------------

void	*ft_calloc(size_t count, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

/*-------------------- start of parsing functions ----------------------*/

bool	ceiling_and_floor(char **line, t_pars *pars, t_stock *stock);
bool	handle_texture(char **str, t_pars *pars, t_stock *stock);
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

bool	start_the_game(t_stock *stock);
int		key_release(int key, t_stock *stock);
int		key_press(int key, t_stock *stock);
int		update(t_stock *stock);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
#endif
