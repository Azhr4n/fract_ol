/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 17:24:13 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 17:24:13 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

static int	nb_of_digit(int n)
{
	int		len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

static void	recur(char **str, int len, int n)
{
	if ((n / 10) != 0)
	{
		if (n < 0)
			recur(str, len - 1, -(n / 10));
		else
			recur(str, len - 1, n / 10);
	}
	n %= 10;
	if (n < 0)
		n = -n;
	(*str)[len] = '0' + (n % 10);
}

char		*ft_itoa(int n)
{
	char	*ret;
	int		len;

	len = nb_of_digit(n);
	if (n < 0)
		len++;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ret[len] = 0;
	recur(&ret, len - 1, n);
	if (n < 0)
		ret[0] = '-';
	return (ret);
}
