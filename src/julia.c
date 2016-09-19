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

#include "fract_ol.h"

int	iteratingJulia(t_complex new, t_complex c)
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
		if ((new.real * new.real) + (new.im * new.im) > 4)
			break;
		i++;
	}
	return (i);
}

void	calculateJulia(t_image_data *data, t_image_value *value, t_area area, void *ptr)
{
	t_vector	vec;
	t_complex	new;
	int			i;
	int			color;
	int			(*f)(t_complex, t_complex);

	f = ptr;
	vec.x = area.start.x - 1;
	while (++vec.x < area.end.x)
	{
		vec.y = area.start.y - 1;
		while (++vec.y < area.end.y)
		{
			new.real = 1.5 * (vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * value->zoom * WIDTH_WINDOW) + value->pos.x;
			new.im = (vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * value->zoom * HEIGHT_WINDOW) + value->pos.y;
			i = f(new, value->c);
			color = (0x010000 * (i * 4)) +
				(0x000100 * (i * 2)) + (0x000001 * (i * 3));
			if (i == MAX_ITERATIONS)
				color = 0x000000;
			pixelSetThread(data, vec, color);
		}
	}
}

void		julia(t_fractal *fractal)
{
	pthread_t	pt[NB_THREADS];
	void		*data[NB_THREADS][4];
	void		*ret;
	int			id[NB_THREADS];
	int			i;

	i = -1;
	while (++i < NB_THREADS)
	{
		fractal->image_data[i].addr_image =
			mlx_get_data_addr(fractal->mlx_image[i], &fractal->image_data[i].bpp,
				&fractal->image_data[i].size_line, &fractal->image_data[i].endian);
		data[i][0] = &fractal->image_data;
		id[i] = i;
		data[i][1] = &id[i];
		data[i][2] = calculateJulia;
		data[i][3] = iteratingJulia;
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
