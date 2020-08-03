/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:36:35 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:36:38 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		non_game_keys(int keycode, t_wolf3d *t)
{
	if (keycode == 4)
	{
		if (t->help == 0)
		{
			t->help = 1;
		}
		else
		{
			t->help = 0;
		}
	}
	else if (keycode == 17)
	{
		if (t->texture == 0)
		{
			t->texture = 1;
		}
		else
		{
			t->texture = 0;
		}
	}
	return (0);
}

int		game_interaction_keys(int keycode, t_wolf3d *t)
{
	if (keycode == 13 || keycode == 126)
	{
		t->move_up = 1;
	}
	else if (keycode == 1 || keycode == 125)
	{
		t->move_down = 1;
	}
	else if (keycode == 2 || keycode == 124)
	{
		t->move_right = 1;
	}
	else if (keycode == 0 || keycode == 123)
	{
		t->move_left = 1;
	}
	else if (keycode == 257 || keycode == 258)
	{
		t->ms = 0.1;
	}
	else if (keycode == 53)
	{
		exit(1);
	}
	else if (keycode == 117)
	{
		wolf_init(t);
	}
	else
	{
		non_game_keys(keycode, t);
	}
	return (0);
}

int		released_keys(int keycode, t_wolf3d *t)
{
	if (keycode == 13 || keycode == 126)
	{
		t->move_up = 0;
	}
	else if (keycode == 1 || keycode == 125)
	{
		t->move_down = 0;
	}
	else if (keycode == 2 || keycode == 124)
	{
		t->move_right = 0;
	}
	else if (keycode == 0 || keycode == 123)
	{
		t->move_left = 0;
	}
	else if (keycode == 257 || keycode == 258)
	{
		t->ms = 0.05;
	}
	return (0);
}

void	left_right_logic(t_wolf3d *t)
{
	if (t->move_right == 1)
	{
		t->x_originaldirection = t->x_direction;
		t->x_direction = t->x_direction * cos(-t->rs) - t->y_direction * sin(-t->rs);
		t->y_direction = t->x_originaldirection * sin(-t->rs) + t->y_direction * cos(-t->rs);
		t->x_originalplane = t->x_newplane;
		t->x_newplane = t->x_newplane * cos(-t->rs) - t->y_newplane * sin(-t->rs);
		t->y_newplane = t->x_originalplane * sin(-t->rs) + t->y_newplane * cos(-t->rs);
	}
	
	if (t->move_left == 1)
	{
		t->x_originaldirection = t->x_direction;
		t->x_direction = t->x_direction * cos(t->rs) - t->y_direction * sin(t->rs);
		t->y_direction = t->x_originaldirection * sin(t->rs) + t->y_direction * cos(t->rs);
		t->x_originalplane = t->x_newplane;
		t->x_newplane = t->x_newplane * cos(t->rs) - t->y_newplane * sin(t->rs);
		t->y_newplane = t->x_originalplane * sin(t->rs) + t->y_newplane * cos(t->rs);
	}
}

int		movement_logic(t_wolf3d *t)
{
	if (t->move_up == 1)
	{
		if (t->map[(int)(t->x_position + t->x_direction * t->ms)][(int)(t->y_position)] == 0)
		{
			t->x_position += t->x_direction * t->ms;
		}
		if (t->map[(int)(t->x_position)][(int)(t->y_position + t->y_direction * t->ms)] == 0)
		{
			t->y_position += t->y_direction * t->ms;
		}
	}
	
	if (t->move_down == 1)
	{
		if (t->map[(int)(t->x_position - t->x_direction * t->ms)][(int)(t->y_position)] == 0)
		{
			t->x_position -= t->x_direction * t->ms;
		}
		if (t->map[(int)(t->x_position)][(int)(t->y_position - t->y_direction * t->ms)] == 0)
		{
			t->y_position -= t->y_direction * t->ms;
		}
	}
	
	left_right_logic(t);
	ray_casting(t);
	
	if (t->help == 1)
	{
		help_text(t);
	}
	
	return (0);
}
