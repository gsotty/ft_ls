/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 14:05:53 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 10:53:31 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	len_nbr(size_t nbr)
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

static void		files_is_dev(size_t nbr_files, STAT *buf, t_struc_ls *struc)
{
	size_t			cont;
	struct group	*g;
	struct passwd	*p;
	size_t			len_nlink;
	size_t			len_size;

	cont = 0;
	while (cont < nbr_files)
	{
		p = getpwuid(buf[cont].st_uid);
		g = getgrgid(buf[cont].st_gid);
		len_nlink = len_nbr(buf[cont].st_nlink);
		len_size = len_nbr(buf[cont].st_size);
		if (struc->len.nlink < len_nlink)
			struc->len.nlink = len_nlink;
		struc->len.size = 8;
		if (struc->len.grname < ft_strlen(g->gr_name))
			struc->len.grname = ft_strlen(g->gr_name);
		if (struc->len.pwname < ft_strlen(p->pw_name))
			struc->len.pwname = ft_strlen(p->pw_name);
		cont++;
	}
}

static void		files_no_dev(size_t nbr_files, STAT *buf, t_struc_ls *struc)
{
	size_t			cont;
	struct group	*g;
	struct passwd	*p;
	size_t			len_nlink;
	size_t			len_size;

	cont = 0;
	while (cont < (size_t)nbr_files)
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

void			verif_len(STAT *buf, t_struc_ls *struc, int nbr_files)
{
	int				is_dev;
	size_t			mask;
	size_t			cont;

	is_dev = 0;
	cont = 0;
	mask = 1;
	mask = (mask << 8) - 1;
	while (cont < (size_t)nbr_files)
	{
		if ((S_ISCHR(buf[cont].st_mode) == 1) ||
				(S_ISBLK(buf[cont].st_mode) == 1))
			is_dev = 1;
		cont++;
	}
	cont = 0;
	if (is_dev == 1)
		files_is_dev(nbr_files, buf, struc);
	else
		files_no_dev(nbr_files, buf, struc);
}
