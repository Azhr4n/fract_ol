/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:49:37 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 14:49:39 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void			*ret;
	unsigned char	*ptr;
	size_t			i;

	ret = (void *)malloc(size);
	if (ret == NULL)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)ret;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ret);
}
