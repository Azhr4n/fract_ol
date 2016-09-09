/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 16:52:23 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/07 16:52:23 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <pthread.h>

#include <stdio.h>

#include "fract_ol.h"

static int	iteratingJulia(t_fractal *fractal)
{
	int		i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		fractal->values.old.real = fractal->values.new.real;
		fractal->values.old.im = fractal->values.new.im;
		fractal->values.new.real = fractal->values.old.real * fractal->values.old.real
			- fractal->values.old.im * fractal->values.old.im + fractal->values.c.real;
		fractal->values.new.im = 2 * fractal->values.old.real * fractal->values.old.im + fractal->values.c.im;
		if ((fractal->values.new.real * fractal->values.new.real
			+ fractal->values.new.im * fractal->values.new.im) > 4)
			break;
		i++;
	}
	return (i);
}

static void calculateJulia(void *mlx_core, t_fractal *fractal, t_area area)
{
	int		i;
	int		x;
	int		y;

	x = area.start.x;
	while (x < area.end.x)
	{
		y = area.start.y;
		while (y < area.end.y)
		{
			fractal->values.new.real = 1.5 * (x - WIDTH_WINDOW / 2)
				/ (0.5 * fractal->values.zoom * WIDTH_WINDOW) + 0;
			fractal->values.new.im = (y - HEIGHT_WINDOW / 2)
				/ (0.5 * fractal->values.zoom * HEIGHT_WINDOW) + 0;
			i = iteratingJulia(fractal);
			pixelSet(mlx_core, fractal, 0x010101 * i);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx_core, fractal->mlx_window,
		fractal->mlx_image, 0, 0);
}

static void	*presetJulia(void *data)
{
	void		**tab;
	void		*mlx_core;
	t_fractal	*fractal;
	t_area		area;
	int			*id;

	tab = data;
	mlx_core = tab[0];
	fractal = tab[1];
	id = tab[2];

	area.start.x = *id % (NB_THREADS / 2) * (WIDTH_WINDOW / (NB_THREADS / 2));
	area.start.y = *id / (NB_THREADS / 2) * (HEIGHT_WINDOW / 2);
	area.end.x = area.start.x + (WIDTH_WINDOW / (NB_THREADS / 2));
	area.end.y = area.start.y + (HEIGHT_WINDOW / 2);

	printf("id : %p\n", id);
	// printf("start_x : %d\n", area.start.x);
	// printf("start_y : %d\n", area.start.y);
	// printf("end_x : %d\n", area.end.x);
	// printf("end_y : %d\n", area.end.y);

	exit(1);
	calculateJulia(mlx_core, fractal, area);
	return (NULL);
}



static void	launchThread(pthread_t **pt, void *data[4])
{
	int			i;
	int			id[NB_THREADS][1];

	i = 0;
	while (i < NB_THREADS)
	{
		tab[i][0] = i;
		data[2] = tab[i];
		if (pthread_create(pt[i], NULL, presetJulia, data) != 0)
		{
			ft_putendl("Thread launching failed.");
			exit(-1);
		}
		i++;
	}
}

void		julia(void *mlx_core, t_fractal *fractal)
{
	pthread_t	*pt;
	void		*ret;
	void		*data[3];
	int			i;


	pt = (pthread_t *)malloc(sizeof(pthread_t) * NB_THREADS);

	data[0] = mlx_core;
	data[1] = fractal;
	launchThread(&pt, data);
	i = 0;
	while (i < NB_THREADS)
	{
		pthread_join(pt[i], &ret);
		i++;
	}
	free(pt);
	exit(1);
	fractal->print = 0;
}
