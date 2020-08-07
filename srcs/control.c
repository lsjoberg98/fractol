/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 13:57:43 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/08/07 15:19:10 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** Increase the scale of the fractal, depending of the mouse position (x and y),
** and increase the iteration level.
** Saves the position to x_pos and y_pos, used later by zoom_out() function.
** The zoom level is capped with the SCALE_LIMIT macro.
*/

static void		zoom_in(int x, int y, t_fractol *f)
{
	if (f->fractal.scale >= SCALE_LIMIT)
	{
		f->fractal.scale = SCALE_LIMIT;
		f->color.blue++;
		return ;
	}
	if (f->mouse.state == 1)
	{
		f->mouse.pos_x = x;
		f->mouse.pos_y = y;
	}
	f->fractal.x = (x / f->fractal.scale + f->fractal.x) - \
		((f->fractal.scale * SCALE_PRECISION) / 2);
	f->fractal.x += ((f->fractal.scale * SCALE_PRECISION) / 2) - \
		(x / (f->fractal.scale * SCALE_PRECISION));
	f->fractal.y = (y / f->fractal.scale + f->fractal.y) - \
		((f->fractal.scale * SCALE_PRECISION) / 2);
	f->fractal.y += ((f->fractal.scale * SCALE_PRECISION) / 2) - \
		(y / (f->fractal.scale * SCALE_PRECISION));
	f->fractal.scale *= SCALE_PRECISION;
	if (f->fractal.type == 1 || f->fractal.type == 4)
		f->color.red++;
}

/*
** Decrease the scale level and the iteration level.
** Uses the mouse position from zoom_in() function.
*/

static void		zoom_out(t_fractol *f)
{
	f->fractal.x = (f->mouse.pos_x / f->fractal.scale + f->fractal.x) - \
		((f->fractal.scale / SCALE_PRECISION) / 2);
	f->fractal.x += ((f->fractal.scale / SCALE_PRECISION) / 2) - \
		(f->mouse.pos_x / (f->fractal.scale / SCALE_PRECISION));
	f->fractal.y = (f->mouse.pos_y / f->fractal.scale + f->fractal.y) - \
		((f->fractal.scale / SCALE_PRECISION) / 2);
	f->fractal.y += ((f->fractal.scale / SCALE_PRECISION) / 2) - \
		(f->mouse.pos_y / (f->fractal.scale / SCALE_PRECISION));
	f->fractal.scale /= SCALE_PRECISION;
	if (f->fractal.type == 1 || f->fractal.type == 4)
		f->color.red--;
}

static void		rand_color(t_fractol *f)
{
	f->color.red = rand() % (0x7F + 0x01);
	f->color.green = rand() % (0x7F + 0x01);
	f->color.blue = rand() % (0x7F + 0x01);
}

int				frac_mouse(int mousecode, int x, int y, t_fractol *f)
{
	if (x > 0 && y > 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		if (mousecode == MOUSE_UP_SCRLL)
			zoom_in(x, y, f);
		else if (mousecode == MOUSE_DOWN_SCRLL)
			zoom_out(f);
		else if (mousecode == MOUSE_MIDDLE_CLK)
			fractol_init(f);
		else if (mousecode == MOUSE_RIGHT_CLK)
			rand_color(f);
		else if (mousecode == MOUSE_LEFT_CLK)
			f->mouse.state = (f->mouse.state == 1) ? 0 : 1;
		fractol_update(f);
	}
	return (0);
}

int				frac_keys(int keycode, t_fractol *f)
{
	if (keycode == KEY_ESCAPE)
		exit(0);
	else if (keycode == KEY_ANSI_W || keycode == KEY_UPARROW)
		f->fractal.y -= 10 / f->fractal.scale;
	else if (keycode == KEY_ANSI_A || keycode == KEY_LEFTARROW)
		f->fractal.x -= 10 / f->fractal.scale;
	else if (keycode == KEY_ANSI_S || keycode == KEY_DOWNARROW)
		f->fractal.y += 10 / f->fractal.scale;
	else if (keycode == KEY_ANSI_D || keycode == KEY_RIGHTARROW)
		f->fractal.x += 10 / f->fractal.scale;
	else if (keycode == KEY_ANSI_E)
		zoom_in((WIN_WIDTH / 2), (WIN_HEIGHT / 2), f);
	else if (keycode == KEY_ANSI_Q)
		zoom_out(f);
	else if (keycode == KEY_ANSI_R)
		fractol_init(f);
	else if (keycode == KEY_SPACE)
		rand_color(f);
	else if (keycode == KEY_ANSI_Z)
		f->fractal.iteration += 10;
	else if (keycode == KEY_ANSI_X)
		f->fractal.iteration -= 10;
	fractol_update(f);
	return (0);
}
