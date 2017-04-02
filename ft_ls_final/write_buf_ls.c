/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:18:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/30 17:37:14 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_while_2(char **save_name, int x, int y, t_struc_ls *struc)
{
	long			time_day;
	long			time_files;

	time_day = time(&time_day);
	time_files = TIME;
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
			printf_l_lik(struc, x, y, save_name);
		else
			printf_l_nlik(struc, x, y);
	}
}

static void		ft_while_buf_ls_2(char **save_name, int y, t_struc_ls *struc,
		int x)
{
	if (struc->flag.l_min == 1)
		ft_while_2(save_name, x, y, struc);
	else
	{
		if (struc->flag.s_min == 1)
			ft_printf("%*d ", struc->len.blocks,
					struc->buf.stat[y][x].st_blocks);
		ft_printf("%s\n", struc->buf.buf[y][x]);
	}
	if (struc->flag.r_maj == 0)
		free(struc->buf.buf[y][x]);
}

static void		ft_while_buf_ls(char **save_name, int y, t_struc_ls *struc,
		int x)
{
	while (x < struc->buf.cont_files[y])
	{
		ft_while_buf_ls_2(save_name, y, struc, x);
		x++;
	}
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

static void		write_files(int y, char **save_name, t_struc_ls *struc,
		long long total)
{
	if ((struc->flag.l_min == 1 || struc->flag.s_min) &&
			struc->buf.files_or_dir[y] == 0 && struc->buf.cont_files[y] != 0)
		ft_printf("total %lld\n", (total));
	if (struc->flag.l_min == 1 || struc->flag.s_min)
		verif_len(struc->buf.stat[y], struc, struc->buf.cont_files[y]);
	ft_while_buf_ls(save_name, y, struc, 0);
	free(struc->buf.save_name[y]);
	free(struc->buf.stat[y]);
	free(struc->buf.buf[y]);
	free(struc->buf.xattr[y]);
}

void			write_buf_ls(char **save_name, int test, t_struc_ls *struc,
		long long total)
{
	int				y;

	y = 0;
	if (struc->flag.f_min == 0)
		order(save_name, struc);
	while (y < struc->len.cont_arg_2)
	{
		if ((y < struc->len.cont_arg_2) && struc->buf.files_or_dir[y] == 0 &&
				y != 0)
			write(1, "\n", 1);
		if ((test == 0 || struc->flag.multi == 1) &&
				struc->buf.files_or_dir[y] == 0)
			ft_printf("%s:\n", save_name[y]);
		write_files(y, save_name, struc, total);
		y++;
	}
	free(struc->buf.xattr);
	free(struc->buf.files_or_dir);
	free(struc->buf.buf);
	free(struc->buf.save_name);
	free(struc->buf.cont_files);
	free(struc->buf.stat);
}
