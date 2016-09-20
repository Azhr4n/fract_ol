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

	if ((ptr = (t_node *)malloc(sizeof(t_node))) == NULL)
	{
		ft_putendl("Failed to create node.");
		exit(1);
	}
	ptr->next = NULL;
	ptr->pos.x = x;
	ptr->pos.y = y;
	return (ptr);
}

t_node	*insertNodeAtEnd(t_node *node, t_node *new)
{
	t_node	*ptr;

	if (node == NULL)
		return (new);
	else
	{
		ptr = node;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (node);
}

void	clearList(t_node **node)
{
	t_node	*next;

	while (*node != NULL)
	{
		next = (*node)->next;
		free(*node);
		*node = NULL;
		*node = next;
	}
}

void	printList(t_node *list)
{
	while (list != NULL)
	{
		printf("pos.x : %f, pos.y : %f\n", list->pos.x, list->pos.y);
		list = list->next;
	}
}

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
	while (i < MAX_ITERATIONS)
	{
		old.real = new.real;
		old.im = new.im;
		new.real = (old.real * old.real) - (old.im * old.im) + c.real;
		new.im = 2 * old.real * old.im + c.im;
		*list = insertNodeAtEnd(*list, createNewNode(new.real, new.im));
		if (new.real * new.real + new.im * new.im > 4 && i < MAX_ITERATIONS)
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
	int			(*f)(t_complex, t_complex, t_node **);

	int			**color_map;
	t_node		*list;
	t_node		*list_ptr;
	float		x;
	float		y;
	t_vector	step;
	t_vector	boundaries;

	list = NULL;
	color_map = allocateColorMap(area.end.x - area.start.x, area.end.y - area.start.y);
	f = ptr;

	for (int d = 0; d < 1000000; d++)
	{
		vec.x = rand() % (int)(area.end.x - area.start.x);
		vec.y = rand() % (int)(area.end.y - area.start.y);
		new.real = 0;
		new.im = 0;
		value.c.real = 1.5 * (vec.x - WIDTH_WINDOW / 2)
			/ (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
		value.c.im = (vec.y - HEIGHT_WINDOW / 2)
			/ (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
		i = f(new, value.c, &list);

		if (i < MAX_ITERATIONS && i > 50)
		{
			boundaries.x = 1.5 * (-WIDTH_WINDOW / 2) / (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x;
			boundaries.y = (-HEIGHT_WINDOW / 2) / (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y;
			step.x = -(boundaries.x - (1.5 * (1 - WIDTH_WINDOW / 2) / (0.5 * value.zoom * WIDTH_WINDOW) + value.pos.x));
			step.y = -(boundaries.y - ((1 - HEIGHT_WINDOW / 2) / (0.5 * value.zoom * HEIGHT_WINDOW) + value.pos.y));

			list_ptr = list;
			while (list_ptr != NULL)
			{
				x = list_ptr->pos.x / step.x + (WIDTH_WINDOW / 2);
				y = list_ptr->pos.y / step.y + (HEIGHT_WINDOW / 2);
				if (roundf(x) < WIDTH_WINDOW && roundf(x) >= 0 && roundf(y) < HEIGHT_WINDOW && roundf(y) >= 0)
					color_map[(int)roundf(x)][(int)roundf(y)] += 1;
				list_ptr = list_ptr->next;
			}
		}
		clearList(&list);
	}

	vec.x = 0;
	while (++vec.x < WIDTH_WINDOW)
	{
		vec.y = 0;
		while (++vec.y < HEIGHT_WINDOW)
		{
			color = (0x010101 * MIN(color_map[(int)vec.x][(int)vec.y], 0xFF));
			pixelSetThread(data, vec, color);
		}
	}
	puts("Done");
}

void		buddhabrot(t_fractal *fractal)
{
	pthread_t	pt[NB_THREADS];
	void		*data[NB_THREADS][4];
	void		*ret;
	int			id[NB_THREADS];
	int			i;

	i = -1;
	while (++i < NB_THREADS)
	{
		fractal->image_data[i].addr_image =
			mlx_get_data_addr(fractal->mlx_image[i], &fractal->image_data[i].bpp,
				&fractal->image_data[i].size_line, &fractal->image_data[i].endian);
		data[i][0] = fractal;
		id[i] = i;
		data[i][1] = &id[i];
		data[i][2] = calculateBuddhabrot;
		data[i][3] = iteratingBuddhabrot;
		if ((pthread_create(&pt[i], NULL, threadFunction, data[i])) != 0)
			exit(-1);
	}
	i = -1;
	while (++i < NB_THREADS)
	{
		if (pthread_join(pt[i], &ret) != 0)
			exit(-1);
	}
}

//boundaries : x : -1.5 | 1.5, y : -1 | 1
//step : x : 0.00625, y : 0.00625

//step = (ABS(val) - 1.5), val x = 1.5 / step
