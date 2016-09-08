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

#include "fract_ol.h"

#include <stdio.h>

void	pixelSet(t_var *vars, t_vector pos, int color, int index_window)
{
	unsigned int	mlx_color;

	mlx_color = mlx_get_color_value(vars->mlx_core, color);
	vars->addr_images[index_window][(pos.x * vars->bpp / 8) 
		+ pos.y * vars->size_line] = (color & 0xFF0000) >> 16;
	vars->addr_images[index_window][(pos.x * vars->bpp / 8) 
		+ pos.y * vars->size_line + 1] = (color & 0xFF00) >> 8;
	vars->addr_images[index_window][(pos.x * vars->bpp / 8) 
		+ pos.y * vars->size_line + 2] = (color & 0xFF) >> 0;
}
