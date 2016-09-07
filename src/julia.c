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

#include "fract_ol.h"

void	julia(void *data)
{
	t_var	*vars;

	vars = (t_var *)data;
	vars->mlx_windows[vars->max_window] = mlx_new_window(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW, "Julia");
	vars->mlx_images[vars->max_window] = mlx_new_image(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW);
	vars->addr_images[vars->max_window] = mlx_get_data_addr(
		vars->mlx_images[vars->max_window],&vars->bpp,
		&vars->size_line, &vars->endian);
	vars->max_window++;
}

void	calculateJulia(t_var *vars)
{
	t_complex	c;
	t_complex	old;
	t_complex	new;
	int			x;
	int			y;
	int			i;

	c.real = 0;
	c.im = 0.25
	x = 0;
	while (x < WIDTH_WINDOW)
	{
		y = 0;
		while (y < HEIGHT_WINDOW)
		{
			new.real = 1.5 * (x - WIDTH_WINDOW / 2) / (0.5 * WIDTH_WINDOW) + 0;
			new.im = (y - HEIGHT_WINDOW / 2) / (0.5 * 1 * HEIGHT_WINDOW) + 0;

			i = 0;
			while (i < vars->max_iterations)
			{
				old.read = new.real;
				old.im = new.im;
				new.real = old.real * old.real - old.im * old.im + c.real;
				new.im = 2 * old.real * old.im + c.im;
				if ((new.real * new.real + new.im * new.im) > 4)
					break;
				i++;
			}
			y++;
		}
		x++;
	}

}
