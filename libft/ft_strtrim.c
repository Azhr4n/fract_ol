/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 16:28:06 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 16:28:07 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

static int	get_last_index(char const *s)
{
	int		ret;
	int		i;

	i = 0;
	ret = -1;
	while (s[i])
	{
		if (s[i] != '\t' && s[i] != ' ' && s[i] != '\n'
			&& s[i] != '\v' && s[i] != '\r' && s[i] != '\f')
			ret = i + 1;
		i++;
	}
	if (ret == -1)
		ret = i;
	return (ret);
}

char		*ft_strtrim(char const *s)
{
	char	*ret;
	int		last_index;
	int		i;

	while (*s == ' ' || *s == '\t' || *s == '\v'
		|| *s == '\f' || *s == '\r' || *s == '\n')
		s++;
	i = 0;
	last_index = get_last_index(s);
	ret = (char *)malloc(sizeof(char) * (last_index + 1));
	if (ret == NULL)
		return (NULL);
	ret[last_index] = 0;
	i = 0;
	while (i < last_index)
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}
