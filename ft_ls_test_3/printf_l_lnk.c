/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l_lnk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:19:50 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 11:39:46 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static void		printf_l_lik_dir(t_struc_ls *struc, int x, int y,
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

void			printf_l_lik(t_struc_ls *struc, int x, int y,
		char **save_name)
{
	char		*test_1;

	test_1 = ft_memalloc(256);
	if (struc->buf.files_or_dir[y] == 1)
	{
		if ((readlink(struc->buf.buf[y][x], test_1, 256)) == -1)
		{
			ft_printf("ls: ");
			perror(struc->buf.buf[y][x]);
		}
		else
			printf_l_lik_2(struc, x, y, test_1);
	}
	else
		printf_l_lik_dir(struc, x, y, save_name);
	free(test_1);
}
