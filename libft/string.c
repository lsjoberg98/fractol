/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 17:50:30 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:39:49 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static	char	*str_precision(char *str, int n)
{
	char	*tmp;

	if (n > 0 && (size_t)n <= ft_strlen(str))
	{
		tmp = ft_strndup(str, n);
		str = tmp;
		free(tmp);
		return (str);
	}
	if (n == -1)
		str = "";
	return (str);
}

void			ifstring(t_struct *f, va_list ap)
{
	char	*str;
	int		nb;

	str = va_arg(ap, char *);
	(str == NULL) ? str = "(null)" : 0;
	str = str_precision(str, f->precision);
	nb = f->width - ft_strlen(str);
	if (f->minus == 0 && nb > 0)
	{
		if (f->zero == 1)
			printzero(f, nb);
		else
			printspace(f, nb);
	}
	if (f->minus == 1 && nb > 0)
	{
		ft_putstr(str);
		printspace(f, nb);
	}
	else
		ft_putstr(str);
	f->printed += ft_strlen(str);
}
