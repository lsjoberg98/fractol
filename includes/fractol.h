/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 20:57:46 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/08/10 13:31:05 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <time.h>

# include "mlx.h"
# include "keys.h"
# include "mouse.h"
# include "libft.h"

# define FT_SQUARE(x)		(x * x)
# define WIN_WIDTH			(1080)
# define WIN_HEIGHT			(720)
# define THREADS			(8)
# define TITLE(fractal)		(fractal)
# define SCALE_LIMIT		(500000000)
# define SCALE_PRECISION	(1.042)

typedef struct	s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}				t_mlx;

typedef struct	s_type
{
	int		type;
	int		depth;
	int		iteration;
	double	width;
	double	height;
	double	scale;
	double	limit;
	double	x;
	double	y;
}				t_type;

typedef struct	s_mouse
{
	int		state;
	int		pos_x;
	int		pos_y;
}				t_mouse;

typedef struct	s_image
{
	char	*data;
	int		size;
	int		endian;
	int		pxc;
}				t_image;

typedef struct	s_color
{
	int		red;
	int		green;
	int		blue;
}				t_color;

typedef struct	s_fractol
{
	t_mlx	mlx;
	t_mouse	mouse;
	t_color	color;
	t_type	fractal;
	t_image	image;
}				t_fractol;

void			fractol_init(t_fractol *f);
void			fractol_update(t_fractol *f);

int				frac_keys(int keycode, t_fractol *f);
int				frac_mouse(int mousecode, int x, int y, t_fractol *f);

void			frac_pthread(t_fractol *f);
int				f_manipulate(int x, int y, t_fractol *f);
void			color_change(t_fractol *f);

int				mandelbrot(t_fractol *f);
int				julia(t_fractol *f);
int				burningship(t_fractol *f);
int				sphere(t_fractol *f);

#endif
