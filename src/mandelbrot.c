/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 16:30:40 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/08 16:30:43 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <pthread.h>

#include "fract_ol.h"

#include <stdio.h>
#include <unistd.h>

int	iteratingMandelbrot(t_complex new, t_complex c)
{
	t_complex	old;
	int			i;

	i = 0;
	while (i < MAX_ITERATIONS)
	{
		old.real = new.real;
		old.im = new.im;
		new.real = (old.real * old.real) - (old.im * old.im) + c.real;
		new.im = 2 * old.real * old.im + c.im;
		if (new.real * new.real + new.im * new.im > 4)
			break;
		i++;
	}
	return (i);
}

void	calculateMandelbrot(t_image_data *data, t_area area,
	int (*f)(t_complex, t_complex))
{
	t_vector	vec;
	t_complex	new;
	int			i;
	int			color;

	vec.x = area.start.x;
	while (vec.x < area.end.x)
	{
		vec.y = area.start.y;
		while (vec.y < area.end.y)
		{
			new.real = 0;
			new.im = 0;
			data->c.real = 1.5 * (vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * data->zoom * WIDTH_WINDOW) + data->pos.x;
			data->c.im = (vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * data->zoom * HEIGHT_WINDOW) + data->pos.y;
			i = f(new, data->c);
			color = (0x010000 * (i % 0xFF)) +
				(0x000100 * (i % 0xFF)) + (0x000001 * (i % 0xFF));
			pixelSetThread(data, vec, color);
			vec.y++;
		}
		vec.x++;
	}
}

void		mandelbrot(t_fractal *fractal)
{
	pthread_t	pt[NB_THREADS];
	void		*data[NB_THREADS][4];
	void		*ret;
	int			id[NB_THREADS];
	int			i;

	fractal->image_data.addr_image =
		mlx_get_data_addr(fractal->mlx_image, &fractal->image_data.bpp,
			&fractal->image_data.size_line, &fractal->image_data.endian);
	i = -1;
	while (++i < NB_THREADS)
	{
		data[i][0] = &fractal->image_data;
		id[i] = i;
		data[i][1] = &id[i];
		data[i][2] = calculateMandelbrot;
		data[i][3] = iteratingMandelbrot;
		if ((pthread_create(&pt[i], NULL, threadFunction, data[i])) != 0)
			exit(-1);
	}
	i = -1;
	while (++i < NB_THREADS)
	{
		if (pthread_join(pt[i], &ret) != 0)
			exit(-1);
	}
}
