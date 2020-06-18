/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:01:33 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/01/23 23:01:37 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int nb)
{
	size_t	i;
	char	*copy;

	if (!(copy = ft_strnew(nb)))
		return (NULL);
	i = 0;
	while (s1[i] && i < (size_t)nb)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
