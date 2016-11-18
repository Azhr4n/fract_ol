/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 17:14:34 by pivanovi          #+#    #+#             */
/*   Updated: 2016/03/02 17:14:35 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "libft.h"

static uintmax_t	nb_of_digit(uintmax_t n)
{
	uintmax_t		len;

	len = 1;
	while ((n /= 10) != 0)
		len++;
	return (len);
}

static void			recur(char **str, uintmax_t len, uintmax_t n)
{
	if ((n / 10) != 0)
		recur(str, len - 1, n / 10);
	n %= 10;
	(*str)[len] = '0' + (n % 10);
}

char				*ft_uimtoa(uintmax_t n)
{
	char		*ret;
	uintmax_t	len;

	len = nb_of_digit(n);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	ret[len] = 0;
	recur(&ret, len - 1, n);
	return (ret);
}
