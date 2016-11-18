/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:30:07 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 18:30:08 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	ret = ft_strlen((char*)src);
	i = 0;
	j = 0;
	while (dst[i] && i < size)
		++i;
	if (size > 0)
		while (i < size - 1 && src[j])
			dst[i++] = src[j++];
	if (j > 0)
	{
		dst[i] = 0;
		return (ret + i - j);
	}
	return (ret + i);
}
