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

#include "fract_ol.h"
#include "libft.h"

#include <stdio.h>

void	calculateMandelbrot(t_var *vars, t_complex c, float zoom, int index_window)
{
	t_complex	old;
	t_complex	new;
	t_vector	pos;
	int			i;

	pos.x = 0;
	while (pos.x < WIDTH_WINDOW)
	{
		pos.y = 0;
		while (pos.y < HEIGHT_WINDOW)
		{
			c.real = 1.5 * (pos.x - WIDTH_WINDOW / 2) / (0.5 * zoom + WIDTH_WINDOW) + 0;
			c.im = (pos.y - HEIGHT_WINDOW / 2) / (0.5 * zoom + HEIGHT_WINDOW) + 0;
			new.real = 0;
			new.im = 0;
			i = 0;
			while (i < MAX_ITERATIONS)
			{
				old.real = new.real;
				old.im = new.im;
				new.real = old.real * old.real - old.im * old.im + c.real;
				new.im = 2 * old.real * old.im + c.im;
				if ((new.real * new.real + new.im * new.im) > 4)
					break;
				i++;
			}
			pixelSet(vars, pos, 0x010101 * i, index_window);
			pos.y++;
		}
		pos.x++;
	}
}

void	mandelbrot(void *data)
{
	t_var		*vars;
	int			index;

	ft_putendl("MNADE");
	vars = (t_var *)data;
	index = getIndexFocus(vars->focus, vars->nb_windows, MANDELBROT);
	vars->mlx_windows[index] = mlx_new_window(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW, "Mandelbrot");
	vars->mlx_images[index] = mlx_new_image(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW);
	vars->addr_images[index] = mlx_get_data_addr(
		vars->mlx_images[index],&vars->bpp,
		&vars->size_line, &vars->endian);
	calculateMandelbrot(vars, vars->fractal_values[index].c, vars->fractal_values[index].zoom, index);
	mlx_put_image_to_window(vars->mlx_core, vars->mlx_windows[index], vars->mlx_images[index], 0, 0);
	ft_putendl("END");
}

