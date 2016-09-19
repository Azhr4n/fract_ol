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

void	calculateMandelbrot(t_image_data *data, t_image_value value, t_area area, void *ptr)
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
			new.real = 0;
			new.im = 0;
			value.c.real = 1.5 * (vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
			value.c.im = (vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
			i = f(new, value.c);
			color = (0x010000 * (i * 4)) +
				(0x000100 * (i * 10)) + (0x000001 * (i * 100));
			if (i == MAX_ITERATIONS)
				color = 0x000000;
			// if (vec.y == 0 && vec.x > 239)
			// 	printf("vec.x : %f\n", vec.x);
			pixelSetThread(data, vec, color);
		}
	}
}

// void		setDataValues(void ***data, t_fractal *fractal, int *id, int i)
// {
// 	fractal->image_data[*i].addr_image =
// 		mlx_get_data_addr(fractal->mlx_image[*i], &fractal->image_data[*i].bpp,
// 			&fractal->image_data[*i].size_line, &fractal->image_data[*i].endian);
// 	data[i][0] = fractal;
// 	id[i] = i;
// 	data[i][1] = &id[i];
// 	data[i][2] = calculateMandelbrot;
// 	data[i][3] = iteratingMandelbrot;
// }

void		mandelbrot(t_fractal *fractal)
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
		data[i][0] = fractal;
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
