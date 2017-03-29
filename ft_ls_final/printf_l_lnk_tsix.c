/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l_lnk_tsix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 11:31:48 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 16:48:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		printf_l_lik_tsix_2_t(t_struc_ls *struc, int x, int y,
		char *test_1)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	if (struc->flag.s_min == 1)
		ft_printf("%*d ", struc->len.blocks, struc->buf.stat[y][x].st_blocks);
	ft_printf("%s %*d %-*s  %-*s  %*lld %.*s %s -> %s\n"
			, tmp_perm =
			permision_l(&struc->buf.stat[y][x], y, x, struc),
			struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			struc->len.pwname, p->pw_name,
			struc->len.grname,
			g->gr_name, struc->len.size,
			struc->buf.stat[y][x].st_size,
			T_MAJ,
			ctime(LEN_TIME) + 4,
			struc->buf.buf[y][x], test_1);
	free(tmp_perm);
}

static void		printf_l_lik_tsix_2(t_struc_ls *struc, int x, int y,
		char *test_1)
{
	char			*time;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	time = ctime(LEN_TIME) + 4;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	time[ft_strlen(time) - 1] = '\0';
	if (struc->flag.s_min == 1)
		ft_printf("%*d ", struc->len.blocks, struc->buf.stat[y][x].st_blocks);
	ft_printf("%s %*d %-*s  %-*s  %*lld %.6s  %d %s -> %s\n"
			, tmp_perm =
			permision_l(&struc->buf.stat[y][x], y, x, struc),
			struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			struc->len.pwname, p->pw_name,
			struc->len.grname,
			g->gr_name, struc->len.size,
			struc->buf.stat[y][x].st_size,
			time, ft_atoi(time + 15),
			struc->buf.buf[y][x], test_1);
	free(tmp_perm);
}

static void		printf_l_lik_t_six_dir(t_struc_ls *struc, int x, int y,
		char **save_name)
{
	char			*tmp;
	char			*test_1;

	tmp = ft_memalloc(32767);
	ft_sprintf(tmp, "%s/%s", save_name[y],
			struc->buf.buf[y][x]);
	test_1 = ft_memalloc(256);
	if ((readlink(tmp, test_1, 256)) == -1)
	{
		ft_printf("2ls: ");
		perror(tmp);
	}
	else if (struc->flag.t_maj == 1)
		printf_l_lik_tsix_2_t(struc, x, y, test_1);
	else
		printf_l_lik_tsix_2(struc, x, y, test_1);
	free(test_1);
	free(tmp);
}

void			printf_l_lik_tsix(t_struc_ls *struc, int x,
		int y, char **save_name)
{
	char			*test_1;

	test_1 = ft_memalloc(256);
	if (struc->buf.files_or_dir[y] == 1)
	{
		if ((readlink(save_name[y], test_1, 256)) == -1)
		{
			ft_printf("ls: ");
			perror(save_name[y]);
		}
		else
			printf_l_lik_tsix_2(struc, x, y, test_1);
	}
	else
		printf_l_lik_t_six_dir(struc, x, y, save_name);
	free(test_1);
}
