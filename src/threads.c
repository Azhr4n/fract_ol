/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/13 12:40:55 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/13 12:40:55 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fract_ol.h"

#include <stdio.h>

static void	threadFunctionNext(void **data, t_fractal *fractal,
	t_area area, int *id)
{
	void	(*f)(t_image_data *, t_image_value, t_area, int (*)(t_complex, t_complex));

	f = data[2];
	f(&fractal->image_data[*id], fractal->image_value, area, data[3]);
}

void		*threadFunction(void *packed_data)
{
	void			**data;
	t_fractal		*fractal;
	t_area			area;
	int				*id;

	data = packed_data;
	fractal = data[0];
	id = data[1];
	area.start.x = *id * (WIDTH_WINDOW / NB_THREADS);
	area.start.y = 0;
	area.end.x = area.start.x + (WIDTH_WINDOW / NB_THREADS);
	area.end.y = HEIGHT_WINDOW;
	threadFunctionNext(data, fractal, area, id);
	return (NULL);
}

// void		*threadFunctionBuddha(void *packed_data)
// {
// 	void			**data;
// 	t_image_data	*image_data;
// 	int				*id;
// 	t_area			area;

// 	data = packed_data;
// 	image_data = data[0];
// 	id = data[1];
// 	area.start.x = *id * (WIDTH_WINDOW / NB_THREADS);
// 	area.start.y = 0;
// 	area.end.x = area.start.x + (WIDTH_WINDOW / NB_THREADS);
// 	area.end.y = HEIGHT_WINDOW;
// 	threadFunctionNext(data, image_data, area);
// 	return (NULL);
// }