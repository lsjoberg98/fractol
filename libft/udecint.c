/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udecint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 18:55:29 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:40:01 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	char	*length_check_u(unsigned long n, t_struct *f, va_list ap)
{
	if (f->length == L)
		n = (unsigned long int)va_arg(ap, long int);
	else if (f->length == LL)
		n = (unsigned long long int)va_arg(ap, long long int);
	else if (f->length == H)
		n = (unsigned short int)va_arg(ap, int);
	else if (f->length == HH)
		n = (unsigned char)va_arg(ap, int);
	else if (f->length == Z)
		n = (size_t)va_arg(ap, size_t);
	else if (f->length == 0)
		n = (unsigned int)va_arg(ap, unsigned int);
	return (ft_itoa_base(n, 10));
}

void			ifudecint(t_struct *f, va_list ap)
{
	unsigned long		n;
	char				*str;

	n = 0;
	str = length_check_u(n, f, ap);
	f->nb = f->precision - ft_strlen(str);
	(str[0] == '0' && f->precision == -1) ? str[0] = '\0' : 0;
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
