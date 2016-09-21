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

pthread_mutex_t		lock = PTHREAD_MUTEX_INITIALIZER;

int		**allocateColorMap(int width, int height)
{
	int		**color_map;
	int		i;
	int		j;

	if ((color_map = (int **)malloc(sizeof(int *) * width)) == NULL)
	{
		ft_putendl("Failed to malloc.");
		exit(-1);
	}
	i = -1;
	while (++i < width)
	{
		if ((color_map[i] = (int *)malloc(sizeof(int) * height)) == NULL)
		{
			ft_putendl("Failed to malloc.");
			exit(-1);
		}
		j = -1;
		while (++j < height)
			color_map[i][j] = 0;
	}
	return (color_map);
}

int	iteratingBuddhabrot(t_complex new, t_complex c, t_node **list)
{
	t_complex	old;
	int			i;

	i = 0;
	while (i < MAX_ITERATIONS_B)
	{
		old.real = new.real;
		old.im = new.im;
		new.real = (old.real * old.real) - (old.im * old.im) + c.real;
		new.im = 2 * old.real * old.im + c.im;
		*list = insertNodeAtEnd(*list, createNewNode(new.real, new.im));
		if (new.real * new.real + new.im * new.im > 4 && i < MAX_ITERATIONS_B)
			break;
		i++;
	}
	return (i);
}

void	calculateBuddhabrot(t_image_data *data, t_image_value value, void *ptr)
{
	int			i;
	int			(*f)(t_complex, t_complex, t_node **);

	t_node		*list;
	t_node		*list_ptr;
	float		x;
	float		y;
	t_vector	step;
	t_vector	boundaries;

	list = NULL;
	f = ptr;

	for (int d = 0; d < 1500000 / NB_THREADS; d++)
	{
		value.vec.x = rand() % (int)(WIDTH_WINDOW);
		value.vec.y = rand() % (int)(HEIGHT_WINDOW);
		value.new.real = 0;
		value.new.im = 0;
		value.c.real = 1.5 * (value.vec.x - WIDTH_WINDOW / 2)
			/ (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
		value.c.im = (value.vec.y - HEIGHT_WINDOW / 2)
			/ (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
		i = f(value.new, value.c, &list);

		if (i < MAX_ITERATIONS_B && i > 50)
		{
			boundaries.x = 1.5 * (-WIDTH_WINDOW / 2) / (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
			boundaries.y = (-HEIGHT_WINDOW / 2) / (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
			step.x = -(boundaries.x - (1.5 * (1 - WIDTH_WINDOW / 2) / (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x));
			step.y = -(boundaries.y - ((1 - HEIGHT_WINDOW / 2) / (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y));

			list_ptr = list;
			while (list_ptr != NULL)
			{
				x = (list_ptr->pos.x - value.pos.x) / step.x + (WIDTH_WINDOW / 2);
				y = (list_ptr->pos.y - value.pos.y) / step.y  + (HEIGHT_WINDOW / 2);
				pthread_mutex_lock(&lock);
				// puts("Lock");
				if (roundf(x) < WIDTH_WINDOW && roundf(x) >= 0 && roundf(y) < HEIGHT_WINDOW && roundf(y) >= 0)
					(*data->color_map)[(int)roundf(x)][(int)roundf(y)] += 1;
				pthread_mutex_unlock(&lock);
				// puts("Unlock");
				list_ptr = list_ptr->next;
			}
		}
		clearList(&list);
	}
	value.vec.x = value.area.start.x - 1;
	while (++value.vec.x < value.area.end.x)
	{
		value.vec.y = value.area.start.y - 1;
		while (++value.vec.y < value.area.end.y)
			pixelSetThread(data, value.vec, value.area.start,
				setColor(MIN((*data->color_map)[(int)value.vec.x][(int)value.vec.y], 0xFF),
				1, 1, 1));
	}
}

void		buddhabrot(t_fractal *fractal)
{
	t_thread	thread;
	void		*data[NB_THREADS][4];
	int			**color_map;
	int			i;

	color_map = allocateColorMap(WIDTH_WINDOW, HEIGHT_WINDOW);
	i = -1;
	while (++i < NB_THREADS)
	{
		fractal->image_data[i].addr_image =
			mlx_get_data_addr(fractal->mlx_image[i], ABPP, ASL, AEN);
		fractal->image_data[i].color_map = &color_map;
		data[i][0] = fractal;
		thread.id[i] = i;
		data[i][1] = &(thread.id[i]);
		data[i][2] = calculateBuddhabrot;
		data[i][3] = iteratingBuddhabrot;
		if ((pthread_create(&(thread.pt[i]), NULL, threadFunction, data[i])) != 0)
			exit(-1);
	}
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_join(thread.pt[i], &(thread.ret[i])) != 0)
			exit(-1);
	// free2D(color_map, WIDTH_WINDOW, HEIGHT_WINDOW);
}
