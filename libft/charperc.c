/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charperc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:52:48 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:33 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
**	Prints zeroes/spaces depending on the value of minus and zero
**	and prints the '%' sign too.
*/

void	ifperc(t_struct *f)
{
	int				nb;

	nb = f->width - 1;
	if (f->minus == 0 && f->width)
	{
		if (f->zero == 1)
			printzero(f, nb);
		else
			printspace(f, nb);
	}
	if (f->minus == 1 && f->width)
	{
		ft_putchar('%');
		printspace(f, nb);
	}
	else
		ft_putchar('%');
	f->printed++;
}

/*
**	If zero = 1 print zeroes, otherwise print spaces and
**	and then do putchar(c) and some spaces if minus = 1,
**	otherwise just putchar(c).
*/

void	ifchar(t_struct *f, va_list ap)
{
	unsigned char	c;
	int				nb;

	nb = f->width - 1;
	c = (unsigned char)va_arg(ap, int);
	if (f->minus == 0 && f->width)
	{
		if (f->zero == 1)
			printzero(f, nb);
		else if (!f->zero)
			printspace(f, nb);
	}
	if (f->width && f->minus == 1)
	{
		ft_putchar(c);
		printspace(f, nb);
	}
	else
		ft_putchar(c);
	f->printed++;
}
