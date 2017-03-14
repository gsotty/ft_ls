/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orber_no_t_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 13:59:44 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/14 14:00:45 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap_orber(int x, int y, t_struc_ls *struc)
{
	char			*tmp_buf;
	struct stat		tmp_stat;

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
			if ((ft_strcmp(struc->buf.buf[x][y],
							struc->buf.buf[x][y + 1])) < 0)
			{
				swap_orber(x, y, struc);
				verif_2 = 1;
			}
			y++;
		}
	}
}

static void	orber_dir(int x, char **save_name, t_struc_ls *struc)
{
	int				tmp_cont;
	char			*tmp_name;
	char			**tmp_buf_x;
	struct stat		*tmp_stat_x;

	tmp_cont = struc->buf.cont_files[x];
	struc->buf.cont_files[x] = struc->buf.cont_files[x + 1];
	struc->buf.cont_files[x + 1] = tmp_cont;
	tmp_buf_x = struc->buf.buf[x];
	struc->buf.buf[x] = struc->buf.buf[x + 1];
	struc->buf.buf[x + 1] = tmp_buf_x;
	tmp_stat_x = struc->buf.stat[x];
	struc->buf.stat[x] = struc->buf.stat[x + 1];
	struc->buf.stat[x + 1] = tmp_stat_x;
	tmp_name = ft_strdup(save_name[x]);
	free(save_name[x]);
	save_name[x] = ft_strdup(save_name[x + 1]);
	free(save_name[x + 1]);
	save_name[x + 1] = ft_strdup(tmp_name);
	free(tmp_name);
}

void		order_no_t_r(char **save_name, t_struc_ls *struc)
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
			if ((ft_strcmp(save_name[x], save_name[x + 1])) < 0)
			{
				orber_dir(x, save_name, struc);
				verif = 1;
			}
			x++;
		}
	}
}
