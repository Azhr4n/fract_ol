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

int		main(int ac, char **av)
{
	t_var	vars;

	setVars(&vars);
	if (ac > 1)
	{
		if (argsValid(&vars, ac, av) == 0)
		{
			free(vars.args);
			ft_putendl("Arguments are not valids.");
			return (0);
		}
		else
			main_loop(&vars);
	}
	else
		ft_putendl("No fractal specified.");
	cleanVars(&vars);
	return (0);
}
