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

int		main(int ac, char **av)
{
	t_var	vars;

	set_vars(&vars);
	if (ac > 1 && ac <= 4)
	{
		if (args_valid(&vars, ac, av) == 0)
		{
			free(vars.args);
			ft_putendl("Arguments are not valids.");
			return (0);
		}
		else
			main_loop(&vars);
	}
	else
		ft_putendl("Either too much args or not any.");
	clean_vars(&vars);
	return (0);
}
