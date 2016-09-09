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
# define NB_THREADS 2

# define V_VALUES vars->fractals[index].values

#include <mlx.h>

enum {
	JULIA,
	MANDELBROT,
	NB_ARGS
};

enum {
	REAL,
	IM
};

enum {
	MUL,
	DIV
};

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

typedef struct		s_area
{
	t_vector		start;
	t_vector		end;
}					t_area;

typedef struct		s_values
{
	t_complex		c;
	t_complex		old;
	t_complex		new;
	t_vector		pos;
	t_vector		vec;
	float			zoom;
}					t_values;

typedef struct		s_fractal
{
	int				type;
	void			*mlx_window;
	void			*mlx_image;
	char			*addr_image;
	int				size_line;
	int				endian;
	int				bpp;
	int				print;
	t_values		values;
}					t_fractal;

typedef void (*t_fp) (void *, t_fractal *);

typedef struct		s_var
{
	t_fp			function_pointers[NB_ARGS];
	char			**args;
	int				nb_windows;
	void			*mlx_core;
	t_fractal		*fractals;
	t_vector		dir;
	int				fract_set;
}					t_var;

void	main_loop(t_var *vars);

void	setVars(t_var *vars);
void	cleanVars(t_var *vars);
int		argsValid(t_var *vars, int ac, char **av);

int		getIndexFocus(int *tab, int len, int focus);

void	julia(void *mlx_core, t_fractal *fractal);
void	mandelbrot(void *mlx_core, t_fractal *fractal);

void	pixelSet(void *mlx_core, t_fractal *fractal, int color);

void	strLower(char *str);

#endif
