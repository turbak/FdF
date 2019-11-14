/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:52:48 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/14 14:19:48 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_abs(int a)
{
	return (a < 0 ? -a : a);
}

t_point	init_point(int x, int y, t_map *map_stat, t_fdf *fdf)
{
	t_point	point;
	
	point.x = x * fdf->camera->zoom;
	point.y = y * fdf->camera->zoom;
	point.z = map_stat->map[y][x] * fdf->camera->zoom;
	return (point);
}

void	iso(float *x, float *y, int z, t_fdf *fdf)
{
	*x = (*x - *y) * cos(fdf->camera->anglex);
	*y = (*x + *y) * sin(fdf->camera->angley) - z;
}

void	draw_line(t_fdf *fdf, t_point s, t_point f)
{
	float		x_step;
	float		y_step;
	int		max;

	iso(&s.x, &s.y, s.z, fdf);
	iso(&f.x, &f.y, f.z, fdf);
	s.x += fdf->camera->posx;
	s.y += fdf->camera->posy;
	f.x += fdf->camera->posx;
	f.y += fdf->camera->posy;
	x_step = f.x - s.x;
	y_step = f.y - s.y;
	max = ft_abs(x_step) > ft_abs(y_step) ? ft_abs(x_step) : ft_abs(y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(s.x - f.x) || (int)(s.y - f.y))
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, s.x, s.y, 0xffffff);
		s.x += x_step;
		s.y += y_step;
	}
}

void	draw(t_map *map_stat, t_fdf *fdf)
{
	int x;
	int y;
	
	y = 0;
	while (y < map_stat->height)
	{
		x = 0;
		while (x < map_stat->width)
		{
			if (x < map_stat->width - 1)
				draw_line(fdf, init_point(x, y, map_stat, fdf), init_point(x + 1, y, map_stat, fdf));
			if (y < map_stat->height - 1)
				draw_line(fdf, init_point(x, y, map_stat, fdf), init_point(x, y + 1, map_stat, fdf));
			x++;
		}
		y++;
	}
}
