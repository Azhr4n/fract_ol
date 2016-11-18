/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:51:12 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 14:51:14 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	unsigned char	cpy;
	char			*ptr;

	cpy = (unsigned char)c;
	while (*s)
	{
		if (*s == cpy)
		{
			ptr = (char *)s;
			return (ptr);
		}
		s++;
	}
	if (!*s && cpy == 0)
	{
		ptr = (char *)s;
		return (ptr);
	}
	return (NULL);
}
