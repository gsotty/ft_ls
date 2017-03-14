/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:21:17 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/14 17:26:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			printf_l_nlik(t_struc_ls *struc, int x, int y)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*zd %-*s  %-*s  %*lld %.12s %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x]),
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

static void		printf_l_lik_2(t_struc_ls *struc, int x, int y, char *test_1)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s -> %s\n",
			tmp_perm = permision_l(&struc->buf.stat[y][x]),
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
	struct stat	stat_nlink;
	char		*test_1;

	tmp = ft_memalloc(32767);
	sprintf(tmp, "%s/%s", save_name[y],
			struc->buf.buf[y][x]);
	if (stat(tmp, &stat_nlink))
	{
		ft_printf("ls :");
		perror(tmp);
	}
	else
	{
		test_1 = ft_memalloc(256);
		if ((readlink(tmp, test_1, 256)) == -1)
		{
			ft_printf("ls: ");
			perror(tmp);
		}
		else
			printf_l_lik_2(struc, x, y, test_1);
		free(test_1);
	}
	free(tmp);
}
