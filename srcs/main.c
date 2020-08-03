/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:37:07 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:37:11 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	mlx_win_init(t_wolf3d *t)
{
	char	*title;

	title = ft_strjoin("Wolf3d : ", t->map_name);
	t->mlx = mlx_init();
	t->win = mlx_new_window(t->mlx, WINX, WINY, title);
	ft_strdel(&title);
}

void	wolf_init(t_wolf3d *t)
{
	t->ms = 0.05;
	t->rs = 0.05;
	t->x_position = 3;
	t->y_position = 3;
	t->x_direction = -1;
	t->y_direction = 0;
	t->x_newplane = 0;
	t->y_newplane = 0.66;
	t->move_up = 0;
	t->move_down = 0;
	t->move_left = 0;
	t->move_right = 0;
	t->x_text = 0;
	t->y_text = 0;
	wall_texture_loader(t);
}

int		ft_close_wolf(void)
{
	exit(1);
	return (0);
}

int		main(int ac, char **av)
{
	t_wolf3d *t;

	if (ac != 2)
	{
		ft_putstr(USAGE);
		return (0);
	}
	if (!(t = (t_wolf3d *)malloc(sizeof(t_wolf3d))))
	{
		return (0);
	}
	if (!(file_parser(t, av)))
	{
		return (0);
	}
	mlx_win_init(t);
	mlx_hook(t->win, 17, 0L, ft_close_wolf, t);
	mlx_hook(t->win, 2, (1L << 0), game_interaction_keys, t);
	mlx_hook(t->win, 3, (1L << 1), released_keys, t);
	t->help = 1;
	wolf_init(t);
	ray_casting(t);
	mlx_loop_hook(t->mlx, movement_logic, t);
	mlx_loop(t->mlx);
}
