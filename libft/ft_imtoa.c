/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:17:10 by pivanovi          #+#    #+#             */
/*   Updated: 2016/03/02 17:17:11 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

static intmax_t		nb_of_digit(intmax_t n)
{
	intmax_t		len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

static void			recur(char **str, intmax_t len, intmax_t n)
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

char				*ft_imtoa(intmax_t n)
{
	char		*ret;
	intmax_t	len;

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
