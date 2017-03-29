/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l_nlnk_tsix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:31:00 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 17:57:35 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		printf_is_dev_t(t_struc_ls *struc, int x, int y)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	size_t			mask;

	mask = 1;
	mask = (mask << 8) - 1;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*zd %-*s  %-*s  %4d,%4d %.*s %s\n",
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

static void		printf_no_dev_t(t_struc_ls *struc, int x, int y)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	size_t			mask;

	mask = 1;
	mask = (mask << 8) - 1;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
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

static void		printf_is_dev(t_struc_ls *struc, int x, int y)
{
	char			*time;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	size_t			mask;

	mask = 1;
	mask = (mask << 8) - 1;
	time = ctime(LEN_TIME) + 4;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	time[ft_strlen(time) - 1] = '\0';
	ft_printf("%s %*zd %-*s  %-*s  %4d,%4d %.6s  %d %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			(int)struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			(int)struc->len.pwname,
			p->pw_name,
			(int)struc->len.grname,
			g->gr_name,
			struc->buf.stat[y][x].st_rdev >> 24,
			struc->buf.stat[y][x].st_rdev & mask,
			time, ft_atoi(time + 15),
			struc->buf.buf[y][x]);
	free(tmp_perm);
}

static void		printf_no_dev(t_struc_ls *struc, int x, int y)
{
	char			*time;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	size_t			mask;

	mask = 1;
	mask = (mask << 8) - 1;
	time = ctime(LEN_TIME) + 4;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	time[ft_strlen(time) - 1] = '\0';
	ft_printf("%s %*zd %-*s  %-*s  %*lld %.6s  %d %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			(int)struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			(int)struc->len.pwname,
			p->pw_name,
			(int)struc->len.grname,
			g->gr_name,
			(int)struc->len.size,
			struc->buf.stat[y][x].st_size,
			time, ft_atoi(time + 15),
			struc->buf.buf[y][x]);
	free(tmp_perm);
}

void			printf_l_nlik_tsix(t_struc_ls *struc, int x,
		int y)
{
	if (struc->flag.s_min == 1)
		ft_printf("%*d ", struc->len.blocks, struc->buf.stat[y][x].st_blocks);
	if (struc->flag.t_maj == 1)
	{
		if ((S_ISCHR(struc->buf.stat[y][x].st_mode) == 1) ||
				(S_ISBLK(struc->buf.stat[y][x].st_mode) == 1))
			printf_is_dev_t(struc, x, y);
		else
			printf_no_dev_t(struc, x, y);
	}
	else
	{
		if ((S_ISCHR(struc->buf.stat[y][x].st_mode) == 1) ||
				(S_ISBLK(struc->buf.stat[y][x].st_mode) == 1))
			printf_is_dev(struc, x, y);
		else
			printf_no_dev(struc, x, y);
	}
}
