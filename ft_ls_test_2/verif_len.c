/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:05:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/07 12:08:53 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	verif_len(STAT *buf, t_struc_ls *struc)
{
	size_t			cont;
	struct group	*g;
	struct passwd	*p;

	cont = 0;
	while (cont < struc->nbr_files)
	{
		p = getpwuid(buf[cont].st_uid);
		g = getgrgid(buf[cont].st_gid);
		if (struc->len.nlink < ft_strlen(ft_itoa(buf[cont].st_nlink)))
			struc->len.nlink = ft_strlen(ft_itoa(buf[cont].st_nlink));
		if (struc->len.size < ft_strlen(ft_itoa(buf[cont].st_size)))
			struc->len.size = ft_strlen(ft_itoa(buf[cont].st_size));
		if (struc->len.grname < ft_strlen(g->gr_name))
			struc->len.grname = ft_strlen(g->gr_name);
		if (struc->len.pwname < ft_strlen(p->pw_name))
			struc->len.pwname = ft_strlen(p->pw_name);
		cont++;
	}
}
