/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <pivanovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 17:54:00 by pivanovi          #+#    #+#             */
/*   Updated: 2016/01/13 17:54:01 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft.h"

void		ft_putstr_fd(const char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}
