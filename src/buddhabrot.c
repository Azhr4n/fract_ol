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

int	iteratingBuddhabrot(t_complex new, t_complex c, t_image_data *data,
	int ***tmp_tab)
{
	float		tmp;
	float		im_tmp;
	int			i;
	float		x;
	float		y;

	(void)data;
	i = -1;
	while (++i < MAX_ITERATIONS)
	{
		tmp = new.real;
		new.real = (new.real * new.real) - (new.im * new.im) + c.real;
		x = ((((new.real - (tmp * tmp)) + (new.im * new.im)) * (0.5 * WIDTH_WINDOW)) / 1.5) + (WIDTH_WINDOW / 2);
		im_tmp = new.im;
		new.im = 2 * tmp * new.im + c.im;
		y = (new.im - (2 * tmp * im_tmp)) * (0.5 * HEIGHT_WINDOW) + (HEIGHT_WINDOW / 2);
		if (roundf(x) == x && x >= 0 && x < WIDTH_WINDOW && roundf(y) == y && y >= 0 && y < HEIGHT_WINDOW)
			(*tmp_tab)[(int)x][(int)y] += 1;
		if ((new.real * new.real) + (new.im * new.im) > 4)
			break;
	}
	return (i);
}

int		**allocateDoubleTab(int width, int height)
{
	int		**tab;
	int		i;
	int		j;

	tab = (int **)malloc(sizeof(int *) * width);
	i = -1;
	while (++i < width)
	{
		tab[i] = (int *)malloc(sizeof(int) * height);
		j = -1;
		while (++j < height)
			tab[i][j] = 0;
	}
	return (tab);
}

void	intermediateBuddha(t_image_data *data, t_area area, void *ptr,
	int ***pixel_intensity)
{
	t_vector	vec;
	t_complex	new;
	int			i;
	int			(*f)(t_complex, t_complex, t_image_data *, int ***);
	int			**tmp_tab;

	tmp_tab = allocateDoubleTab(WIDTH_WINDOW, HEIGHT_WINDOW);
	f = ptr;
	vec.x = area.start.x - 1;
	while (++vec.x < area.end.x)
	{
		vec.y = area.start.y;
		while (++vec.y < area.end.y)
		{
			new.real = 0;
			new.im = 0;
			data->c.real = 1.5 * (vec.x - WIDTH_WINDOW / 2)
				/ (0.5 * data->zoom * WIDTH_WINDOW) + data->pos.x;
			data->c.im = (vec.y - HEIGHT_WINDOW / 2)
				/ (0.5 * data->zoom * HEIGHT_WINDOW) + data->pos.y;
			i = f(new, data->c, data, &tmp_tab);
			if (i != MAX_ITERATIONS)
			{
				for (int k = area.start.x; k < area.end.x; k++)
				{
					for (int j = area.start.y; j < area.end.y; j++)
						(*pixel_intensity)[k][j] += tmp_tab[k][j];
				}
			}
			for (int k = 0; k < WIDTH_WINDOW; k++)
			{
				for (int j = 0; j < HEIGHT_WINDOW; j++)
					tmp_tab[k][j] = 0;
			}
		}
	}
	puts("Done");
	//FREE(TMP_TAB);
}

void	calculateBuddhabrot(t_image_data *data, t_area area, void *ptr)
{
	int			**pixel_intensity;
	t_vector	vec;
	int			color;

	pixel_intensity = allocateDoubleTab(area.end.x - area.start.x, area.end.y - area.start.y);
	intermediateBuddha(data, area, ptr, &pixel_intensity);
	for (vec.x = area.start.x; vec.x < area.end.x; vec.x++)
	{
		for (vec.y = area.start.y; vec.y < area.end.y; vec.y++)
		{
			if (pixel_intensity[(int)vec.x][(int)vec.y] > 100)
				printf("[%d] ", pixel_intensity[(int)vec.x][(int)vec.y]);
			color = (0x010000 * (pixel_intensity[(int)vec.x][(int)vec.y])) +
				(0x000100 * (pixel_intensity[(int)vec.x][(int)vec.y]))
				+ (0x000001 * (pixel_intensity[(int)vec.x][(int)vec.y]));
			pixelSetThread(data, vec, color);
		}
	}
	//FREE PIXEL INTENSITY
}

void		buddhabrot(t_fractal *fractal)
{
	pthread_t	pt[NB_THREADS];
	void		*data[NB_THREADS][4];
	void		*ret;
	int			id[NB_THREADS];
	int			i;

	exit(1);
	fractal->image_data.addr_image =
		mlx_get_data_addr(fractal->mlx_image, &fractal->image_data.bpp,
			&fractal->image_data.size_line, &fractal->image_data.endian);
	i = -1;
	while (++i < NB_THREADS)
	{
		data[i][0] = &fractal->image_data;
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

//(1.5 * (vec.x - 240)) / (0.5 * 240) = data->c.real
//(1.5 * (vec.x - 240)) / (0.5 * 240) = -1.5
//(1.5 * (vec.x - 240)) = (-1.5 * (0.5 * 480))
//vec.x = ((data->c.real * (0.5 * WIDTH_WINDOW)) / 1.5) + (WIDTH_WINDOW / 2)

//(vec.y - HEIGHT_WINDOW / 2) / (0.5 * HEIGHT_WINDOW) = data->c.im;
//vec.y = (data->c.im * (0.5 * HEIGHT_WINDOW)) + (HEIGHT_WINDOW / 2)

//new_real+ = (new.real * new.real) - (new.im * new.im) + c.real
//new_real+ = (new.real * new.real) - (new.im * new.im) + c.real
//new_real+ = ((new.real * new.real) - (new.im * new.im)) + ((1.5 * (vec.x - 240)) / (0.5 * 480))

//((new.real * new.real) - (new.im * new.im)) + ((1.5 * (vec.x - 240)) / (0.5 * 480)) = new.real+
//((new.real * new.real) - (new.im * new.im)) + ((1.5 * (vec.x - 240)) / (0.5 * 480)) = new.real+
//-(new.im * new.im)) + ((1.5 * (vec.x - 240)) / (0.5 * 480)) = new.real+ - (new.real * new.real)
//(1.5 * (vec.x - 240)) / (0.5 * 480) = (new.real+ - (new.real * new.real)) + (new.im * new.im)
//1.5 * (vec.x - 240) = ((new.real+ - (new.real * new.real)) + (new.im * new.im)) * (0.5 * 480)
//vec.x = ((((new.real+ - (new.real * new.real)) + (new.im * new.im)) * (0.5 * 480)) / 1.5) + 240
//vec.x = ((((new.real+ - (new.real * new.real)) + (new.im * new.im)) * (0.5 * WIDTH_WINDOW)) / 1.5) + (WIDTH_WINDOW / 2)

//new.im = 2 * tmp * new.im + c.im;
//(2 * tmp * new.im) + (vec.y - HEIGHT_WINDOW / 2) / (0.5 * HEIGHT_WINDOW) = new.im+;
//(vec.y - HEIGHT_WINDOW / 2) / (0.5 * HEIGHT_WINDOW) = (new.im+ - (2 * tmp * new.im))
//(vec.y - HEIGHT_WINDOW / 2) = ((new.im+ - (2 * tmp * new.im)) * (0.5 * HEIGHT_WINDOW))
//vec.y = ((new.im+ - (2 * tmp * new.im)) * (0.5 * HEIGHT_WINDOW)) + (HEIGHT_WINDOW / 2)