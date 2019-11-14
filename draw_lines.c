/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:52:48 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/14 20:37:07 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_abs(int a)
{
	return (a < 0 ? -a : a);
}

t_point	*init_point(int x, int y, t_map *map_stat)
{
	t_point	*point;
	
	point = malloc(sizeof(t_point));
	point->x = x;
	point->y = y;
	point->z = map_stat->map[y][x];
	point->h = map_stat->map[y][x];
	return (point);
}

static void	rotate_x(float *y, float *z, double a)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(a) + *z * sin(a);
	*z = -previous_y * sin(a) + *z * cos(a);
}

static void	rotate_y(float *x, float *z, double b)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(b) + *z * sin(b);
	*z = -previous_x * sin(b) + *z * cos(b);
}

//static void	rotate_z(float *x, float *y, double c)
//{
//	int previous_x;
//	int previous_y;
//
//	previous_x = *x;
//	previous_y = *y;
//	*x = previous_x * cos(c) - previous_y * sin(c);
//	*y = previous_x * sin(c) + previous_y * cos(c);
//}

void	iso(float *x, float *y, int z, t_fdf *fdf)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_point	rotate(t_point *p, t_fdf *fdf)
{
		p->x *= fdf->camera->zoom;
		p->y *= fdf->camera->zoom;
		p->z *= fdf->camera->zoom;
		if (fdf->camera->iso == 1)
			iso(&p->x, &p->y, p->z, fdf);
		else
		{
			rotate_x(&p->y, &p->z, fdf->camera->a);
			rotate_y(&p->x, &p->z, fdf->camera->b);
			//rotate_z(&p->x, &p->y, fdf->camera->c);
		}
		p->x += fdf->camera->posx;
		p->y += fdf->camera->posy;
	return (*p);
}

void	draw_line(t_fdf *fdf, t_point s, t_point f)
{
	float		x_step;
	float		y_step;
	int			max;

	x_step = f.x - s.x;
	y_step = f.y - s.y;
	max = ft_abs(x_step) > ft_abs(y_step) ? ft_abs(x_step) : ft_abs(y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(s.x - f.x) || (int)(s.y - f.y))
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, s.x, s.y, (int)f.h || (int)s.h ? 0xffff11 : 0xffffff);
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
				draw_line(fdf, rotate(init_point(x, y, map_stat), fdf), rotate(init_point(x + 1, y, map_stat), fdf));
			if (y < map_stat->height - 1)
				draw_line(fdf, rotate(init_point(x, y, map_stat), fdf), rotate(init_point(x, y + 1, map_stat), fdf));
			x++;
		}
		y++;
	}
}
