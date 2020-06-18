/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifhex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:45:47 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:17 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	char	*length_check_x(unsigned long n, t_struct *f, va_list ap)
{
	if (f->length == L)
		n = (unsigned long int)va_arg(ap, uintmax_t);
	else if (f->length == LL)
		n = (unsigned long long int)va_arg(ap, uintmax_t);
	else if (f->length == H)
		n = (unsigned short)va_arg(ap, int);
	else if (f->length == HH)
		n = (unsigned char)va_arg(ap, int);
	else if (f->length == Z)
		n = (size_t)va_arg(ap, size_t);
	else if (f->length == 0)
		n = (unsigned int)va_arg(ap, unsigned int);
	return (ft_itoa_base(n, 16));
}

void			ifhex(t_struct *f, va_list ap)
{
	unsigned long		n;
	char				*str;
	int					len;

	n = 0;
	str = length_check_x(n, f, ap);
	(str[0] == '0' && f->precision == -1) ? str[0] = '\0' : 0;
	if (f->x == 1)
		ft_strupper(str);
	if (f->hash && str[0] != '0' && str[0] != '\0')
	{
		f->nb = f->precision - ft_strlen(str);
		(f->x == 1) ? str = pre_converter(str, f, 'X', 0) : 0;
		(f->x == 0) ? str = pre_converter(str, f, 'x', 0) : 0;
	}
	len = ft_strlen(str);
	(!f->hash) ? f->nb = f->precision - len : 0;
	(f->hash && str[1] == '\0') ? f->nb = f->precision - len : 0;
	if (f->precision > 0 && f->nb > 0)
		str = pre_converter(str, f, '0', 1);
	(f->minus == 1) ? str = leftaligned(f, str) : 0;
	(f->minus == 0) ? str = rightaligned(f, str) : 0;
	ft_putstr(str);
	f->printed += ft_strlen(str);
	ft_strdel(&str);
}
