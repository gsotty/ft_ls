/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_dir_t_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 10:33:37 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 10:33:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		orber_dir_t_r(int x, char **save_name, t_struc_ls *struc)
{
	int				tmp_cont;
	char			*tmp_name;
	char			**tmp_buf_x;
	struct stat		*tmp_stat_x;
	size_t			*tmp_xattr_x;

	tmp_xattr_x = struc->buf.xattr[x];
	struc->buf.xattr[x] = struc->buf.xattr[x + 1];
	struc->buf.xattr[x + 1] = tmp_xattr_x;
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
