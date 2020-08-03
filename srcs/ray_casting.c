/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:37:33 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:37:36 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	delta_rays_init(t_wolf3d *t)
{
	t->x_deltarays = sqrt(1 + (t->y_directionofrays * t->y_directionofrays) / (t->x_directionofrays * t->x_directionofrays));
	t->y_deltarays = sqrt(1 + (t->x_directionofrays * t->x_directionofrays)	/ (t->y_directionofrays * t->y_directionofrays));
	
	if (t->x_directionofrays < 0)
	{
		t->x_step = -1;
		t->x_siderays = (t->x_positionofrays - t->x_map) * t->x_deltarays;
	}
	else
	{
		t->x_step = 1;
		t->x_siderays = (t->x_map + 1.0 - t->x_positionofrays) * t->x_deltarays;
	}
	if (t->y_directionofrays < 0)
	{
		t->y_step = -1;
		t->y_siderays = (t->y_positionofrays - t->y_map) * t->y_deltarays;
	}
	else
	{
		t->y_step = 1;
		t->y_siderays = (t->y_map + 1.0 - t->y_positionofrays) * t->y_deltarays;
	}
}

void	delta_rays(t_wolf3d *t)
{
	t->hit = 0;
	while (t->hit == 0)
	{
		if (t->x_siderays < t->y_siderays)
		{
			t->x_siderays += t->x_deltarays;
			t->x_map += t->x_step;
			t->side = 0;
		}
		else
		{
			t->y_siderays += t->y_deltarays;
			t->y_map += t->y_step;
			t->side = 1;
		}
		if (t->map[t->x_map][t->y_map] > 0)
			t->hit = 1;
	}
}

void	roof_floor_casting(t_wolf3d *t, int x)
{
	if (t->texture == 0){
		if (t->start > 0)
		{
			t->color = 0x66CCFF;
			t->y = -1;
			
			if (x < WINX && t->y < WINY)
			{
				while (++t->y < t->start)
				{
					ft_memcpy(t->img_ptr + 4 * WINX * t->y + x * 4,&t->color, sizeof(int));
				}
			}
		}
	}
	if (t->end > 0)
	{
		t->color = 0x333333;
		t->y = t->end - 1;
		
		if (x < WINX && t->y < WINY)
		{
			while (++t->y < WINY)
			{
				ft_memcpy(t->img_ptr + 4 * WINX * t->y + x * 4,&t->color, sizeof(int));
			}
		}
	}
}

void	ray_casting_init(t_wolf3d *t, int x)
{
	t->x_cam = 2 * x / (double)(WINX) - 1;
	t->x_positionofrays = t->x_position;
	t->y_positionofrays = t->y_position;
	t->x_directionofrays = t-> x_direction + t-> x_newplane * t->x_cam;
	t->y_directionofrays = t-> y_direction + t-> y_newplane * t->x_cam;
	t->x_map = (int)t->x_positionofrays;
	t->y_map = (int)t->y_positionofrays;
	delta_rays_init(t);
	delta_rays(t);
	if (t->side == 0)
	{
		t->walldistance = (t->x_map - t->x_positionofrays + (1 - t->x_step) / 2) / t->x_directionofrays;
	}
	else
	{
		t->walldistance = (t->y_map - t->y_positionofrays + (1 - t->y_step) / 2) / t->y_directionofrays;
	}
}

void	ray_casting(t_wolf3d *t)
{
	t->x = -1;
	t->img = mlx_new_image(t->mlx, WINX, WINY);
	t->img_ptr = mlx_get_data_addr(t->img, &t->bpp, &t->sl, &t->endian);
	
	if (t->texture == 1)
	{
		sky_creator(t);
	}
	
	while (++t->x < WINX)
	{
		ray_casting_init(t, t->x);
		t->lineheight = (int)(WINY / t->walldistance);
		t->start = -t->lineheight / 2 + WINY / 2;
		
		if (t->start < 0)
		{
			t->start = 0;
		}
		
		t->end = t->lineheight / 2 + WINY / 2;
		
		if (t->end >= WINY)
		{
			t->end = WINY - 1;
		}
		
		if (t->side == 1)
		{
			t->color = 0xdd8800;
		}
		else
		{
			t->color = 0x00FF00;
		}
		
		wall_creator(t->x, t->start - 1, t->end, t);
		roof_floor_casting(t, t->x);
	}
	
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	mlx_destroy_image(t->mlx, t->img);
}
