/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 15:55:05 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 16:05:32 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

char		*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t		i;
	size_t		inc;

	i = 0;
	while (dest[i])
		i++;
	inc = 0;
	while (src[inc] && inc < n)
	{
		dest[i] = src[inc];
		inc++;
		i++;
	}
	dest[i] = 0;
	return (dest);
}
