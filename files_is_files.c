/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_is_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:46:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 09:49:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	malloc_struc(t_struc_ls *struc)
{
	struc->buf.files_or_dir[struc->len.cont_arg_2] = 1;
	if (!(struc->buf.xattr[struc->len.cont_arg_2] = ft_memalloc(
					sizeof(size_t) * 1)))
		return (-1);
	if (!(struc->buf.buf[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char *) * 1)))
		return (-1);
	if (!(struc->buf.save_name[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char) * struc->len.argv)))
		return (-1);
	if (!(struc->buf.stat[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(STAT) * struc->len.argv)))
		return (-1);
	if (!(struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
				[struc->len.cont_arg_2]] = ft_memalloc(sizeof(char *) *
					struc->len.argv)))
		return (-1);
	return (1);
}

static void	verif_xattr(char *str, t_struc_ls *struc)
{
	int			ret;
	char		*chemin;
	size_t		taille;

	taille = 32764;
	chemin = ft_memalloc(32764);
	if ((ret = listxattr(str, chemin, taille, XATTR_NOFOLLOW)) > 0)
	{
		if (ret != -1)
		{
			struc->buf.xattr[struc->len.cont_arg_2][struc->buf.cont_files
				[struc->len.cont_arg_2]] = 1;
		}
	}
	free(chemin);
}

void		files_is_files(char *str, t_struc_ls *struc, STAT stat)
{
	if ((malloc_struc(struc)) == -1)
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
	verif_xattr(str, struc);
	struc->len.total = stat.st_blocks;
	struc->buf.cont_files[struc->len.cont_arg_2]++;
	struc->len.cont_arg_2++;
}
