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

	vars = (t_var *)param;
	if (old_x == 0)
		old_x = x;
	if (old_y == 0)
		old_y = y;
	// recalc = 0;	
	// if (old_x - x < 0)
	// 	vars->fractal_values[0].c.real -= 0.0001;
	// if (old_x - x > 0)
	// 	vars->fractal_values[0].c.real += 0.0001;
	// if (old_y - y < 0)
	// 	vars->fractal_values[0].c.im -= 0.0001;
	// if (old_y + y > 0)
	// 	vars->fractal_values[0].c.im += 0.0001;
	// if ((old_x - x < 0) || (old_x - x > 0) || (old_y - y < 0) || (old_y + y > 0))
	// 	vars->recalc = 1;
	return (0);
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
	return (0);
}

static int myButtonHook(int button, int x, int y, void *param)
{
	t_var	*vars;

	(void)x;
	(void)y;
	(void)button;
	vars = (t_var *)param;
	// if (button == 4)
	// {
		// vars->fractal_values[0].zoom *= 1.1;
		// vars->recalc = 1;
	// }
	// else if (button == 5)
	// {
		// vars->fractal_values[0].zoom /= 1.1;
		// vars->recalc = 1;
	// }
	return (1);
}

static int	refresh(void *param)
{
	t_var	*vars;
	int		i;

	vars = (t_var *)param;
	// if (vars->dir.x != 0 || vars->dir.y != 0)
		// vars->recalc = 1;
	// if (vars->dir.x > 0)
		// vars->fractal_values[0].c.real += 0.0001;
	// else if (vars->dir.x < 0)
		// vars->fractal_values[0].c.real -= 0.0001;
	// if (vars->dir.y > 0)
		// vars->fractal_values[0].c.im += 0.0001;
	// else if (vars->dir.y < 0)
		// vars->fractal_values[0].c.im -= 0.0001;

	i = 0;
	while (i < vars->nb_windows)
	{
		if (vars->fractals[i].recalc)
			vars->function_pointers[vars->fractals[i].type]
				(vars->mlx_core, &vars->fractals[i]);
		i++;
	}
	return (0);
}

void		setFractalValues(t_var *vars)
{
	int		i;

	i = 0;
	while (i < vars->nb_windows)
	{
		vars->fractals[i].values.c.real = DEFAULT_REAL;
		vars->fractals[i].values.c.im = DEFAULT_IM;
		vars->fractals[i].values.zoom = 1;
		i++;
	}
}

void		main_loop(t_var *vars)
{
	int		i;

	setFractalValues(vars);
	i = 0;
	while (i < vars->nb_windows)
	{
		vars->function_pointers[vars->fractals[i].type]
			(vars->mlx_core, &vars->fractals[i]);
		i++;
	}
	i = 0;
	while (i < vars->nb_windows)
	{
		mlx_mouse_hook(vars->fractals[i].mlx_window, myButtonHook, vars);
		mlx_hook(vars->fractals[i].mlx_window, 6, (1L<<6), myMouseHook, vars);
		mlx_hook(vars->fractals[i].mlx_window, 2, (1L<<0), myKeyPressed, vars);
		mlx_hook(vars->fractals[i].mlx_window, 3, (1L<<1), myKeyReleased, vars);
		i++;
	}
	mlx_loop_hook(vars->mlx_core, refresh, vars);
	mlx_loop(vars->mlx_core);
}
