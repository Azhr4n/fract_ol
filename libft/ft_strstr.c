/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:00:28 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 16:00:28 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include "libft.h"

#include <stdio.h>

char		*ft_strstr(const char *big, const char *little)
{
	int		i;

	i = 0;
	if (!*little)
		return ((char*)big);
	while (*big)
	{
		i = 0;
		if (*big == little[i])
		{
			while (*(big + i) && little[i] && *(big + i) == little[i])
				i++;
			if (!little[i])
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
