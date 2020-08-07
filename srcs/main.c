/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 20:57:14 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/08/07 15:05:59 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	f_usage(void)
{
	ft_putstr("Usage: ");
	ft_putstr("./fractol mandelbrot | julia | burningship | sphere\n");
	ft_putendl("Keys:");
	ft_putendl("\t[E]               -> Zoom in");
	ft_putendl("\t[Q]               -> Zoom out");
	ft_putendl("\t[Z]               -> Iterations++");
	ft_putendl("\t[X]               -> Iterations--");
	ft_putendl("\t[R]               -> Reset values");
	ft_putendl("\t[SPACE]           -> Colorize");
	ft_putendl("\t[W][A][S][D]      -> Move");
	ft_putendl("\t[ESC]             -> Exit");
	ft_putendl("Mouse:");
	ft_putendl("\t[SCROLL]          -> Zoom");
	ft_putendl("\t[RIGHT CLK]       -> Colorize");
	ft_putendl("\t[MIDDLE CLK]      -> Reset values");
	ft_putendl("\t[LEFT CLK]        -> Manipulate fractal");
}

static int	selectf(char *arg, t_fractol *f)
{
	f->fractal.type = 0;
	if (ft_strequ(arg, "mandelbrot"))
		f->fractal.type = 1;
	else if (ft_strequ(arg, "julia"))
		f->fractal.type = 2;
	else if (ft_strequ(arg, "burningship"))
		f->fractal.type = 3;
	else if (ft_strequ(arg, "sphere"))
		f->fractal.type = 4;
	else
	{
		ft_putstr(arg);
		ft_putendl(" is not a valid parameter");
	}
	return (f->fractal.type);
}

void		fractol_init(t_fractol *f)
{
	f->fractal.x = -2.60;
	f->fractal.y = -1.20;
	f->fractal.scale = 300.00;
	f->fractal.iteration = 42;
	f->color.red = 19;
	f->color.green = -200;
	f->color.blue = 42;
	f->mouse.pos_x = WIN_WIDTH / 2;
	f->mouse.pos_y = WIN_HEIGHT / 2;
	if (f->fractal.type == 2)
	{
		f->fractal.x = -2.10;
		f->mouse.state = 1;
		f->fractal.iteration = 100;
	}
	if (f->fractal.type == 4)
		f->fractal.iteration = 200;
}

/*
** Refresh the image. Updates its values and prints the number of iterations
** and the zoom level (scale) of the fractal.
*/

void		fractol_update(t_fractol *f)
{
	char *iter;
	char *size;

	iter = ft_itoa(f->fractal.iteration);
	size = ft_itoa(f->fractal.scale);
	if (f->fractal.iteration <= 0)
		f->fractal.iteration = 0;
	frac_pthread(f);
	mlx_string_put(f->mlx.init, f->mlx.win, 10, 5, 0xFFFFFF, iter);
	mlx_string_put(f->mlx.init, f->mlx.win, 10, 35, 0xFFFFFF, size);
	free(iter);
	free(size);
}

/*
** Main function, creates the fractol structure and a network connection between
** the program and the x-server, making it possible to draw on the screen,
** getting the keyboard and mouse inputs.
*/

int			main(int ac, char *av[])
{
	t_fractol	*f;

	if (ac == 2)
	{
		if (!(f = (t_fractol *)malloc(sizeof(t_fractol))))
			ft_error("Memory Allocation failed", 1);
		if (!(selectf(av[1], f)))
			ft_error("Please try again", 2);
		f->mlx.init = mlx_init();
		f->mlx.win = mlx_new_window(f->mlx.init, WIN_WIDTH, \
			WIN_HEIGHT, TITLE(av[1]));
		f->mlx.img = mlx_new_image(f->mlx.init, WIN_WIDTH, WIN_HEIGHT);
		f->image.data = mlx_get_data_addr(f->mlx.img, \
		&f->image.pxc, &f->image.size, &f->image.endian);
		fractol_init(f);
		fractol_update(f);
		mlx_hook(f->mlx.win, 2, 3, frac_keys, f);
		mlx_hook(f->mlx.win, 4, 3, frac_mouse, f);
		mlx_hook(f->mlx.win, 6, 3, f_manipulate, f);
		mlx_loop(f->mlx.init);
	}
	else
		f_usage();
	return (0);
}
