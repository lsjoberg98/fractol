/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 16:05:49 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/05/12 16:28:17 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int			mandelbrot(t_fractol *f)
{
	double	zr;
	double	zi;
	double	cr;
	double	ci;
	double	tmp_zr;

	f->fractal.depth = 0;
	zr = (f->mouse.pos_x - WIN_WIDTH) / ((double)WIN_WIDTH * 2) + 0.25;
	zi = (f->mouse.pos_y - WIN_HEIGHT) / ((double)WIN_HEIGHT) + 0.50;
	ci = f->fractal.width / f->fractal.scale + f->fractal.y;
	cr = f->fractal.height / f->fractal.scale + f->fractal.x;
	while (FT_SQUARE(zr) + FT_SQUARE(zi) < 4 \
			&& f->fractal.depth < f->fractal.iteration)
	{
		tmp_zr = zr;
		zr = FT_SQUARE(zr) - FT_SQUARE(zi) + cr;
		zi = (2 * zi) * tmp_zr + ci;
		f->fractal.depth += 1;
	}
	return (f->fractal.depth);
}
