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

static int	myMouseHook(int x, int y, void *param)
{
	t_var		*vars;
	static int	old_x = 0;
	static int	old_y = 0;
	int			recalc;

	vars = (t_var *)param;
	if (old_x == 0)
		old_x = x;
	if (old_y == 0)
		old_y = y;
	recalc = 0;
	if ((old_x - x < 0) || (old_x - x > 0) || (old_y - y < 0) || (old_y + y > 0))
		recalc = 1;
	if (old_x - x < 0)
		vars->fractal_values[0].c.real -= 0.001;
	if (old_x - x > 0)
		vars->fractal_values[0].c.real += 0.001;
	if (old_y - y < 0)
		vars->fractal_values[0].c.im -= 0.001;
	if (old_y + y > 0)
		vars->fractal_values[0].c.im += 0.001;
	if (recalc)
	{
		calculateJulia(vars, vars->fractal_values[0].c, vars->fractal_values[0].zoom, 0);
		mlx_put_image_to_window(vars->mlx_core, vars->mlx_windows[0], vars->mlx_images[0], 0, 0);
	}
	return (0);
}

static int	myKeyHook(int keycode, void *param)
{
	t_var	*vars;
	int		recalc;

	vars = (t_var *)param;
	if (keycode == ESC_KEYCODE)
	{
		cleanVars(vars);
		exit(0);
	}
	recalc = 0;
	if (keycode >= 123 && keycode <= 126)
		recalc = 1;
	if (keycode == 123)
		vars->fractal_values[0].c.real -= 0.001;
	else if (keycode == 124)
		vars->fractal_values[0].c.real += 0.001;
	if (keycode == 126)
		vars->fractal_values[0].c.im -= 0.001;
	else if (keycode == 125)
		vars->fractal_values[0].c.im += 0.001;
	if (recalc)
	{
		calculateJulia(vars, vars->fractal_values[0].c, vars->fractal_values[0].zoom, 0);
		mlx_put_image_to_window(vars->mlx_core, vars->mlx_windows[0], vars->mlx_images[0], 0, 0);
	}
	return (0);
}

static int myButtonHook(int button, int x, int y, void *param)
{
	t_var	*vars;

	(void)x;
	(void)y;
	vars = (t_var *)param;
	if (button == 4)
	{
		vars->fractal_values[0].zoom += 1;
		if (vars->focus[0] == JULIA)
		{
			calculateJulia(vars, vars->fractal_values[0].c, vars->fractal_values[0].zoom, 0);
			mlx_put_image_to_window(vars->mlx_core, vars->mlx_windows[0], vars->mlx_images[0], 0, 0);
		}
	}
	else if (button == 5)
	{
		vars->fractal_values[0].zoom -= 1;
		if (vars->focus[0] == JULIA)
		{
			calculateJulia(vars, vars->fractal_values[0].c, vars->fractal_values[0].zoom, 0);
			mlx_put_image_to_window(vars->mlx_core, vars->mlx_windows[0], vars->mlx_images[0], 0, 0);
		}
	}
	return (1);
}

void		setFractalValues(t_var *vars)
{
	int		i;

	i = 0;
	while (i < vars->nb_windows)
	{
		vars->fractal_values[i].c.real = DEFAULT_REAL;
		vars->fractal_values[i].c.im = DEFAULT_IM;
		vars->fractal_values[i].zoom = 1;
		i++;
	}
}

void		main_loop(t_var *vars)
{
	int		i;

	vars->mlx_windows = (void **)malloc(sizeof(void *) * vars->nb_windows);
	vars->mlx_images = (void **)malloc(sizeof(void *) * vars->nb_windows);
	vars->addr_images = (char **)malloc(sizeof(char *) * vars->nb_windows);
	vars->fractal_values = (t_values *)malloc(sizeof(t_values) * vars->nb_windows);
	setFractalValues(vars);
	i = 0;
	while (i < vars->nb_windows)
	{
		vars->function_pointers[vars->focus[i]](vars);
		i++;
	}
	i = 0;
	while (i < vars->nb_windows)
	{
		mlx_key_hook(vars->mlx_windows[i], myKeyHook, vars);
		mlx_mouse_hook(vars->mlx_windows[i], myButtonHook, vars);
		mlx_hook(vars->mlx_windows[i], 6, (1L<<6), myMouseHook, vars);
		i++;
	}
	mlx_loop(vars->mlx_core);
}
