/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orber.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:03:10 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 17:52:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	order_r(char **save_name, t_struc_ls *struc)
{
	if (struc->flag.t_min == 1 || struc->flag.s_maj == 1)
	{
		order_no_t_r(save_name, struc);
		order_t_r(save_name, struc);
	}
	else
		order_no_t_r(save_name, struc);
}

static void	order_no_r(char **save_name, t_struc_ls *struc)
{
	if (struc->flag.t_min == 1 || struc->flag.s_maj == 1)
	{
		order_no_t_no_r(save_name, struc);
		order_t_no_r(save_name, struc);
	}
	else
		order_no_t_no_r(save_name, struc);
}

void		order(char **save_name, t_struc_ls *struc)
{
	if (struc->flag.r_min == 1)
		order_r(save_name, struc);
	else
		order_no_r(save_name, struc);
}
