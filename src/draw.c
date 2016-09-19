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

void	pixelSetThread(t_image_data *data, t_vector vec, int color)
{
	data->addr_image[((int)vec.x * data->bpp / 8)
		+ (int)vec.y * data->size_line] = (color & 0xFF0000) >> 16;
	data->addr_image[((int)vec.x * data->bpp / 8)
		+ (int)vec.y * data->size_line + 1] = (color & 0xFF00) >> 8;
	data->addr_image[((int)vec.x * data->bpp / 8)
		+ (int)vec.y * data->size_line + 2] = (color & 0xFF) >> 0;
}
