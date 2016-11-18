/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:49:49 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 14:49:52 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t					i;
	const unsigned char		*ptr_s1;
	const unsigned char		*ptr_s2;

	if (!n)
		return (0);
	ptr_s1 = (const unsigned char *)s1;
	ptr_s2 = (const unsigned char *)s2;
	i = 0;
	while (*ptr_s1 == *ptr_s2 && i < n - 1)
	{
		ptr_s1++;
		ptr_s2++;
		i++;
	}
	return (*ptr_s1 - *ptr_s2);
}
