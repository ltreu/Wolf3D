/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltreu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 09:37:23 by ltreu             #+#    #+#             */
/*   Updated: 2018/09/20 09:37:26 by ltreu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		map_checker(char *buffer, t_wolf3d *t)
{
	int		i;
	i = 0;
	
	int		length_variable;
	length_variable = 0;
	
	t->length_line = ft_linelen(buffer);
	t->main_lines = ft_countlines(buffer);
	
	while (buffer[i] && buffer[i] != '\0')
	{
		if ((buffer[i] < 48 || buffer[i] > 57) && buffer[i] != ' ' && buffer[i] != '\n')
		{
			return (0);
		}
		
		length_variable++;
		
		if (buffer[i] == '\n')
		{
			if (length_variable - 1 != t->length_line)
			{
				return (0);
			}
			length_variable = 0;
		}
		
		i++;
	}
	return (1);
}

int		map_side_checker(t_wolf3d *t)
{
	int		i;
	i = 0;
	
	while (i < t->length_line)
	{
		if (t->map[0][i] == 0)
		{
			return (0);
		}
		
		if (t->map[t->main_lines - 1][i] == 0)
		{
			return (0);
		}
		i++;
	}
	
	i = 0;
	
	while (i < t->main_lines)
	{
		if (t->map[i][0] == 0)
		{
			return (0);
		}
		if (t->map[i][t->length_line - 1] == 0)
		{
			return (0);
		}
		i++;
	}
	if (t->map[3][3] != 0)
	{
		return (0);
	}
	return (1);
}

int		line_parser(t_wolf3d *t, char **av)
{
	int		i;
	i = 0;
	
	int		j;
	j = -1;
	
	int		k;
	k = 0;
	
	int		fd;
	fd = open(av[1], O_RDONLY);
	
	char	*stringarr;

	while (ft_get_next_line(fd, &stringarr) > 0)
	{
		if (!(t->map[i] = (int *)malloc(sizeof(int) * t->length_line)))
		{
			return (0);
		}
		while (++j < t->length_line)
		{
			if (stringarr[k] == ' ')
			{
				k++;
			}
			
			t->map[i][j] = ft_atoi(&stringarr[k]);
			k++;
		}
		
		i++;
		free(stringarr);
	}
	return (1);
}

int		file_parser(t_wolf3d *t, char **av)
{
	int		fd;
	fd = open(av[1], O_RDONLY);
	
	char	*buffer;
	buffer = ft_strnew(65536);
	
	int		i;
	i = 0;

	if (fd < 0 || (read(fd, buffer, 65536)) < 1)
	{
		ft_putstr("wolf3d: ");
		ft_putstr(av[1]);
		ft_putstr(": No such file\n");
		return (0);
	}
	if (!(map_checker(buffer, t)))
	{
		ft_putstr("Map error\n");
		return (0);
	}
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		if (buffer[i] == ' ')
		{
			t->length_line--;
		}
		i++;
	}
	
	ft_strdel(&buffer);
	t->map_name = av[1];
	close(fd);
	if (!(t->map = (int **)malloc(sizeof(int *) * t->main_lines)) || !(line_parser(t, av)))
	{
		return (0);
	}
	if (!map_side_checker(t))
	{
		ft_putstr("Map error\n");
		return (0);
	}
	return (1);
}
