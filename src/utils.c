/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:55:47 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/21 14:55:48 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "fract_ol.h"

void	free2d_int(int **tab, int width)
{
	int		i;

	i = -1;
	while (++i < width)
		free(tab[i]);
	free(tab);
}

void	str_lower(char *str)
{
	while (*str != 0)
	{
		*str = (char)ft_tolower(*str);
		str++;
	}
}

int		**allocate_color_map(int width, int height)
{
	int		**color_map;
	int		i;
	int		j;

	if ((color_map = (int **)malloc(sizeof(int *) * width)) == NULL)
	{
		ft_putendl("Failed to malloc.");
		exit(-1);
	}
	i = -1;
	while (++i < width)
	{
		if ((color_map[i] = (int *)malloc(sizeof(int) * height)) == NULL)
		{
			ft_putendl("Failed to malloc.");
			exit(-1);
		}
		j = -1;
		while (++j < height)
			color_map[i][j] = 0;
	}
	return (color_map);
}

void	set_buddha_values(t_image_value value, t_complex *c, t_complex *new)
{
	t_vector	vec;

	vec.x = rand() % (int)(WIDTH_WINDOW);
	vec.y = rand() % (int)(HEIGHT_WINDOW);
	new->real = 0;
	new->im = 0;
	c->real = CX(vec.x) + value.pos.x;
	c->im = CY(vec.y) + value.pos.y;
}
