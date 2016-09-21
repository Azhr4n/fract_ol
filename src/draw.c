/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/08 09:55:35 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/08 09:55:36 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "fract_ol.h"

void	pixel_set_thread(t_image_data *data, t_vector vec, t_vector start,
	int color)
{
	data->addr_image[((int)(vec.x - start.x) * data->bpp / 8)
		+ (int)(vec.y - start.y) * data->size_line] = (color & 0xFF0000) >> 16;
	data->addr_image[((int)(vec.x - start.x) * data->bpp / 8)
		+ (int)(vec.y - start.y) * data->size_line + 1] = (color & 0xFF00) >> 8;
	data->addr_image[((int)(vec.x - start.x) * data->bpp / 8)
		+ (int)(vec.y - start.y) * data->size_line + 2] = (color & 0xFF) >> 0;
}

int		set_color(int iterations, int r, int g, int b)
{
	if (iterations == MAX_ITERATIONS)
		return (0x000000);
	else
		return ((0x010000 * (iterations * r)) +
		(0x000100 * (iterations * g)) + (0x000001 * (iterations * b)));
}
