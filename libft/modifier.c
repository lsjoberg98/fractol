/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 19:21:12 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/22 18:30:20 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
**	Checks for flags and sets 1 to thee struct for the flag it found.
*/

static	void	flags(const char *format, t_struct *f)
{
	while (ft_strchr("-+ #0", format[f->i]))
	{
		if (format[f->i] == '-')
			f->minus = 1;
		if (format[f->i] == '+')
			f->plus = 1;
		if (format[f->i] == ' ')
			f->space = 1;
		if (format[f->i] == '#')
			f->hash = 1;
		if (format[f->i] == '0')
			f->zero = 1;
		f->i++;
	}
	if (f->plus == 1)
		f->space = 0;
}

/*
**	if there is a '*' we use widthstar otherwise we convert width to int.
**	and move the index forward.
*/

void			width(const char *format, t_struct *f, va_list ap)
{
	widthstar(format, f, ap);
	if (format[f->i] >= '0' && format[f->i] <= '9')
		f->width = ft_atoi(&format[f->i]);
	while (format[f->i] >= '0' && format[f->i] <= '9')
		f->i++;
}

static	void	precision(const char *format, t_struct *f, va_list ap, int nb)
{
	if (format[f->i] == '.')
	{
		f->precision = -1;
		f->precisiontf = 0;
		f->i++;
		if (format[f->i] >= '0' && format[f->i] <= '9')
		{
			f->precision = ft_atoi(&format[f->i]);
			(f->precision == 0) ? f->precision = -1 : 0;
			(f->precision >= 1) ? f->precisiontf = 1 : 0;
		}
		else if (format[f->i] == '*')
		{
			nb = va_arg(ap, int);
			(nb >= 0) ? f->precision = nb : 0;
			(nb >= 0) ? f->precisiontf = 1 : 0;
			while (format[f->i] == '*')
				f->i++;
		}
	}
	while (format[f->i] >= '0' && format[f->i] <= '9')
		f->i++;
}

/*
**	Checks the length letters and asigns the value to f->length
*/

static	void	length(const char *format, t_struct *f)
{
	if (format[f->i] == 'h')
	{
		if (format[f->i + 1] == 'h')
			f->length = HH;
		else if (format[f->i - 1] != 'h')
			f->length = H;
	}
	if (format[f->i] == 'l')
	{
		if (format[f->i + 1] == 'l')
			f->length = LL;
		else if (format[f->i - 1] != 'l')
			f->length = L;
	}
	(format[f->i] == 'L') ? f->length = BIGL : 0;
	(format[f->i] == 'z') ? f->length = Z : 0;
	while (ft_strchr(LENGTH, format[f->i]) && format[f->i])
		f->i++;
}

void			modifier(const char *format, t_struct *f, va_list ap)
{
	flags(format, f);
	width(format, f, ap);
	precision(format, f, ap, 0);
	length(format, f);
}
