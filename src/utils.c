/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 14:55:47 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/21 14:55:48 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

#include "fract_ol.h"

void		free2Dint(int **tab, int width)
{
	int		i;

	i = -1;
	while (++i < width)
		free(tab[i]);
	free(tab);
}

void	strLower(char *str)
{
	while (*str != 0)
	{
		*str = (char)ft_tolower(*str);
		str++;
	}
}