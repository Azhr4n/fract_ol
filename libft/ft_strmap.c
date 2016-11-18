/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 15:06:18 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 15:06:22 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char		*ret;
	int			i;

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
		ret[i] = f(s[i]);
		i++;
	}
	return (ret);
}
