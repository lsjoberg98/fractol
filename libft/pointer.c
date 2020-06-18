/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 20:48:55 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/21 19:39:57 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ifpointer(t_struct *f, va_list ap)
{
	unsigned long long	p;
	char				*str;
	char				*joint;
	int					nb;

	p = va_arg(ap, unsigned long long);
	str = ft_itoa_base((unsigned long long)p, 16);
	(str[0] == '0' && f->precision == -1) ? str[0] = '\0' : 0;
	joint = ft_strjoin("0x", str);
	nb = f->width - (ft_strlen(joint));
	if ((f->minus == 0 && nb > 0))
		(f->zero == 1) ? printzero(f, nb) : printspace(f, nb);
	if (f->minus == 1 && nb > 0)
	{
		ft_putstr(joint);
		printspace(f, nb);
	}
	else
		ft_putstr(joint);
	f->printed += ft_strlen(joint);
	free(str);
	free(joint);
}
