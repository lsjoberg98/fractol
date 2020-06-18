/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:24:37 by lsjoberg          #+#    #+#             */
/*   Updated: 2019/10/16 17:39:49 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last_pos;

	last_pos = 0;
	while (*str)
	{
		if (*str == c)
			last_pos = (char*)str;
		str++;
	}
	if (last_pos)
		return (last_pos);
	if (c == '\0')
		return ((char*)str);
	return (0);
}
