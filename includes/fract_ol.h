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

# define WIDTH_WINDOW 500
# define HEIGHT_WINDOW 500
# define TITLE "FRACT_OLOLOL"

# define ESC_KEYCODE 53

#include <mlx.h>

enum {
	JULIA,
	MANDELBROT,
	NB_ARGS
};

typedef void (*t_fp) (void *);

typedef struct		s_var
{
	t_fp			function_pointers[NB_ARGS];
	int				args_valid[NB_ARGS];
	char			**args;
	void			*mlx_core;
	void			**mlx_windows;
	void			**mlx_images;
	char			**addr_images;
	int				size_line;
	int				endian;
	int				bpp;
	int				nb_windows;
	int				max_window;
	int				max_iterations;
}					t_var;

typedef struct		s_complex
{
	int				real;
	int				im;
}					t_complex;


void	main_loop(t_var *vars);
int		myKeyHook(int keycode, void *param);

void	setVars(t_var *vars);
void	cleanVars(t_var *vars);
char	argsValid(t_var *vars, int ac, char **av);


void	julia(void *data);
void	mandelbrot(void *data);

void	strLower(char *str);

#endif
