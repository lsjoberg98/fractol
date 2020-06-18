/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:04:52 by lsjoberg          #+#    #+#             */
/*   Updated: 2019/10/19 15:06:30 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int	*tab;

	if (min >= max)
	{
		tab = NULL;
		return (tab);
	}
	if (!(tab = malloc(sizeof(int) * (max - min))))
		return (NULL);
	while (max >= min)
	{
		tab[max - min - 1] = max - 1;
		max--;
	}
	return (tab);
}
