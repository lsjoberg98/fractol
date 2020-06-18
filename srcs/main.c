/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 20:57:14 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/06/08 15:34:15 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	selectf(char *arg, t_fractol *f)
{
    f->fractal.type = 0;
	if (ft_strequ(arg, "mandelbrot"))
		f->fractal.type = 1;
	else if (ft_strequ(arg, "julia"))
		f->fractal.type = 2;
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
	f->color.red = 0x42;
	f->color.green = 0x32;
	f->color.blue = 0x22;
	f->mouse.pos_x = WIN_WIDTH / 2;
	f->mouse.pos_y = WIN_HEIGHT / 2;
	if (f->fractal.type == 2)
	{
		f->fractal.x = -2.10;
		f->mouse.state = 1;
		f->fractal.iteration = 100;
	}
}

/*
** Refresh the image. Updates its values and prints the number of iterations
** and the zoom level (scale) of the fractal.
*/

void		fractol_update(t_fractol *f)
{
	if (f->fractal.iteration <= 0)
		f->fractal.iteration = 0;
	frac_pthread(f);
	mlx_string_put(f->mlx.init, f->mlx.win, 10, 5, 0xFFFFFF, \
		ft_itoa(f->fractal.iteration));
	mlx_string_put(f->mlx.init, f->mlx.win, 10, 35, 0xFFFFFF, \
		
		ft_itoa((int)f->fractal.scale));
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
		write(1, "Loser\n", 6);
	return (0);
}
