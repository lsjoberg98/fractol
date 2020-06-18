/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:59:15 by lsjoberg          #+#    #+#             */
/*   Updated: 2019/10/18 17:18:32 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*x;
	char	*y;
	size_t	i;

	i = 0;
	y = (char *)src;
	x = (char *)dst;
	if (y < x)
	{
		while (len)
		{
			len--;
			*(x + len) = *(y + len);
		}
	}
	else
		ft_memcpy(x, y, len);
	return (dst);
}
