/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:01:32 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 16:01:33 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	cpy;

	ptr = NULL;
	cpy = (char)c;
	while (*s)
	{
		if (*s == cpy)
			ptr = (char *)s;
		s++;
	}
	if (!*s && !(char)c)
		return ((char *)s);
	return (ptr);
}
