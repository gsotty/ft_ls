/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:05:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/11 15:24:16 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	len_nbr(size_t nbr)
{
	size_t	x;
	size_t	nbr_tmp;

	nbr_tmp = nbr;
	x = 1;
	while (nbr_tmp >= 10)
	{
		ft_printf("nbr_tmp = %d\n", nbr_tmp);
		nbr_tmp = nbr_tmp / 10;
		x++;
	}
	ft_printf("x = %d\n", x);
	return (x);
}

void	verif_len(STAT *buf, t_struc_ls *struc, int nbr_files)
{
	size_t			cont;
	struct group	*g;
	struct passwd	*p;

	cont = 0;
	while (cont < nbr_files)
	{
		p = getpwuid(buf[cont].st_uid);
		g = getgrgid(buf[cont].st_gid);
		ft_printf("111 %d - %d\n", struc->len.nlink, buf[cont].st_nlink);
		ft_printf("nlink = %d  len_nbr = %d\n", struc->len.nlink,
				len_nbr(buf[cont].st_nlink));
		if (((struc->len.nlink) < (len_nbr(buf[cont].st_nlink))))
		{
			ft_printf("222 %d\n", struc->len.nlink);
			ft_printf("%d %d\n", struc->len.nlink, len_nbr(buf[cont].st_nlink));
			struc->len.nlink = len_nbr(buf[cont].st_nlink);
			ft_printf("333 %d\n", struc->len.nlink);
			ft_printf("%d %d\n", struc->len.nlink, len_nbr(buf[cont].st_nlink));
		}
		ft_printf("444 %d\n", struc->len.nlink);
		ft_printf("%d %d\n", struc->len.nlink, len_nbr(buf[cont].st_nlink));
		if (struc->len.size < ft_strlen(ft_itoa(buf[cont].st_size)))
			struc->len.size = ft_strlen(ft_itoa(buf[cont].st_size));
		if (struc->len.grname < ft_strlen(g->gr_name))
			struc->len.grname = ft_strlen(g->gr_name);
		if (struc->len.pwname < ft_strlen(p->pw_name))
			struc->len.pwname = ft_strlen(p->pw_name);
		cont++;
	}
	ft_printf("nlink = %d\n", struc->len.nlink);
}