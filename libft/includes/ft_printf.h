/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:45:03 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/10 15:50:42 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <float.h>

/*
**	------ FLAGS / MODIFIERS / CONVERSION VARIABLES ----
*/

# define L			1
# define LL			2
# define BIGL		3
# define H			4
# define HH			5
# define Z			6

# define CONVERSION	"cspdiouxXf%"
# define FLAGS		"#0-+ .*0123456789hlLz"
# define ALL		"#0-+ .*0123456789hlLzcspdiouxXf%"
# define LENGTH		"lLhz"

typedef struct	s_struct
{
	char		*format;
	int			printed;
	int			i;
	int			len;
	char		padding;
	int			minus;
	int			plus;
	int			space;
	int			zero;
	int			hash;
	int			width;
	int			precisiontf;
	int			precision;
	int			length;
	int			nb;
	int			sign;
	int			conv;
	int			conv2;
	int			conv3;
	int			x;
}				t_struct;

/*
** ---------- MAIN --------------------
*/

void			test_strings(char *s1, int r1, int r2, char *test_name);

/*
** ---------- FT_PRINTF ---------------
*/

int				ft_printf(const char *fmt, ...);

/*
** ---------- DISTRIBUTOR -------------
*/

void			distributor(t_struct *f, char c, va_list ap);

/*
** ---------- MODIFIER ----------------
*/

void			modifier(const char *format, t_struct *f, va_list ap);

/*
** ---------- C_CONVERSION ------------
*/

void			ifperc(t_struct *f);
void			ifchar(t_struct *f, va_list ap);
void			ifstring(t_struct *f, va_list ap);
void			ifpointer(t_struct *f, va_list ap);
void			ifoctal(t_struct *f, va_list ap);
void			ifudecint(t_struct *f, va_list ap);
void			iffloat(t_struct *f, va_list ap);
void			ifhex(t_struct *f, va_list ap);
void			ifint(t_struct *f, va_list ap);

/*
** ---------- HELPER_PRINT ------------
*/

void			printspace(t_struct *f, int nb);
void			printzero(t_struct *f, int nb);
void			widthstar(const char *format, t_struct *f, va_list ap);

/*
** ---------- HELPER_CONV -------------
*/

char			*pre_converter(char *str, t_struct *f, char c, int check);
char			*converter_r(char *str, size_t nb, t_struct *f, char c);
char			*leftaligned(t_struct *f, char *str);
char			*rightaligned(t_struct *f, char *str);
char			*converter_l(char *str, size_t nb, t_struct *f, char c);

/*
** ---------- HELPER_SWAP -------------
*/

char			*swap_plus_minus(char *joint, char c, int i);
char			*swap_zero_x_l(char *joint, char c, int i);
char			*swap_zero_x_r(char *joint, char c, int i);
char			*swap_space(char *joint, char c, int i);

#endif
