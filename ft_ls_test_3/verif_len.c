/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:05:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/14 11:29:16 by gsotty           ###   ########.fr       */
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
		nbr_tmp = nbr_tmp / 10;
		x++;
	}
	return (x);
}

void	verif_len(STAT *buf, t_struc_ls *struc, int nbr_files)
{
	size_t			cont;
	struct group	*g;
	struct passwd	*p;
	int				len_nlink;
	int				len_size;

	cont = 0;
	while (cont < nbr_files)
	{
		p = getpwuid(buf[cont].st_uid);
		g = getgrgid(buf[cont].st_gid);
		len_nlink = len_nbr(buf[cont].st_nlink);
		len_size = len_nbr(buf[cont].st_size);
		if (struc->len.nlink < len_nlink)
			struc->len.nlink = len_nlink;
		if (struc->len.size < len_size)
			struc->len.size = len_size;
		if (struc->len.grname < ft_strlen(g->gr_name))
			struc->len.grname = ft_strlen(g->gr_name);
		if (struc->len.pwname < ft_strlen(p->pw_name))
			struc->len.pwname = ft_strlen(p->pw_name);
		cont++;
	}
}
