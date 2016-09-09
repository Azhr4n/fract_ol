/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/09 12:38:53 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/09 12:38:53 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <string.h>

#include <stdio.h>

void	*print(void *arg)
{
	int	*ptr;

	ptr = arg;
	printf("%d\n", *ptr);

	return (NULL);
}

int main(void)
{
	pthread_t	thread[4];
	int			tab[4][1];
	void		*ret;
	void		*data;
	int			i;


	for (i = 0; i < 4; i++)
	{
		tab[i][0] = i;
		data = tab[i];
		pthread_create(&thread[i], NULL, print, data);
	}
	for (i = 0; i < 4; i++)
		pthread_join(thread[i], &ret);

	return (0);
}
