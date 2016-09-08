/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 15:58:15 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/07 15:58:16 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "fract_ol.h"

#include <stdio.h>

int			getIndexFocus(int *tab, int len, int focus)
{
	int		i;

	i = 0;
	while (i < len)
	{
		if (tab[i] == focus)
			return (i);
		i++;
	}
	return (-1);
}

void		setVars(t_var *vars)
{
	vars->args = (char **)malloc(sizeof(char *) * NB_ARGS);
	vars->args[0] = ft_strdup("julia");
	vars->args[1] = ft_strdup("mandelbrot");
	vars->function_pointers[JULIA] = julia;
	vars->function_pointers[MANDELBROT] = mandelbrot;
	vars->mlx_core = mlx_init();
	vars->nb_windows = 0;
	vars->dir.x = 0;
	vars->dir.y = 0;
	vars->recalc = 0;
	ft_putendl("Variables initialized.");
}

void		cleanVars(t_var *vars)
{
	int	i;

	i = 0;
	while (i < NB_ARGS)
	{
		free(vars->args[i]);
		i++;
	}
	free(vars->args);
	i = 0;
	while (i < vars->nb_windows)
	{
		mlx_destroy_image(vars->mlx_core, vars->mlx_images[i]);
		mlx_destroy_window(vars->mlx_core, vars->mlx_windows[i]);
		i++;
	}
	free(vars->addr_images);
	free(vars->mlx_images);
	free(vars->mlx_windows);
	free(vars->focus);
	free(vars->fractal_values);
	ft_putendl("Variables cleared.");
}

static int	checkDouble(t_var *vars)
{
	int		i;
	int		j;

	i = 0;
	while (i < vars->nb_windows - 1)
	{
		j = i + 1;
		while (j < vars->nb_windows)
		{
			if (vars->focus[i] == vars->focus[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	presetFocus(t_var *vars, int ac, char **av)
{
	int		i;
	int		j;

	if ((vars->focus = (int *)malloc(sizeof(int) * vars->nb_windows)) == NULL)
		return (0);
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (j < NB_ARGS)
		{
			if (strcmp(av[i], vars->args[j]) == 0)
				vars->focus[i - 1] = j;
			j++;
		}
	}
	if (!checkDouble(vars))
	{
		free(vars->focus);
		return (0);
	}
	else
		return (1);
}

char		argsValid(t_var *vars, int ac, char **av)
{
	int		i;
	int		j;
	int		safe;

	i = 0;
	while (++i < ac)
	{
		strLower(av[i]);
		j = 0;
		safe = 0;
		while (j < NB_ARGS)
		{
			if (strcmp(av[i], vars->args[j]) == 0)
			{
				vars->nb_windows++;
				safe = 1;
				break;
			}
			j++;
		}
		if (safe == 0)
			return 0;
	}
	return (presetFocus(vars, ac, av));
}
