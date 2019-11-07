/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:13:34 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/07 19:24:02 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	**char_to_arr(char **grid, t_fdf map_stat)
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
		map_stat.len = 0;
		str = ft_strsplit(grid[i], ' ');
		while (str[map_stat.len])
			map_stat.len++;
		map[i] = (int *)malloc(sizeof(int) * map_stat.len);
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
}

t_fdf	line_num(char **av)
{
	t_fdf map_stat;
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

int	**get_map(char **av)
{
	int fd;
	char *line;
	char **grid;
	t_fdf	map_stat;

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

int main(int ac, char **av)
{
	void	*mlx_ptr;
	int 	**map;

	//mlx_ptr = mlx_init();
	map = get_map(av);
	//mlx_new_window(mlx_ptr, 1000, 1000, "mlx_test");
	//mlx_loop(mlx_ptr);
	return (0);
}