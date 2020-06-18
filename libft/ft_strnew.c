/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:23:24 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/02/08 15:32:40 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *area;

	if (!(area = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(area, '\0', (size + 1));
	return (area);
}
