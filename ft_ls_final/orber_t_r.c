/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orber_t_r.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 14:12:22 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 15:53:13 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap_orber(int x, int y, t_struc_ls *struc)
{
	size_t			tmp_xattr;
	char			*tmp_buf;
	struct stat		tmp_stat;

	tmp_xattr = struc->buf.xattr[x][y];
	struc->buf.xattr[x][y] = struc->buf.xattr[x][y + 1];
	struc->buf.xattr[x][y + 1] = tmp_xattr;
	tmp_buf = ft_strdup(struc->buf.buf[x][y]);
	free(struc->buf.buf[x][y]);
	struc->buf.buf[x][y] =
		ft_strdup(struc->buf.buf[x][y + 1]);
	free(struc->buf.buf[x][y + 1]);
	struc->buf.buf[x][y + 1] = ft_strdup(tmp_buf);
	free(tmp_buf);
	tmp_stat = struc->buf.stat[x][y];
	struc->buf.stat[x][y] = struc->buf.stat[x][y + 1];
	struc->buf.stat[x][y + 1] = tmp_stat;
}

static void	orber_files(int x, t_struc_ls *struc)
{
	int				y;
	int				verif_2;

	verif_2 = 1;
	while (verif_2 == 1)
	{
		y = 0;
		verif_2 = 0;
		while (y < struc->buf.cont_files[x] - 1)
		{
			if (ORD_1 > ORD_21)
			{
				swap_orber(x, y, struc);
				verif_2 = 1;
			}
			y++;
		}
	}
}

static int	verif_order(int x, char **save_name, t_struc_ls *struc)
{
	int			tmp;

	tmp = struc->buf.files_or_dir[x];
	struc->buf.files_or_dir[x] = struc->buf.files_or_dir[x + 1];
	struc->buf.files_or_dir[x + 1] = tmp;
	orber_dir_t_r(x, save_name, struc);
	return (1);
}

static int	diff_order(int x, int verif, char **save_name, t_struc_ls *struc)
{
	struct stat		stat_tmp;
	struct stat		stat_tmp_2;

	if ((lstat(save_name[x], &stat_tmp)) == -1)
		return (-1);
	if ((lstat(save_name[x + 1], &stat_tmp_2)) == -1)
		return (-1);
	if (ORD > ORD_2 && struc->buf.files_or_dir[x] == 0)
		verif = verif_order(x, save_name, struc);
	else if (ORD > ORD_2 && struc->buf.files_or_dir[x] == 1 &&
			struc->buf.files_or_dir[x + 1] == 1)
		verif = verif_order(x, save_name, struc);
	else if (struc->buf.files_or_dir[x] == 0 &&
			struc->buf.files_or_dir[x + 1] == 1)
		verif = verif_order(x, save_name, struc);
	return (verif);
}

void		order_t_r(char **save_name, t_struc_ls *struc)
{
	int				x;
	int				verif;

	verif = 1;
	while (verif == 1)
	{
		x = 0;
		verif = 0;
		orber_files(x, struc);
		while (x < struc->len.cont_arg_2 - 1)
		{
			if ((verif = diff_order(x, verif, save_name, struc)) == -1)
				return ;
			x++;
			orber_files(x, struc);
		}
	}
}
