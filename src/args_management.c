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

void	setVars(t_var *vars)
{
	int		i;

	vars->args = (char **)malloc(sizeof(char *) * NB_ARGS);
	vars->args[0] = ft_strdup("julia");
	vars->args[1] = ft_strdup("mandelbrot");
	vars->function_pointers[JULIA] = julia;
	vars->function_pointers[MANDELBROT] = mandelbrot;
	i = 0;
	while (i < NB_ARGS)
	{
		vars->args_valid[i] = 0;
		i++;
	}
	vars->mlx_core = mlx_init();
	vars->nb_windows = 0;
	vars->max_window = 0;
}

void	cleanVars(t_var *vars)
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
	ft_putendl("Vars cleared.");
}

char	argsValid(t_var *vars, int ac, char **av)
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
				vars->args_valid[j] = 1;
				safe = 1;
				break;
			}
			j++;
		}
		if (safe == 0)
			return 0;
	}
	return 1;
}
