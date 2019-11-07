/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauranus <cauranus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:04:17 by cauranus          #+#    #+#             */
/*   Updated: 2019/11/07 19:17:12 by cauranus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
#include <stdio.h>
#include "libft/libft.h"

typedef struct 	s_fdf
{
	int 		**map;
	int			len;
	int			height;
}				t_fdf;

#endif