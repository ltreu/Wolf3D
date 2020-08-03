/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:36:46 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:37:00 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	help_text(t_wolf3d *t)
{
	mlx_string_put(t->mlx, t->win, 10, 5, 0xEEEEEE, "Move with W A S D or Arrows."); 
	
	mlx_string_put(t->mlx, t->win, 10, 25, 0xEEEEEE, "Sprint with SHIFT.");
	
	mlx_string_put(t->mlx, t->win, 10, 45, 0xEEEEEE, "Textures on or off with T.");
	
	mlx_string_put(t->mlx, t->win, 10, 65, 0xEEEEEE, "Level reset with Del.");
	
	mlx_string_put(t->mlx, t->win, 10, 85, 0xEEEEEE, "Help text with H");
	
	mlx_string_put(t->mlx, t->win, 10, 105, 0xEEEEEE, "Quit with ESC.");
}
