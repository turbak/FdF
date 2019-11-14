/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:13:34 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/14 14:14:36 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	char_to_arr(char **grid, t_map map_stat)
{
	int **map;
	int i;
	char **str;
	int j;

	i = 0;
	map = (int **)malloc(sizeof(int *) * map_stat.height);
	while (grid[i])
	{
		j = 0;
		map_stat.width = 0;
		str = ft_strsplit(grid[i], ' ');
		while (str[map_stat.width])
			map_stat.width++;
		map[i] = (int *)malloc(sizeof(int) * map_stat.width);
		while (str[j])
		{
			map[i][j] = ft_atoi(str[j]);
			ft_strdel(&str[j]);
			j++;
		}
		free(str);
		i++;
	}
	map[i] = NULL;
	map_stat.map = map;
	return (map_stat);
}

t_map	line_num(char **av)
{
	t_map map_stat;
	int fd;
	char *line;

	map_stat.height = 0;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_strdel(&line);
		map_stat.height++;
	}
	close(fd);
	return (map_stat);
}

t_map get_map(char **av)
{
	int fd;
	char *line;
	char **grid;
	t_map	map_stat;

	map_stat = line_num(av);
	grid = (char **)malloc(sizeof(char *) * map_stat.height + 1);
	fd = open(av[1], O_RDONLY);
	map_stat.height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		grid[map_stat.height] = ft_strdup(line);
		ft_strdel(&line);
		map_stat.height++;
	}
	grid[map_stat.height] = NULL;
	map_stat = line_num(av);
	close(fd);
	return (char_to_arr(grid, map_stat));
}


int	controls(int key, void *fdf1)
{
	t_fdf *fdf;
	
	fdf = (t_fdf *)fdf1;
	if (key == MAIN_PAD_ESC)
	{
		(void)fdf;
		exit(0);
	}
	if (key == NUM_PAD_6)
	{
		fdf->camera->posx += 10;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_8)
	{
		fdf->camera->posy -= 10;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_4)
	{
		fdf->camera->posx -= 10;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_2)
	{
		fdf->camera->posy += 10;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_PLUS)
	{
		fdf->camera->zoom += 0.3;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_MINUS)
	{
		fdf->camera->zoom -= 0.3;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_7)
	{
		fdf->camera->anglex += 0.05;
		fdf->camera->angley -= 0.05;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	if (key == NUM_PAD_1)
	{
		fdf->camera->angley -= 0.05;
		fdf->camera->anglex -= 0.05;
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		draw(fdf->map, fdf);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_fdf 	*fdf;

	fdf = malloc(sizeof(t_fdf));
	fdf->camera = malloc(sizeof(t_camera));
	fdf->camera->posx = 300;
	fdf->camera->posy = 150;
	fdf->map = malloc(sizeof(t_map));
	fdf->mlx_ptr = mlx_init();
	*fdf->map = get_map(av);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, 1500, 1500, "mlx_test");
	//mlx_hook(fdf->win_ptr, 2, 0, controls, fdf);
	mlx_key_hook(fdf->win_ptr, controls, fdf);
	fdf->camera->zoom = 70;
	fdf->camera->anglex = 0.8;
	fdf->camera->angley = 0.8;
	draw(fdf->map, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}