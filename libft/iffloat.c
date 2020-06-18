/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iffloat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 14:58:31 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:13 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	char	*length_check_f(long double n, t_struct *f, va_list ap)
{
	if (f->length == BIGL)
		n = (long double)va_arg(ap, long double);
	else
		n = (long double)va_arg(ap, double);
	(n < 0) ? f->sign = 1 : 0;
	if (f->precision == 0)
	{
		f->precision = 6;
		f->precisiontf = 1;
	}
	else if (f->hash && f->precision == -1
		&& !f->precisiontf && n != 0)
	{
		f->precisiontf = 1;
		f->precision = 0;
	}
	return (ft_ftoa(n, f->precision, f->precisiontf));
}

void			iffloat(t_struct *f, va_list ap)
{
	char			*str;
	long double		n;

	n = 0;
	str = length_check_f(n, f, ap);
	f->nb = f->precision - ft_strlen(str);
	if (f->space && !f->sign)
	{
		f->nb = 1;
		str = pre_converter(str, f, ' ', 2);
	}
	if (((f->plus && !f->sign) || f->sign) && str[0] != '-')
		str = pre_converter(str, f, '+', 3);
	if (f->minus == 1)
		str = leftaligned(f, str);
	else if (f->minus == 0)
		str = rightaligned(f, str);
	ft_putstr(str);
	f->printed += ft_strlen(str);
	ft_strdel(&str);
}
