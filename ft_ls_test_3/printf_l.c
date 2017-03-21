/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:21:17 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/21 15:07:01 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			printf_l_nlik(t_struc_ls *struc, int x, int y)
{
	size_t			mask;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	mask = 1;
	mask = (mask << 8) - 1;
	if ((S_ISCHR(struc->buf.stat[y][x].st_mode) == 1) ||
			(S_ISBLK(struc->buf.stat[y][x].st_mode) == 1))
	{
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
	else
	{
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
}

static void		printf_l_lik_2(t_struc_ls *struc, int x, int y, char *test_1)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s -> %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x], y, x, struc),
			struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			struc->len.pwname,
			p->pw_name,
			struc->len.grname,
			g->gr_name,
			struc->len.size,
			struc->buf.stat[y][x].st_size,
			ctime(&struc->buf.stat[y][x].st_mtime) + 4,
			struc->buf.buf[y][x], test_1);
	free(tmp_perm);
}

void			printf_l_lik(t_struc_ls *struc, int x, int y,
		char **save_name)
{
	char		*tmp;
	char		*test_1;

	tmp = ft_memalloc(32767);
	ft_sprintf(tmp, "%s/%s", save_name[y],
			struc->buf.buf[y][x]);
	test_1 = ft_memalloc(256);
	if ((readlink(tmp, test_1, 256)) == -1)
	{
		ft_printf("ls: ");
		perror(tmp);
	}
	else
		printf_l_lik_2(struc, x, y, test_1);
	free(test_1);
	free(tmp);
}
