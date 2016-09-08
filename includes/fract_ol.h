/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pivanovi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 12:55:56 by pivanovi          #+#    #+#             */
/*   Updated: 2016/09/07 12:55:57 by pivanovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# define WIDTH_WINDOW 840
# define HEIGHT_WINDOW 620
# define TITLE "FRACT_OLOLOL"

# define DEFAULT_REAL -0.7
# define DEFAULT_IM 0.27015

# define ESC_KEYCODE 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define MAX_ITERATIONS 300

#include <mlx.h>

enum {
	JULIA,
	MANDELBROT,
	NB_ARGS
};

typedef void (*t_fp) (void *);



typedef struct		s_complex
{
	float			real;
	float			im;
}					t_complex;

typedef struct		s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct		s_values
{
	t_complex		c;
	float			zoom;
}					t_values;

typedef struct		s_var
{
	t_fp			function_pointers[NB_ARGS];
	int				*focus;
	int				actual_focus;
	char			**args;
	void			*mlx_core;
	void			**mlx_windows;
	void			**mlx_images;
	char			**addr_images;
	t_values		*fractal_values;
	int				size_line;
	int				endian;
	int				bpp;
	int				nb_windows;
	t_vector		dir;
	int				recalc;
}					t_var;

void	main_loop(t_var *vars);

void	setVars(t_var *vars);
void	cleanVars(t_var *vars);
char	argsValid(t_var *vars, int ac, char **av);

int		getIndexFocus(int *tab, int len, int focus);

void	julia(void *data);
void	calculateJulia(t_var *vars, t_complex c, float zoom, int index_window);

void	mandelbrot(void *data);

void	pixelSet(t_var *vars, t_vector pos, int color, int index_window);

void	strLower(char *str);

#endif
