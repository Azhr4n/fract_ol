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

static void	threadFunctionNext(void **data, t_image_data *image_data,
	t_area area)
{
	int		(*f_ptr)(t_complex, t_complex);
	void	(*f)(t_image_data *, t_area, int (*)(t_complex, t_complex));

	f = data[2];
	f_ptr = data[3];
	f(image_data, area, f_ptr);
}

void		*threadFunction(void *packed_data)
{
	void			**data;
	t_image_data	*image_data;
	int				*id;
	t_area			area;

	data = packed_data;
	image_data = data[0];
	id = data[1];
	area.start.x = *id % (NB_THREADS / 2) * (WIDTH_WINDOW / (NB_THREADS / 2));
	area.start.y = *id / (NB_THREADS / 2) * (HEIGHT_WINDOW / 2);
	area.end.x = area.start.x + (WIDTH_WINDOW / (NB_THREADS / 2));
	area.end.y = area.start.y + (HEIGHT_WINDOW / 2);
	threadFunctionNext(data, image_data, area);
	return (NULL);
}
