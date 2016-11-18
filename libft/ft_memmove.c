/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 17:16:32 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/11 17:16:32 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	buff[len];
	unsigned char	*ptr_src;
	unsigned char	*ptr_dst;
	size_t			i;

	ptr_src = (unsigned char *)src;
	ptr_dst = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		buff[i] = ptr_src[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		ptr_dst[i] = buff[i];
		i++;
	}
	return (dst);
}
