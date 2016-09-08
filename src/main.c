/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 12:38:18 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/07 12:38:20 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <libft.h>

#include "fract_ol.h"

#include <stdio.h>

void	strLower(char *str)
{
	while (*str != 0)
	{
		*str = (char)ft_tolower(*str);
		str++;
	}
}

void	mandelbrot(void *data)
{
	t_var	*vars;
	int		index;

	vars = (t_var *)data;
	index = getIndexFocus(vars->focus, vars->nb_windows, MANDELBROT);
	vars->mlx_windows[index] = mlx_new_window(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW, "Mandelbrot");
	vars->mlx_images[index] = mlx_new_image(vars->mlx_core,
		WIDTH_WINDOW, HEIGHT_WINDOW);
	vars->addr_images[index] = mlx_get_data_addr(
		vars->mlx_images[index],&vars->bpp,
		&vars->size_line, &vars->endian);
}

int		main(int ac, char **av)
{
	t_var	vars;

	setVars(&vars);
	if (ac > 1)
	{
		if (argsValid(&vars, ac, av) == 0)
			ft_putendl("Arguments are not valids.");
		else
			main_loop(&vars);
	}
	else
		ft_putendl("No fractal specified.");
	cleanVars(&vars);
	return (0);
}
