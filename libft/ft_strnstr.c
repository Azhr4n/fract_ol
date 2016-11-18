/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:02:47 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 16:02:47 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	inc;

	inc = 0;
	if (!*little)
		return ((char*)big);
	while (*big && inc < len)
	{
		i = 0;
		if (*big == little[i])
		{
			while (*(big + i) && *(big + i) == little[i] && inc < len)
			{
				inc++;
				i++;
			}
			if (!little[i])
				return ((char *)big);
			inc -= i;
		}
		else
			inc++;
		big++;
	}
	return (NULL);
}
