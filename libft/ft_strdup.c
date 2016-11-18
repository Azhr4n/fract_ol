/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 15:05:13 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 15:05:14 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i])
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (ret == NULL)
		return (NULL);
	ret[i] = 0;
	i = 0;
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}
