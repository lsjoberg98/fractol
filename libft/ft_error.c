/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 22:29:10 by lsjoberg          #+#    #+#             */
/*   Updated: 2020/08/07 15:07:19 by lsjoberg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Outputs the string msg to the standard output followed by an exit of the
** program with a custom return value (defined by ret).
*/

void	ft_error(char *reason, int ret)
{
	ft_putendl(reason);
	exit(ret);
}
