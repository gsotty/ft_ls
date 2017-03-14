/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:18:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/14 17:13:01 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		printf_l_nlik_tsix(t_struc_ls *struc, int x,
		int y)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	char			*tmp_join;

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
			tmp_join = ft_strjoin("Jun  1  ",
				ctime(&struc->buf.stat[y][x].st_mtime) + 20),
			struc->buf.buf[y][x]);
	free(tmp_perm);
	free(tmp_join);
}

static void		printf_l_lik_tsix_2(t_struc_ls *struc, int x, int y,
		char *test_1)
{
	struct group	*g;
	struct passwd	*p;
	char			*tmp_perm;
	char			*tmp_join;

	p = getpwuid(struc->buf.stat[y][x].st_uid);
	g = getgrgid(struc->buf.stat[y][x].st_gid);
	ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s -> %s\n"
			, tmp_perm =
			permision_l(&struc->buf.stat[y][x]),
			struc->len.nlink,
			struc->buf.stat[y][x].st_nlink,
			struc->len.pwname, p->pw_name,
			struc->len.grname,
			g->gr_name, struc->len.size,
			struc->buf.stat[y][x].st_size,
			tmp_join = ft_strjoin("Jun  1  ",
				ctime(&struc->buf.stat[y][x].st_mtime) + 20),
			struc->buf.buf[y][x], test_1);
	free(tmp_perm);
	free(tmp_join);
}

static void		printf_l_lik_tsix(t_struc_ls *struc, int x,
		int y, char **save_name)
{
	char			*tmp;
	char			*test_1;
	struct stat		stat_nlink;

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
			printf_l_lik_tsix_2(struc, x, y, test_1);
		free(test_1);
	}
	free(tmp);
}

static void		printf_l_nlik(t_struc_ls *struc, int x, int y)
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

static void		printf_l_lik(t_struc_ls *struc, int x, int y,
		char **save_name)
{
	char			*tmp;
	struct stat		stat_nlink;
	char			*test_1;

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

static void		ft_while_2(char **save_name, int x, int y, t_struc_ls *struc)
{
	long			time_day;
	long			time_files;

	time_day = time(&time_day);
	time_files = struc->buf.stat[y][x].st_mtime;
	if (!(time_files > time_day - 15778800 &&
				time_files < time_day + 60))
	{
		if (S_ISLNK(struc->buf.stat[y][x].st_mode) == 1)
			printf_l_lik_tsix(struc, x, y, save_name);
		else
			printf_l_nlik_tsix(struc, x, y);
	}
	else
	{
		if (S_ISLNK(struc->buf.stat[y][x].st_mode) == 1)
		{
			printf_l_lik(struc, x, y, save_name);
		}
		else
			printf_l_nlik(struc, x, y);
	}
}

static void		ft_while_buf_ls(char **save_name, int y, t_struc_ls *struc,
		int x)
{
	while (x < struc->buf.cont_files[y])
	{
		if (struc->flag.l_min == 1)
			ft_while_2(save_name, x, y, struc);
		else
			ft_printf("%s\n", struc->buf.buf[y][x]);
		if (struc->flag.r_maj == 0)
			free(struc->buf.buf[y][x]);
		x++;
	}
	write(1, "\n", 1);
	x = 0;
	while (x < struc->buf.cont_files[y] && struc->flag.r_maj == 1)
	{
		if (struc->flag.a_min == 1 && ft_strcmp(struc->buf.buf[y][x], ".")
				!= 0 && ft_strcmp(struc->buf.buf[y][x], "..") != 0)
			recursive_r_maj_files_ls(save_name[y], struc->buf.buf[y][x],
					struc);
		else if (struc->flag.a_min == 0)
			recursive_r_maj_files_ls(save_name[y], struc->buf.buf[y][x],
					struc);
		free(struc->buf.buf[y][x]);
		x++;
	}
}

void			write_buf_ls(char **save_name, int test, t_struc_ls *struc,
		long long total)
{
	int				y;

	y = 0;
	if (struc->flag.r_min == 1)
		order_r(save_name, struc);
	else
		order_no_r(save_name, struc);
	while (y < struc->len.cont_arg_2)
	{
		if (test == 0 || struc->flag.multi == 1)
			ft_printf("%s:\n", save_name[y]);
		if (struc->flag.l_min == 1)
			ft_printf("total %lld\n", total / 512);
		if (struc->flag.l_min == 1)
			verif_len(struc->buf.stat[y], struc, struc->buf.cont_files[y]);
		ft_while_buf_ls(save_name, y, struc, 0);
		free(struc->buf.save_name[y]);
		free(struc->buf.stat[y]);
		free(struc->buf.buf[y]);
		y++;
	}
	free(struc->buf.buf);
	free(struc->buf.save_name);
	free(struc->buf.cont_files);
	free(struc->buf.stat);
}
