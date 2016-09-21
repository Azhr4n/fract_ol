/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 15:52:41 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/21 15:52:41 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	set_fractal_values(t_var *vars)
{
	int		i;

	i = 0;
	while (i < vars->nb_windows)
	{
		vars->fractals[i].image_value.c.real = DEFAULT_REAL;
		vars->fractals[i].image_value.c.im = DEFAULT_IM;
		vars->fractals[i].image_value.zoom = 1;
		vars->fractals[i].image_value.pos.x = 0;
		if (vars->fractals[i].type == MANDELBROT
			|| vars->fractals[i].type == BUDDHABROT)
			vars->fractals[i].image_value.pos.x = -0.5;
		vars->fractals[i].image_value.pos.y = 0;
		vars->fractals[i].print = 1;
		i++;
	}
}

void	set_constant(t_var *vars, int type, float value)
{
	int		i;

	i = 0;
	while (i < vars->nb_windows)
	{
		if (vars->fractals[i].type == JULIA && i == vars->focus)
		{
			if (type == REAL)
				vars->fractals[i].image_value.c.real += value
					/ vars->fractals[i].image_value.zoom;
			else if (type == IM)
				vars->fractals[i].image_value.c.im += value
					/ vars->fractals[i].image_value.zoom;
			if (type == REAL || type == IM)
				vars->fractals[i].print = 1;
		}
		i++;
	}
}

void	set_zoom(t_var *vars, int type, float value, int id)
{
	if (type == MUL)
		vars->fractals[id].image_value.zoom *= value;
	else if (type == DIV)
		vars->fractals[id].image_value.zoom /= value;
	if (type == MUL || type == DIV)
		vars->fractals[id].print = 1;
}

int		my_mouse_hook(int x, int y, void *param)
{
	t_var		*vars;

	vars = (t_var *)param;
	if ((x - vars->mouse_pos.x) < 0)
		set_constant(vars, REAL, -vars->real_const_val);
	else if ((x - vars->mouse_pos.x) > 0)
		set_constant(vars, REAL, vars->real_const_val);
	if (y - vars->mouse_pos.y < 0)
		set_constant(vars, IM, -vars->im_const_val);
	else if (y - vars->mouse_pos.y > 0)
		set_constant(vars, IM, vars->im_const_val);
	vars->mouse_pos.x = x;
	vars->mouse_pos.y = y;
	return (0);
}

void	change_constant_values(int keycode, t_var *vars)
{
	if (keycode == PLUS)
	{
		if (vars->shift)
			vars->im_const_val += DEFAULT_IM_ADD;
		else
			vars->real_const_val += DEFAULT_REAL_ADD;
	}
	else if (keycode == MINUS)
	{
		if (vars->shift)
		{
			if (vars->im_const_val > DEFAULT_IM_ADD)
				vars->im_const_val -= DEFAULT_IM_ADD;
		}
		else
		{
			if (vars->real_const_val > DEFAULT_REAL_ADD)
				vars->real_const_val -= DEFAULT_REAL_ADD;
		}
	}
	else if (keycode == RESET)
		set_fractal_values(vars);
}
