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
	if (vars->args == NULL)
	{
		ft_putendl("Malloc failed.");
		exit(-1);
	}
	vars->args[0] = ft_strdup("julia");
	vars->args[1] = ft_strdup("mandelbrot");
	vars->function_pointers[JULIA] = julia;
	// vars->function_pointers[MANDELBROT] = mandelbrot;
	vars->mlx_core = mlx_init();
	vars->nb_windows = 0;
	vars->dir.x = 0;
	vars->dir.y = 0;
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
	ft_putendl("Variables cleared.");
}

static void	allocateVars(t_var *vars, int index, int type)
{
	vars->fractals[index].type = type;
	vars->fractals[index].mlx_window = mlx_new_window(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW, vars->args[type]);
	vars->fractals[index].mlx_image = mlx_new_image(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW);
	vars->fractals[index].addr_image = 
		mlx_get_data_addr(&vars->fractals[index].mlx_image,
			&vars->fractals[index].bpp,	&vars->fractals[index].size_line,
			&vars->fractals[index].endian);
	vars->fractals[index].recalc = 1;
}

static void	presetStruct(t_var *vars, int ac, char **av)
{
	int		i;
	int		j;

	if ((vars->fractals = (t_fractal *)malloc(sizeof(t_fractal) * vars->nb_windows)) == NULL)
	{
		ft_putendl("Malloc failed.");
		exit(-1);
	}
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (j < NB_ARGS)
		{
			if (strcmp(av[i], vars->args[j]) == 0)
				allocateVars(vars, i - 1, j);
			j++;
		}
	}
}

int		argsValid(t_var *vars, int ac, char **av)
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
	presetStruct(vars, ac, av);
	return (1);
}
