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

#include "fract_ol.h"

#include <stdio.h>

static int	iteratingMandelbrot(t_fractal *fractal)
{
	int		i;

	i = 0;
	fractal->values.new.real = 0;
	fractal->values.new.im = 0;
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

void		mandelbrot(void *mlx_core, t_fractal *fractal)
{
	int		i;

	fractal->values.vec.x = 0;
	while (fractal->values.vec.x < WIDTH_WINDOW)
	{
		fractal->values.vec.y = 0;
		while (fractal->values.vec.y < HEIGHT_WINDOW)
		{
			fractal->values.c.real = 1.5 * (fractal->values.vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * fractal->values.zoom * WIDTH_WINDOW) + 0;
			fractal->values.c.im = (fractal->values.vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * fractal->values.zoom * HEIGHT_WINDOW) + 0;
			i = iteratingMandelbrot(fractal);
			pixelSet(mlx_core, fractal, 0x010101 * i);
			fractal->values.vec.y++;
		}
		fractal->values.vec.x++;
	}
	mlx_put_image_to_window(mlx_core, fractal->mlx_window,
		fractal->mlx_image, 0, 0);
	fractal->print = 0;
}
