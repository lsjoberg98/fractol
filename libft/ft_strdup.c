/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:54:41 by lsjoberg          #+#    #+#             */
/*   Updated: 2019/10/29 11:22:29 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		size;

	size = ft_strlen(src) + 1;
	if (!(new = (char *)malloc(sizeof(char) * size)))
		return (0);
	new = ft_memcpy(new, src, size);
	return (new);
}
