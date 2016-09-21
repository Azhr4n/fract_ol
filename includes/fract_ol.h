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

# define VTFF vars->fractals[i].mlx_image[inc]

# define CX(x) 1.5 * (x - WIDTH_WINDOW / 2) / (0.5 * value.zoom * WIDTH_WINDOW)
# define CY(y) (y - HEIGHT_WINDOW / 2) / (0.5 * value.zoom * HEIGHT_WINDOW)

# define RFX roundf(value.vec.x)
# define RFY roundf(value.vec.y)

# define RFXC (RFX < WIDTH_WINDOW && RFX >= 0)
# define RFYC (RFY < WIDTH_WINDOW && RFY >= 0)

# include <pthread.h>
# include <mlx.h>

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
	t_vector		step;
	t_node			*list;
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

typedef void		(*t_fp) (t_fractal *);
typedef int			(*t_bob)(t_complex, t_complex);

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

void				main_loop(t_var *vars);

void				set_vars(t_var *vars);
void				clean_vars(t_var *vars);
int					args_valid(t_var *vars, int ac, char **av);

void				*thread_func(void *packed_data);

void				julia(t_fractal *fractal);
void				mandelbrot(t_fractal *fractal);
void				buddhabrot(t_fractal *fractal);

int					my_key_pressed(int keycode, void *param);
int					my_key_released(int keycode, void *param);
int					my_button_hook(int button, int x, int y, void *param);
int					refresh(void *param);

void				set_fractal_values(t_var *vars);
void				set_constant(t_var *vars, int type, float value);
void				set_zoom(t_var *vars, int type, float value, int id);
int					my_mouse_hook(int x, int y, void *param);
void				change_constant_values(int keycode, t_var *vars);

void				pixel_set_thread(t_image_data *data,
	t_vector vec, t_vector start, int color);
int					set_color(int iterations, int r, int g, int b);

void				free2d_int(int **tab, int width);
void				str_lower(char *str);
int					**allocate_color_map(int width, int height);
void				set_buddha_values(t_image_value value,
	t_complex *c, t_complex *new);

t_node				*create_new_node(float x, float y);
t_node				*insert_node_at_end(t_node *node, t_node *new);
void				clear_list(t_node **node);

#endif
