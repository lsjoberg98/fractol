/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:02:36 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:20 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	char	*length_check_int(intmax_t n, t_struct *f, va_list ap)
{
	if (f->length == L)
		n = (long int)va_arg(ap, long int);
	else if (f->length == LL)
		n = (long long int)va_arg(ap, long long int);
	else if (f->length == H)
		n = (short int)va_arg(ap, int);
	else if (f->length == HH)
		n = (signed char)va_arg(ap, int);
	else if (f->length == Z)
		n = (size_t)va_arg(ap, size_t);
	else if (f->length == 0)
		n = (int)va_arg(ap, int);
	if (n < 0)
	{
		f->sign = 1;
		n *= -1;
	}
	return (ft_itoa_base(n, 10));
}

void			ifint(t_struct *f, va_list ap)
{
	intmax_t		n;
	char			*str;

	n = 0;
	str = length_check_int(n, f, ap);
	f->nb = f->precision - ft_strlen(str);
	(str[0] == '0' && f->precision == -1) ? str[0] = '\0' : 0;
	if (f->precision > 0 && f->nb > 0)
		str = pre_converter(str, f, '0', 1);
	if (f->space && !f->sign)
	{
		f->nb = 1;
		str = pre_converter(str, f, ' ', 2);
	}
	if ((f->plus && !f->sign) || f->sign)
		str = pre_converter(str, f, '+', 3);
	if (f->minus == 1)
		str = leftaligned(f, str);
	else if (f->minus == 0)
		str = rightaligned(f, str);
	ft_putstr(str);
	f->printed += ft_strlen(str);
	ft_strdel(&str);
}
