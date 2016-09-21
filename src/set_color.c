/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:32:16 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/21 11:32:17 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

int		setColor(int iterations, int r, int g, int b)
{
	if (iterations == MAX_ITERATIONS)
		return (0x000000);
	else
		return ((0x010000 * (iterations * r)) +
		(0x000100 * (iterations * g)) + (0x000001 * (iterations * b)));
}
