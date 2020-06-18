/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifoctal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:06:57 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:25 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	char	*length_check_o(unsigned long n, t_struct *f, va_list ap)
{
	if (f->length == L)
		n = (unsigned long)va_arg(ap, unsigned long);
	else if (f->length == LL)
		n = (unsigned long long)va_arg(ap, unsigned long long);
	else if (f->length == H)
		n = (unsigned short)va_arg(ap, unsigned int);
	else if (f->length == HH)
		n = (unsigned char)va_arg(ap, unsigned int);
	else if (f->length == Z)
		n = (size_t)va_arg(ap, size_t);
	else if (f->length == 0)
		n = va_arg(ap, unsigned int);
	return (ft_itoa_base)(n, 8);
}

void			ifoctal(t_struct *f, va_list ap)
{
	unsigned long		n;
	char				*str;

	n = 0;
	str = length_check_o(n, f, ap);
	(str[0] == '0' && f->precision == -1) ? str[0] = '\0' : 0;
	if (f->hash)
		str = pre_converter(str, f, '0', 0);
	f->nb = f->precision - ft_strlen(str);
	if (f->precision > 0 && f->nb > 0)
		str = pre_converter(str, f, '0', 1);
	if (f->minus == 1)
		str = leftaligned(f, str);
	else if (f->minus == 0)
		str = rightaligned(f, str);
	ft_putstr(str);
	f->printed += ft_strlen(str);
	ft_strdel(&str);
}
