/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_l_tsix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:15:26 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/21 12:23:20 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			printf_l_nlik_tsix(t_struc_ls *struc, int x,
		int y)
{
	char			*time;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	size_t			mask;

	mask = 1;
	mask = (mask << 8) - 1;
	if ((S_ISCHR(struc->buf.stat[y][x].st_mode) == 1) ||
			(S_ISBLK(struc->buf.stat[y][x].st_mode) == 1))
	{
		time = ctime(&struc->buf.stat[y][x].st_mtime) + 4;
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
	else
	{
		time = ctime(&struc->buf.stat[y][x].st_mtime) + 4;
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
}

static void		printf_l_lik_tsix_2(t_struc_ls *struc, int x, int y,
		char *test_1)
{
	char			*time;
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;

	time = ctime(&struc->buf.stat[y][x].st_mtime) + 4;
	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	time[ft_strlen(time) - 1] = '\0';
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

void			printf_l_lik_tsix(t_struc_ls *struc, int x,
		int y, char **save_name)
{
	char			*tmp;
	char			*test_1;

	tmp = ft_memalloc(32767);
	if (ft_strcmp(save_name[y], "/etc") == 0)
	{
		test_1 = ft_memalloc(256);
		if ((readlink(save_name[y], test_1, 256)) == -1)
		{
			ft_printf("ls: ");
			perror(tmp);
		}
		else
			printf_l_lik_tsix_2(struc, x, y, test_1);
	}
	else
	{
		ft_sprintf(tmp, "%s/%s", save_name[y],
				struc->buf.buf[y][x]);
		test_1 = ft_memalloc(256);
		if ((readlink(tmp, test_1, 256)) == -1)
		{
			ft_printf("ls: ");
			perror(tmp);
		}
		else
			printf_l_lik_tsix_2(struc, x, y, test_1);
	}
	free(test_1);
	free(tmp);
}
