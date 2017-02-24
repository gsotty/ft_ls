/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:29:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:29:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_isnum(int c)
{
	if (('0' <= c && c <= '9'))
		return (1);
	return (0);
}

int			check_width(t_struc *struc, const char *str, int z, int y)
{
	while (y < z && str[y] != '.')
	{
		if ((ft_isnum(str[y]) == 1) && str[y] != '0')
		{
			struc->width.number = ft_atoi((char *)str + y);
			return (1);
		}
		y++;
	}
	return (0);
}
