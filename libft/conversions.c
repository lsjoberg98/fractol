/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 20:33:24 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:36 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
**	checks the specifier
*/

void	distributor(t_struct *f, char c, va_list ap)
{
	(c == 'c') ? ifchar(f, ap) : 0;
	(c == 's') ? ifstring(f, ap) : 0;
	(c == 'p') ? ifpointer(f, ap) : 0;
	(c == '%') ? ifperc(f) : 0;
	(c == 'd' || c == 'i') ? ifint(f, ap) : 0;
	if (c == 'o' || c == 'u' || c == 'x' || c == 'X')
	{
		f->conv = 1;
		(c == 'o') ? ifoctal(f, ap) : 0;
		(c == 'u') ? ifudecint(f, ap) : 0;
		if (c == 'x' || c == 'X')
		{
			f->conv2 = 1;
			(c == 'X') ? f->x = 1 : 0;
			ifhex(f, ap);
		}
	}
	if (c == 'f')
	{
		f->conv3 = 1;
		iffloat(f, ap);
	}
}
