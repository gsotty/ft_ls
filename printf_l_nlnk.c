/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l_nlnk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:20:11 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 16:48:47 by gsotty           ###   ########.fr       */
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
	if (struc->flag.s_min == 1)
		ft_printf("%*d ", struc->len.blocks, struc->buf.stat[y][x].st_blocks);
	ft_printf("%s %*zd %-*s  %-*s %4d,%4d %.*s %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			(int)struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			(int)struc->len.pwname,
			p->pw_name,
			(int)struc->len.grname,
			g->gr_name,
			struc->buf.stat[y][x].st_rdev >> 24,
			struc->buf.stat[y][x].st_rdev & mask,
			T_MAJ,
			ctime(LEN_TIME) + 4,
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
	if (struc->flag.s_min == 1)
		ft_printf("%*d ", struc->len.blocks, struc->buf.stat[y][x].st_blocks);
	ft_printf("%s %*zd %-*s  %-*s  %*lld %.*s %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			(int)struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			(int)struc->len.pwname,
			p->pw_name,
			(int)struc->len.grname,
			g->gr_name,
			(int)struc->len.size,
			struc->buf.stat[y][x].st_size,
			T_MAJ,
			ctime(LEN_TIME) + 4,
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
