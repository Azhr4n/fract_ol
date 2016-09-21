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

void		set_vars(t_var *vars)
{
	vars->args = (char **)malloc(sizeof(char *) * NB_ARGS);
	if (vars->args == NULL)
	{
		ft_putendl("Malloc failed.");
		exit(-1);
	}
	vars->args[0] = ft_strdup("julia");
	vars->args[1] = ft_strdup("mandelbrot");
	vars->args[2] = ft_strdup("buddhabrot");
	vars->function_pointers[JULIA] = julia;
	vars->function_pointers[MANDELBROT] = mandelbrot;
	vars->function_pointers[BUDDHABROT] = buddhabrot;
	vars->mlx_core = mlx_init();
	vars->nb_windows = 0;
	vars->dir.x = 0;
	vars->dir.y = 0;
	vars->mouse_pos.x = 0;
	vars->mouse_pos.y = 0;
	vars->fract_set = 0;
}

void		clean_vars(t_var *vars)
{
	int	i;
	int	j;

	i = -1;
	while (++i < NB_ARGS)
		free(vars->args[i]);
	free(vars->args);
	if (vars->fract_set)
	{
		i = -1;
		while (++i < vars->nb_windows)
		{
			j = -1;
			while (++j < NB_THREADS)
				mlx_destroy_image(vars->mlx_core,
					vars->fractals[i].mlx_image[j]);
			mlx_destroy_window(vars->mlx_core, vars->fractals[i].mlx_window);
		}
		free(vars->fractals);
	}
}

static void	allocate_vars(t_var *vars, int index, int type)
{
	int		i;

	vars->fractals[index].type = type;
	vars->fractals[index].mlx_window = mlx_new_window(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW, vars->args[type]);
	i = 0;
	while (i < NB_THREADS)
	{
		vars->fractals[index].mlx_image[i] = mlx_new_image(vars->mlx_core,
			(WIDTH_WINDOW / NB_THREADS), HEIGHT_WINDOW);
		i++;
	}
	vars->fract_set = 1;
	vars->real_const_val = 0.001;
	vars->im_const_val = 0.00001;
	if (type == BUDDHABROT)
		vars->fractals[index].image_value.list = NULL;
}

static void	preset_struct(t_var *vars, int ac, char **av)
{
	int		i;
	int		j;

	if ((vars->fractals =
		(t_fractal *)malloc(sizeof(t_fractal) * vars->nb_windows)) == NULL)
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
				allocate_vars(vars, i - 1, j);
			j++;
		}
	}
}

int			args_valid(t_var *vars, int ac, char **av)
{
	int		i;
	int		j;
	int		safe;

	i = 0;
	while (++i < ac)
	{
		str_lower(av[i]);
		j = 0;
		safe = 0;
		while (j < NB_ARGS)
		{
			if (strcmp(av[i], vars->args[j]) == 0)
			{
				vars->nb_windows++;
				safe = 1;
				break ;
			}
			j++;
		}
		if (safe == 0)
			return (0);
	}
	preset_struct(vars, ac, av);
	return (1);
}
