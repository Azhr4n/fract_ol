/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddhabrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/14 12:09:20 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/14 12:09:20 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft.h>
#include <stdlib.h>
#include <pthread.h>

#include "fract_ol.h"

#include <stdio.h>

t_node	*createNewNode(float x, float y)
{
	t_node	*ptr;

	ptr = (t_node *)malloc(sizeof(t_node));
	ptr->next = NULL;
	ptr->pos.x = x;
	ptr->pos.y = y;
	return (ptr);
}

void	insertNodeAtEnd(t_node *node, t_node *new)
{
	t_node	*ptr;

	ptr = node;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}


int	iteratingBuddhabrot(t_complex new, t_complex c, t_node *list)
{
	t_complex	old;
	int			i;

	(void)list;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		old.real = new.real;
		old.im = new.im;
		new.real = (old.real * old.real) - (old.im * old.im) + c.real;
		new.im = 2 * old.real * old.im + c.im;
		if (new.real * new.real + new.im * new.im > 4)
			break;
		i++;
	}
	return (i);
}

void	calculateBuddhabrot(t_image_data *data, t_image_value value, t_area area, void *ptr)
{
	t_vector	vec;
	t_complex	new;
	int			i;
	int			color;
	int			(*f)(t_complex, t_complex, t_node *);
	t_node		list;


	f = ptr;
	vec.x = area.start.x - 1;
	while (++vec.x < area.end.x)
	{
		vec.y = area.start.y - 1;
		while (++vec.y < area.end.y)
		{
			new.real = 0;
			new.im = 0;
			// value.c.real = vec.x / (value.zoom * 100) + (-2.1);
			value.c.real = 1.5 * (vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
			value.c.im = (vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
			i = f(new, value.c, &list);
			exit(1);
			color = (0x010000 * (i * 4)) +
				(0x000100 * (i * 10)) + (0x000001 * (i * 100));
			if (i == MAX_ITERATIONS)
				color = 0x000000;
			// pixelSetThread(data, vec, color);
			(void)data;
		}
	}
}

void		buddhabrot(t_fractal *fractal)
{
	pthread_t	pt[NB_THREADS];
	void		*data[NB_THREADS][4];
	void		*ret;
	int			id[NB_THREADS];
	int			i;

	i = -1;
	while (++i < 1)
	{
		fractal->image_data[i].addr_image =
			mlx_get_data_addr(fractal->mlx_image[i], &fractal->image_data[i].bpp,
				&fractal->image_data[i].size_line, &fractal->image_data[i].endian);
		data[i][0] = &fractal->image_data;
		id[i] = i;
		data[i][1] = &id[i];
		data[i][2] = calculateBuddhabrot;
		data[i][3] = iteratingBuddhabrot;
		if ((pthread_create(&pt[i], NULL, threadFunction, data[i])) != 0)
			exit(-1);
	}
	i = -1;
	while (++i < 1)
	{
		if (pthread_join(pt[i], &ret) != 0)
			exit(-1);
	}
}

//boundaries : x : -1.5 | 1.5, y : -1 | 1
//step : x : 0.00625, y : 0.00625

