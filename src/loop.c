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

int		my_key_pressed(int keycode, void *param)
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
	change_constant_values(keycode, vars);
	return (0);
}

int		my_key_released(int keycode, void *param)
{
	t_var	*vars;

	vars = (t_var *)param;
	if (keycode == ESC_KEYCODE)
	{
		clean_vars(vars);
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

int		my_button_hook(int button, int x, int y, void *param)
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
		vars->fractals[*id].image_value.pos.x += ((x - WIDTH_WINDOW / 2)
			/ vars->fractals[*id].image_value.zoom) / 10000;
		vars->fractals[*id].image_value.pos.y += ((y - HEIGHT_WINDOW / 2)
			/ vars->fractals[*id].image_value.zoom) / 10000;
		set_zoom(vars, MUL, 1.01, *id);
	}
	else if (button == 6)
		set_zoom(vars, MUL, 1.01, *id);
	else if (button == 5)
		set_zoom(vars, DIV, 1.01, *id);
	return (1);
}

int		refresh(void *param)
{
	t_var	*vars;
	int		i;
	int		inc;

	vars = (t_var *)param;
	i = 0;
	while (i < vars->nb_windows)
	{
		if (vars->fractals[i].print)
		{
			vars->function_pointers[vars->fractals[i].type](
				&vars->fractals[i]);
			inc = 0;
			while (inc < NB_THREADS)
			{
				mlx_put_image_to_window(vars->mlx_core,
					vars->fractals[i].mlx_window,
					VTFF, inc * (WIDTH_WINDOW / NB_THREADS), 0);
				inc++;
			}
			vars->fractals[i].print = 0;
		}
		i++;
	}
	return (0);
}

void	main_loop(t_var *vars)
{
	int		i;
	int		id[vars->nb_windows];
	void	*tab[vars->nb_windows][2];

	set_fractal_values(vars);
	vars->focus = vars->nb_windows;
	i = 0;
	while (i < vars->nb_windows)
	{
		tab[i][0] = vars;
		id[i] = i;
		tab[i][1] = &id[i];
		mlx_mouse_hook(vars->fractals[i].mlx_window, my_button_hook, tab[i]);
		mlx_hook(vars->fractals[i].mlx_window, 6,
			(1L << 6), my_mouse_hook, vars);
		mlx_hook(vars->fractals[i].mlx_window, 2,
			(1L << 0), my_key_pressed, vars);
		mlx_hook(vars->fractals[i].mlx_window, 3,
			(1L << 1), my_key_released, vars);
		i++;
	}
	mlx_loop_hook(vars->mlx_core, refresh, vars);
	mlx_loop(vars->mlx_core);
}
