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

void	main_loop(t_var *vars)
{
	int		i;

	vars->mlx_windows = (void **)malloc(sizeof(void *) * vars->nb_windows);
	vars->mlx_images = (void **)malloc(sizeof(void *) * vars->nb_windows);
	vars->addr_images = (char **)malloc(sizeof(char *) * vars->nb_windows);

	i = 0;
	while (i < NB_ARGS)
	{
		if (vars->args_valid[i] == 1)
			vars->function_pointers[i](vars);
		i++;
	}
	i = 0;
	while (i < vars->nb_windows)
	{
		mlx_key_hook(vars->mlx_windows[i], myKeyHook, vars);
		i++;
	}
	mlx_loop(vars->mlx_core);
}

int		myKeyHook(int keycode, void *param)
{
	t_var	*vars;

	vars = (t_var *)param;
	if (keycode == ESC_KEYCODE)
	{
		cleanVars(vars);
		exit(0);
	}
	return (0);
}
