/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 17:46:30 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/06/05 19:40:43 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** Put a pixel in a specific position defined by the draw_fractal() function.
** Change colors depending on the iteration level.
** If the iteration level is equal to the fractal depth, paint it black ;)
*/

static void		put_pixel(t_fractol *f, int depth)
{
	int			pos;
	
	pos = (f->fractal.height + (f->fractal.width * WIN_WIDTH)) * 4;
	if (f->fractal.height < WIN_WIDTH \
		&& f->fractal.width < WIN_HEIGHT \
			&& depth == f->fractal.iteration)
	{
		f->image.data[pos] = 0x00;
		f->image.data[pos + 1] = 0x00;
		f->image.data[pos + 2] = 0x00;
	}
	else if (f->fractal.height < WIN_WIDTH \
		&& f->fractal.width < WIN_HEIGHT)
	{
		f->image.data[pos] = f->color.red + (depth * 2.42);
		f->image.data[pos + 1] = f->color.green + (depth * 2.42);
		f->image.data[pos + 2] = f->color.blue + (depth * 2.42);	
	}
}

/*
** Draw the fractal from the fractal.type (selection), and put it on the
** window image.
** Colors will depend on the "depth level", each fractal function will return
** this level.
*/

static void		*draw_fractal(void *tab)
{
	t_fractol	*frac;
	int			depth;
	double		tmp_width;

	frac = (t_fractol *)tab;
	tmp_width = frac->fractal.width;
	while (frac->fractal.height < WIN_WIDTH)
	{
		frac->fractal.width = tmp_width;
		while (frac->fractal.width < frac->fractal.limit)
		{
			depth = (frac->fractal.type == 1) ? mandelbrot(frac) : depth;
			// depth = (frac->fractal.type == 2) ? julia(frac) : depth;
			put_pixel(frac, depth);
			frac->fractal.width += 1;
		}
		frac->fractal.height += 1;
	}
	return (tab);
	
}

/*
** The image is passed to this function, cutting it cut it into smaller section
** for the multithreading. Once all the image have been generated, the resulting
** image is put to the window and then destroyed.
*/

void			frac_pthread(t_fractol *f)
{
	t_fractol	tab[THREADS];
	pthread_t	t[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)&tab[i], (void *)f, sizeof(t_fractol));
		tab[i].fractal.width = ((double)(1.00 / THREADS) * WIN_WIDTH) * i;
		tab[i].fractal.limit = ((double)(1.00 / THREADS) * WIN_WIDTH) * (i + 1);
		i += 1;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_create(&t[i], NULL, draw_fractal, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(f->mlx.init, f->mlx.win, \
		f->mlx.img, 0, 0);
}

/*
** If mouse.state is on (1), get the x and y coordinates of the mouse cursor,
** and keep updating it to the fractol structure. This is used to manipulate
** the parameters of the fractals (ci, and cr).
*/

int			f_manipulate(int x, int y, t_fractol *f)
{
	if (f->mouse.state == 1 && (x > 0 && y > 0) \
		&& (x < WIN_WIDTH && y < WIN_HEIGHT))
	{
		f->mouse.pos_x = x;
		f->mouse.pos_y = y;
		fractol_update(f);
	}
	return (0);
}