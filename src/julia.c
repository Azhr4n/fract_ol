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

int		iterating_julia(t_complex new, t_complex c)
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
			break ;
		i++;
	}
	return (i);
}

void	calculate_julia(t_image_data *data, t_image_value value, void *ptr)
{
	int		(*f)(t_complex, t_complex);

	f = ptr;
	value.vec.x = value.area.start.x - 1;
	while (++value.vec.x < value.area.end.x)
	{
		value.vec.y = value.area.start.y - 1;
		while (++value.vec.y < value.area.end.y)
		{
			value.new.real = 1.5 * (value.vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
			value.new.im = (value.vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
			pixel_set_thread(data, value.vec, value.area.start,
				set_color(f(value.new, value.c), 4, 2, 3));
		}
	}
}

void	julia(t_fractal *fractal)
{
	t_thread	thread;
	void		*data[NB_THREADS][4];
	int			i;

	i = -1;
	while (++i < NB_THREADS)
	{
		fractal->image_data[i].addr_image =
			mlx_get_data_addr(fractal->mlx_image[i], ABPP, ASL, AEN);
		data[i][0] = fractal;
		thread.id[i] = i;
		data[i][1] = &(thread.id[i]);
		data[i][2] = calculate_julia;
		data[i][3] = iterating_julia;
		if ((pthread_create(&(thread.pt[i]), 0, thread_func, data[i])) != 0)
			exit(-1);
	}
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_join(thread.pt[i], &(thread.ret[i])) != 0)
			exit(-1);
}
