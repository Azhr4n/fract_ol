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

void	pixelSet(void *mlx_core, t_fractal *fractal, int color)
{
	unsigned int	mlx_color;

	mlx_color = mlx_get_color_value(mlx_core, color);
	fractal->addr_image[(fractal->values.vec.x * fractal->bpp / 8) 
		+ fractal->values.vec.y * fractal->size_line] = (color & 0xFF0000) >> 16;
	fractal->addr_image[(fractal->values.vec.x * fractal->bpp / 8) 
		+ fractal->values.vec.y * fractal->size_line + 1] = (color & 0xFF00) >> 8;
	fractal->addr_image[(fractal->values.vec.x * fractal->bpp / 8) 
		+ fractal->values.vec.y * fractal->size_line + 2] = (color & 0xFF) >> 0;
}
