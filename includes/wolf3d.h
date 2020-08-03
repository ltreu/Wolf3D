/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:34:06 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:35:00 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# define WINX 1024
# define WINY 768
# define USAGE "usage: wolf3d \"map\"\n"

typedef struct	s_texture
{
	void		*img;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}				t_texture;

typedef struct	s_wolf3d
{
	t_texture	texturearray[9];
	char		*map_name;
	void		*mlx;
	void		*win;
	void		*img;
	void		*img_ptr;
	int			**map;
	int			main_lines;
	int			length_line;
	int			bpp;
	int			endian;
	int			sl;
	int			x_map;
	int			y_map;
	int			x_step;
	int			y_step;
	int			hit;
	int			side;
	int			lineheight;
	int			start;
	int			end;
	int			color;
	int			help;
	int			x_text;
	int			y_text;
	int			id;
	int			texture;
	int			x_floortext;
	int			y_floortext;
	int			move_up;
	int			move_down;
	int			move_left;
	int			move_right;
	int			x;
	int			y;
	double		ms;
	double		rs;
	double		x_position;
	double		y_position;
	double		x_direction;
	double		y_direction;
	double		x_newplane;
	double		y_newplane;
	double		x_cam;
	double		x_positionofrays;
	double		y_positionofrays;
	double		x_directionofrays;
	double		y_directionofrays;
	double		x_siderays;
	double		y_siderays;
	double		x_deltarays;
	double		y_deltarays;
	double		walldistance;
	double		x_originaldirection;
	double		x_originalplane;
	double		x_wall;
	double		x_floor;
	double		y_floor;
	double		x_curfloortext;
	double		y_curfloortext;
	double		curdist;
	double		weight;
}				t_wolf3d;

void			mlx_win_init(t_wolf3d *t);
void			wolf_init(t_wolf3d *t);
int				ft_close_wolf(void);

int				map_checker(char *buffer, t_wolf3d *t);
int				file_parser(t_wolf3d *t, char **av);
int				line_parser(t_wolf3d *t, char **av);

void			delta_rays_init(t_wolf3d *t);
void			delta_rays(t_wolf3d *t);
void			roof_floor_casting(t_wolf3d *t, int x);
void			ray_casting_init(t_wolf3d *t, int x);
void			ray_casting(t_wolf3d *t);

void			wall_creator(int x, int start, int end, t_wolf3d *t);
void			sky_creator(t_wolf3d *t);
void			floor_creator(t_wolf3d *t);
void			convert_image(t_wolf3d *t, int x, int y, int color);

void			help_text(t_wolf3d *t);

void			wall_texture_loader(t_wolf3d *t);
void			floor_roof_texture_loader(t_wolf3d *t, int a, int b);

int				non_game_keys(int keycode, t_wolf3d *t);
int				game_interaction_keys(int keycode, t_wolf3d *t);
int				released_keys(int keycode, t_wolf3d *t);
void			left_right_logic(t_wolf3d *t);
int				movement_logic(t_wolf3d *t);

#endif
