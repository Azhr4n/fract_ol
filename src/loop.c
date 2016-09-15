/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 15:59:38 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/07 15:59:39 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "fract_ol.h"

#include <stdio.h>

void		setFractalValues(t_var *vars)
{
	int		i;

	i = 0;
	while (i < vars->nb_windows)
	{
		vars->fractals[i].image_data.c.real = DEFAULT_REAL;
		vars->fractals[i].image_data.c.im = DEFAULT_IM;
		vars->fractals[i].image_data.zoom = 1;
		vars->fractals[i].image_data.pos.x = 0;
		if (vars->fractals[i].type == MANDELBROT)
			vars->fractals[i].image_data.pos.x = -0.5;
		vars->fractals[i].image_data.pos.y = 0;
		vars->fractals[i].print = 1;
		i++;
	}
}

void		setConstant(t_var *vars, int type, float value)
{
	int		i;

	i = 0;
	while (i < vars->nb_windows)
	{
		if (vars->fractals[i].type == JULIA && i == vars->focus)
		{
			if (type == REAL)
				vars->fractals[i].image_data.c.real += value 
					/ vars->fractals[i].image_data.zoom;
			else if (type == IM)
				vars->fractals[i].image_data.c.im += value
					/ vars->fractals[i].image_data.zoom;
			if (type == REAL || type == IM)
				vars->fractals[i].print = 1;
		}
		i++;
	}
}

void		setZoom(t_var *vars, int type, float value, int id)
{
	if (type == MUL)
		vars->fractals[id].image_data.zoom *= value;
	else if (type == DIV)
		vars->fractals[id].image_data.zoom /= value;
	if (type == MUL || type == DIV)
		vars->fractals[id].print = 1;
}

static int	myMouseHook(int x, int y, void *param)
{
	t_var		*vars;

	vars = (t_var *)param;

	if ((x - vars->mouse_pos.x) < 0)
		setConstant(vars, REAL, -vars->real_const_val);
	else if ((x - vars->mouse_pos.x) > 0)
		setConstant(vars, REAL, vars->real_const_val);
	if (y - vars->mouse_pos.y < 0)
		setConstant(vars, IM, -vars->im_const_val);
	else if (y - vars->mouse_pos.y > 0)
		setConstant(vars, IM, vars->im_const_val);
	vars->mouse_pos.x = x;
	vars->mouse_pos.y = y;
	return (0);
}

static void	changeConstantValues(int keycode, t_var *vars)
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
		setFractalValues(vars);
}

static int myKeyPressed(int keycode, void *param)
{
	t_var	*vars;

	vars = (t_var *)param;
	if (keycode == UP && vars->dir.y == 0)
		vars->dir.y += -1;
	if (keycode == DOWN && vars->dir.y == 0)
		vars->dir.y += 1;
	if (keycode == LEFT && vars->dir.x == 0)
		vars->dir.x += -1;
	if (keycode == RIGHT && vars->dir.x == 0)
		vars->dir.x += 1;
	if (keycode == SHIFT)
		vars->shift = 1;
	changeConstantValues(keycode, vars);
	return (0);
}

static int myKeyReleased(int keycode, void *param)
{
	t_var	*vars;

	vars = (t_var *)param;
	if (keycode == ESC_KEYCODE)
	{
		cleanVars(vars);
		exit(0);
	}
	if (keycode == UP)
		vars->dir.y = 0;
	if (keycode == DOWN)
		vars->dir.y = 0;
	if (keycode == LEFT)
		vars->dir.x = 0;
	if (keycode == RIGHT)
		vars->dir.x = 0;
	if (keycode == SHIFT)
		vars->shift = 0;
	return (0);
}

static int	myButtonHook(int button, int x, int y, void *param)
{
	void	**tab;
	t_var	*vars;
	int		*id;

	tab = param;
	vars = tab[0];
	id = tab[1];
	if (button == 1)
		vars->focus = *id;
	if (button == 4)
	{
		vars->fractals[*id].image_data.pos.x += ((x - WIDTH_WINDOW / 2)
			/ vars->fractals[*id].image_data.zoom) / 10000;
		vars->fractals[*id].image_data.pos.y += ((y - HEIGHT_WINDOW / 2)
			/ vars->fractals[*id].image_data.zoom) / 10000;
		setZoom(vars, MUL, 1.01, *id);
	}
	else if (button == 6)
		setZoom(vars, MUL, 1.01, *id);
	else if (button == 5)
		setZoom(vars, DIV, 1.01, *id);
	return (1);
}

static int	refresh(void *param)
{
	t_var	*vars;
	int		i;

	vars = (t_var *)param;
	i = 0;
	while (i < vars->nb_windows)
	{
		if (vars->fractals[i].print)
		{
			vars->function_pointers[vars->fractals[i].type]
				(&vars->fractals[i]);
			mlx_put_image_to_window(vars->mlx_core,
				vars->fractals[i].mlx_window,
				vars->fractals[i].mlx_image, 0, 0);
			vars->fractals[i].print = 0;
		}
		i++;
	}
	return (0);
}

void		main_loop(t_var *vars)
{
	int		i;
	int		id[vars->nb_windows];
	void	*tab[vars->nb_windows][2];

	setFractalValues(vars);
	vars->focus = vars->nb_windows;
	i = 0;
	while (i < vars->nb_windows)
	{
		tab[i][0] = vars;
		id[i] = i;
		tab[i][1] = &id[i];
		mlx_mouse_hook(vars->fractals[i].mlx_window, myButtonHook, tab[i]);
		mlx_hook(vars->fractals[i].mlx_window, 6, (1L<<6), myMouseHook, vars);
		mlx_hook(vars->fractals[i].mlx_window, 2, (1L<<0), myKeyPressed, vars);
		mlx_hook(vars->fractals[i].mlx_window, 3,
			(1L<<1), myKeyReleased, vars);
		i++;
	}
	mlx_loop_hook(vars->mlx_core, refresh, vars);
	mlx_loop(vars->mlx_core);
}
