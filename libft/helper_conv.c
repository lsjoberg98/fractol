/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:09:40 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/22 18:32:53 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

/*
**	Check 0 joins 0x with the string to print in hexa.
**	Check 1 || 2
*/

char	*pre_converter(char *str, t_struct *f, char c, int check)
{
	char	*tmp;
	char	*joint;

	if (check == 0)
	{
		(str[0] == '0' && c == '0') ? joint = ft_strdup(str) : 0;
		(str[0] != '0' && c == '0') ? joint = ft_strjoin("0", str) : 0;
		(c == 'x') ? joint = ft_strjoin("0x", str) : 0;
		(c == 'X') ? joint = ft_strjoin("0X", str) : 0;
	}
	if (check == 1 || check == 2)
	{
		tmp = ft_strcnew(f->nb, c);
		joint = ft_strjoin(tmp, str);
		free(tmp);
	}
	if (check == 3)
		if ((f->plus && !f->sign) || f->sign)
		{
			(f->plus && !f->sign) ? joint = ft_strjoin("+", str) : 0;
			(f->sign) ? joint = ft_strjoin("-", str) : 0;
		}
	free(str);
	return (joint);
}

char	*converter_l(char *str, size_t nb, t_struct *f, char c)
{
	char	*joint;
	char	*tmp;
	int		i;

	joint = NULL;
	tmp = NULL;
	i = 0;
	tmp = ft_strcnew(nb, c);
	joint = ft_strjoin(str, tmp);
	free(tmp);
	free(str);
	if (f->hash && f->conv2 && (f->width || f->precision))
		joint = swap_zero_x_l(joint, 'c', i);
	return (joint);
}

char	*converter_r(char *str, size_t nb, t_struct *f, char c)
{
	char	*joint;
	char	*tmp;
	int		i;

	joint = NULL;
	tmp = NULL;
	tmp = ft_strcnew(nb, c);
	joint = ft_strjoin(tmp, str);
	i = 0;
	free(tmp);
	free(str);
	if (f->zero && f->width && (f->plus || f->minus)
		&& !f->precision && !f->conv)
		joint = swap_plus_minus(joint, c, i);
	else if (f->zero && f->width && (f->sign || f->plus)
		&& f->conv3)
		joint = swap_plus_minus(joint, c, i);
	if (f->hash && f->conv2 && (f->width || f->precision))
		joint = swap_zero_x_r(joint, c, i);
	(f->space && f->width) ? joint = swap_space(joint, c, i) : 0;
	return (joint);
}

char	*leftaligned(t_struct *f, char *str)
{
	int		nb;
	char	*joint;

	joint = NULL;
	nb = f->width - ft_strlen(str);
	if (nb > 0)
		return (joint = converter_l(str, nb, f, ' '));
	if (nb < 0 && f->nb > 0 && f->conv2)
		return (joint = swap_zero_x_l(str, '0', 0));
	return (str);
}

char	*rightaligned(t_struct *f, char *str)
{
	int		nb;
	char	*joint;

	joint = NULL;
	nb = f->width - ft_strlen(str);
	if (nb > 0)
	{
		if (f->zero == 1 && f->width > 0 && !f->sign
			&& !f->precision)
			return (joint = converter_r(str, nb, f, '0'));
		else if (f->zero && f->width > 0 && f->conv3)
			return (joint = converter_r(str, nb, f, '0'));
		else if (f->zero && !f->precision)
		{
			joint = converter_r(str, nb, f, '0');
			return (joint = swap_plus_minus(joint, '+', 0));
		}
		else
			return (joint = converter_r(str, nb, f, ' '));
	}
	if (nb < 0 && f->nb > 0 && f->conv2)
		return (joint = swap_zero_x_r(str, '0', 0));
	return (str);
}
