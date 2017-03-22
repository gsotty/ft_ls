/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_is_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:46:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/22 15:04:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	files_is_files(char *str, t_struc_ls *struc, STAT stat)
{
	size_t		mask;
	int			ret;
	char		*chemin;
	size_t		taille;

	mask = 1;
	taille = 32764;
	chemin = ft_memalloc(32764);
	struc->buf.files_or_dir[struc->len.cont_arg_2] = 1;
	if (!(struc->buf.xattr[struc->len.cont_arg_2] = ft_memalloc(
					sizeof(size_t) * 1)))
		return ;
	if (!(struc->buf.buf[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char *) * 1)))
		return ;
	if (!(struc->buf.save_name[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char) * struc->len.argv)))
		return ;
	if (!(struc->buf.stat[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(STAT) * struc->len.argv)))
		return ;
	if (!(struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
				[struc->len.cont_arg_2]] = ft_memalloc(sizeof(char *) *
					struc->len.argv)))
		return ;
	struc->buf.stat[struc->len.cont_arg_2][struc->buf.cont_files
		[struc->len.cont_arg_2]] = stat;
	ft_memcpy(struc->buf.save_name[struc->len.cont_arg_2], str,
			struc->len.argv);
	struc->buf.save_name[struc->len.cont_arg_2][struc->len.argv] = '\0';
	ft_memcpy(struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
			[struc->len.cont_arg_2]], str, struc->len.argv);
	struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
		[struc->len.cont_arg_2]][struc->len.argv] = '\0';
	if ((ret = listxattr(str, chemin, taille, XATTR_NOFOLLOW)) > 0 &&
			ft_strstr(str, "/usr") == NULL)
	{
		if (ret != -1)
		{
			struc->buf.xattr[struc->len.cont_arg_2][struc->buf.cont_files
				[struc->len.cont_arg_2]] = 1;
		}
	}
	mask = (mask << 8) - 1;
	struc->len.total = stat.st_blocks;
	struc->buf.cont_files[struc->len.cont_arg_2]++;
	struc->len.cont_arg_2++;
	free(chemin);
}
