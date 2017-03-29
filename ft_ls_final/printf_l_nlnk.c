/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l_nlnk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:20:11 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 11:20:22 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		printf_is_dev(t_struc_ls *struc, int x, int y)
{
	size_t			mask;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	mask = 1;
	mask = (mask << 8) - 1;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*zd %-*s  %-*s %4d,%4d %.12s %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			(int)struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			(int)struc->len.pwname,
			p->pw_name,
			(int)struc->len.grname,
			g->gr_name,
			struc->buf.stat[y][x].st_rdev >> 24,
			struc->buf.stat[y][x].st_rdev & mask,
			ctime(&struc->buf.stat[y][x].st_mtime) + 4,
			struc->buf.buf[y][x]);
	free(tmp_perm);
}

static void		printf_no_dev(t_struc_ls *struc, int x, int y)
{
	size_t			mask;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	mask = 1;
	mask = (mask << 8) - 1;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*zd %-*s  %-*s  %*lld %.12s %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			(int)struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			(int)struc->len.pwname,
			p->pw_name,
			(int)struc->len.grname,
			g->gr_name,
			(int)struc->len.size,
			struc->buf.stat[y][x].st_size,
			ctime(&struc->buf.stat[y][x].st_mtime) + 4,
			struc->buf.buf[y][x]);
	free(tmp_perm);
}

void			printf_l_nlik(t_struc_ls *struc, int x, int y)
{
	if ((S_ISCHR(struc->buf.stat[y][x].st_mode) == 1) ||
			(S_ISBLK(struc->buf.stat[y][x].st_mode) == 1))
		printf_is_dev(struc, x, y);
	else
		printf_no_dev(struc, x, y);
}
