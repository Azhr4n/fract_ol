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

# define WIDTH_WINDOW 480
# define HEIGHT_WINDOW 320
# define TITLE "FRACT_OLOLOL"

# define DEFAULT_REAL -0.7
# define DEFAULT_IM 0.27015
# define DEFAULT_REAL_ADD 0.0001
# define DEFAULT_IM_ADD 0.0001

# define ESC_KEYCODE 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define MINUS 78
# define PLUS 69
# define RESET 117
# define SHIFT 257

# define MAX_ITERATIONS 2048
# define MAX_ITERATIONS_B 250
# define NB_THREADS 24

# define MIN(a, b) (((a) < (b)) ? (a) : (b))

# define ABPP &fractal->image_data[i].bpp
# define ASL &fractal->image_data[i].size_line
# define AEN &fractal->image_data[i].endian

#include <pthread.h>
#include <mlx.h>

enum {
	JULIA,
	MANDELBROT,
	BUDDHABROT,
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
	double			real;
	double			im;
}					t_complex;

typedef struct		s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct		s_area
{
	t_vector		start;
	t_vector		end;
}					t_area;

typedef struct		s_node
{
	t_vector		pos;
	void			*next;
}					t_node;

typedef	struct		s_image_value
{
	t_area			area;
	double			zoom;
	t_vector		pos;
	t_vector		vec;
	t_complex		new;
	t_complex		c;
}					t_image_value;

typedef	struct		s_image_data
{
	char			*addr_image;
	int				size_line;
	int				endian;
	int				bpp;
	int				***color_map;
}					t_image_data;

typedef struct		s_fractal
{
	void			*mlx_window;
	void			*mlx_image[NB_THREADS];
	t_image_data	image_data[NB_THREADS];
	t_image_value	image_value;
	int				print;
	int				type;
	
}					t_fractal;

typedef void (*t_fp) (t_fractal *);

typedef struct		s_thread
{
	pthread_t		pt[NB_THREADS];
	void			*ret[NB_THREADS];
	int				id[NB_THREADS];
}					t_thread;

typedef struct		s_var
{
	t_fp			function_pointers[NB_ARGS];
	char			**args;
	int				nb_windows;
	void			*mlx_core;
	int				focus;
	t_fractal		*fractals;
	t_vector		dir;
	int				shift;
	float			real_const_val;
	float			im_const_val;
	t_vector		mouse_pos;
	int				fract_set;
}					t_var;

void	main_loop(t_var *vars);

void	setVars(t_var *vars);
void	cleanVars(t_var *vars);
int		argsValid(t_var *vars, int ac, char **av);

int		getIndexFocus(int *tab, int len, int focus);

void	*threadFunction(void *packed_data);

void	julia(t_fractal *fractal);
int		iteratingJulia(t_complex new, t_complex c);
void	calculateJulia(t_image_data *data, t_image_value value, void *ptr);

void	mandelbrot(t_fractal *fractal);
int		iteratingMandelbrot(t_complex new, t_complex c);
void	calculateMandelbrot(t_image_data *data, t_image_value value, void *ptr);

void	buddhabrot(t_fractal *fractal);
// int		iteratingBuddhabrot(t_complex new, t_complex c);
// void	calculateBuddhabrot(t_image_data *data, t_area area,
// 	int (*f)(t_complex, t_complex));

void	pixelSetThread(t_image_data *data, t_vector vec, t_vector start,
	int color);
int		setColor(int iterations, int r, int g, int b);

void	strLower(char *str);
void	free2Dint(int **tab, int width);

t_node	*createNewNode(float x, float y);
t_node	*insertNodeAtEnd(t_node *node, t_node *new);
void	clearList(t_node **node);



#endif
