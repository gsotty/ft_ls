/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 15:28:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/21 15:28:47 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_precision(t_struc *struc, const char *str, int z, int y)
{
	while (y < z)
	{
		if (str[y] == '.')
		{
			struc->precision.number = ft_atoi((char *)str + y + 1);
			return (1);
		}
		y++;
	}
	struc->precision.number = -1;
	return (0);
}
