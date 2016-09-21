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

pthread_mutex_t	g_lock = PTHREAD_MUTEX_INITIALIZER;

int		iterating_buddhabrot(t_complex new, t_complex c, t_node **list)
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
		*list = insert_node_at_end(*list, create_new_node(new.real, new.im));
		if (new.real * new.real + new.im * new.im > 4 && i < MAX_ITERATIONS_B)
			break ;
		i++;
	}
	return (i);
}

void	update_color_map(t_image_data *data, t_image_value value)
{
	t_node		*list_ptr;

	value.step.x = -((CX(0) + value.pos.x) - (CX(1) + value.pos.x));
	value.step.y = -((CY(0) + value.pos.y) - (CY(1) + value.pos.y));
	list_ptr = value.list;
	while (list_ptr != NULL)
	{
		value.vec.x = (list_ptr->pos.x - value.pos.x)
			/ value.step.x + (WIDTH_WINDOW / 2);
		value.vec.y = (list_ptr->pos.y - value.pos.y)
			/ value.step.y + (HEIGHT_WINDOW / 2);
		pthread_mutex_lock(&g_lock);
		if (RFXC && RFYC)
			(*data->color_map)[(int)RFX][(int)RFY] += 1;
		pthread_mutex_unlock(&g_lock);
		list_ptr = list_ptr->next;
	}
}

void	calculate_buddhabrot(t_image_data *data, t_image_value value, void *ptr)
{
	int		(*f)(t_complex, t_complex, t_node **);
	int		i;
	int		j;

	f = ptr;
	j = -1;
	while (++j < 1500000 / NB_THREADS)
	{
		set_buddha_values(value, &value.c, &value.new);
		i = f(value.new, value.c, &value.list);
		if (i < MAX_ITERATIONS_B && i > 50)
			update_color_map(data, value);
		clear_list(&value.list);
	}
	value.vec.x = value.area.start.x - 1;
	while (++value.vec.x < value.area.end.x)
	{
		value.vec.y = value.area.start.y - 1;
		while (++value.vec.y < value.area.end.y)
			pixel_set_thread(data, value.vec, value.area.start,
				set_color(
					MIN((*data->color_map)[(int)value.vec.x][(int)value.vec.y],
				0xFF), 1, 1, 1));
	}
}

void	buddhabrot(t_fractal *fractal)
{
	t_thread	thread;
	void		*data[NB_THREADS][4];
	int			**color_map;
	int			i;

	color_map = allocate_color_map(WIDTH_WINDOW, HEIGHT_WINDOW);
	i = -1;
	while (++i < NB_THREADS)
	{
		fractal->image_data[i].addr_image =
			mlx_get_data_addr(fractal->mlx_image[i], ABPP, ASL, AEN);
		fractal->image_data[i].color_map = &color_map;
		data[i][0] = fractal;
		thread.id[i] = i;
		data[i][1] = &(thread.id[i]);
		data[i][2] = calculate_buddhabrot;
		data[i][3] = iterating_buddhabrot;
		if ((pthread_create(&(thread.pt[i]), 0, thread_func, data[i])) != 0)
			exit(-1);
	}
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_join(thread.pt[i], &(thread.ret[i])) != 0)
			exit(-1);
	free2d_int(color_map, WIDTH_WINDOW);
}
