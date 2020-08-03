/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:37:53 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:37:58 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	floor_roof_texture_loader(t_wolf3d *t, int a, int b)
{
	t->texturearray[5].img = mlx_xpm_file_to_image(t->mlx, "textures/sand.xpm", &a, &b);
	t->texturearray[5].data = mlx_get_data_addr(t->texturearray[5].img, &t->texturearray[5].bpp, &t->texturearray[5].sizeline, &t->texturearray[5].endian);
	
	
	a = 512;
	b = 512;
	
	t->texturearray[6].img = mlx_xpm_file_to_image(t->mlx, "textures/sky.xpm", &a, &b);
	t->texturearray[6].data = mlx_get_data_addr(t->texturearray[6].img, &t->texturearray[6].bpp, &t->texturearray[6].sizeline, &t->texturearray[6].endian);
}

void	wall_texture_loader(t_wolf3d *t)
{
	int		a;
	a = 64;
	
	int		b;
	b = 64;

	t->texturearray[0].img = mlx_xpm_file_to_image(t->mlx, "textures/wood.xpm", &a, &b);
	t->texturearray[0].data = mlx_get_data_addr(t->texturearray[0].img, &t->texturearray[0].bpp, &t->texturearray[0].sizeline, &t->texturearray[0].endian);
	
	t->texturearray[1].img = mlx_xpm_file_to_image(t->mlx, "textures/stone.xpm", &a, &b);
	t->texturearray[1].data = mlx_get_data_addr(t->texturearray[1].img, &t->texturearray[1].bpp, &t->texturearray[1].sizeline, &t->texturearray[1].endian);
	
	
	t->texturearray[2].img = mlx_xpm_file_to_image(t->mlx, "textures/mossy.xpm", &a, &b);
	t->texturearray[2].data = mlx_get_data_addr(t->texturearray[2].img, &t->texturearray[2].bpp, &t->texturearray[2].sizeline, &t->texturearray[2].endian);
	
	
	t->texturearray[3].img = mlx_xpm_file_to_image(t->mlx, "textures/redbrick.xpm", &a, &b);
	t->texturearray[3].data = mlx_get_data_addr(t->texturearray[3].img, &t->texturearray[3].bpp, &t->texturearray[3].sizeline, &t->texturearray[3].endian);
	
	
	t->texturearray[4].img = mlx_xpm_file_to_image(t->mlx, "textures/wood.xpm", &a, &b);
	t->texturearray[4].data = mlx_get_data_addr(t->texturearray[4].img, &t->texturearray[4].bpp, &t->texturearray[4].sizeline, &t->texturearray[4].endian);
	
	floor_roof_texture_loader(t, a, b);
}


