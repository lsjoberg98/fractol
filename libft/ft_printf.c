/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:06:35 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:37:53 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	bezerostruct(t_struct *f)
{
	f->i = 0;
	f->printed = 0;
	f->sign = 0;
	f->len = 0;
	f->minus = 0;
	f->plus = 0;
	f->space = 0;
	f->zero = 0;
	f->hash = 0;
	f->width = 0;
	f->padding = 0;
	f->precisiontf = 0;
	f->precision = 0;
	f->length = 0;
	f->conv = 0;
	f->conv2 = 0;
	f->conv3 = 0;
	f->x = 0;
}

void	bezerostruct2(t_struct *f)
{
	f->printed = 0;
	f->sign = 0;
	f->len = 0;
	f->minus = 0;
	f->plus = 0;
	f->space = 0;
	f->zero = 0;
	f->hash = 0;
	f->width = 0;
	f->padding = 0;
	f->precisiontf = 0;
	f->precision = 0;
	f->length = 0;
	f->conv = 0;
	f->conv2 = 0;
	f->conv3 = 0;
	f->x = 0;
}

/*
**	Checks for flags and if it finds any it calls the modifier
**	else it goes to the distributor and after that sets struct to 0
**	but keeps the position of i
*/

int		parsel(t_struct *f, int pos, const char *format, va_list ap)
{
	f->i = pos;
	if (ft_strchr(FLAGS, format[pos]))
		modifier(format, f, ap);
	else
	{
		distributor(f, format[pos], ap);
		bezerostruct2(f);
	}
	pos = f->i;
	if (format[pos] == '\0')
		return (pos);
	return (pos - 1);
}

/*
**	Checks the format for what comes after the '%' sign and calls the parsel
*/

int		formatparse(const char *format, t_struct *f, va_list ap, int pos)
{
	while (format[pos] != '\0')
	{
		if (format[pos] != '%')
			f->printed += write(1, &format[pos], 1);
		else if (format[pos] == '%')
		{
			if (!(ft_strchr(ALL, format[pos + 1]) || format[pos] == '\0'))
				break ;
			while (ft_strchr(ALL, format[pos + 1]) && format[pos] != '\0')
			{
				pos++;
				if (ft_strchr(CONVERSION, format[pos]))
				{
					pos = parsel(f, pos, format, ap) + 2;
					break ;
				}
				else
					pos = parsel(f, pos, format, ap);
			}
			continue;
		}
		pos++;
	}
	return (f->printed);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			status;
	t_struct	*s;
	int			fmtlen;

	if (!(s = (t_struct*)malloc(sizeof(t_struct))))
		return (0);
	bezerostruct(s);
	s->format = (char *)format;
	va_start(ap, format);
	fmtlen = ft_strlen(format);
	if (!fmtlen)
		return (0);
	if (fmtlen == 1 && format[0] == '%')
		return (0);
	status = formatparse(format, s, ap, 0);
	va_end(ap);
	free(s);
	return (status);
}
