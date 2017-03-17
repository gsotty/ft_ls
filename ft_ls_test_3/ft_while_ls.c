/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_while_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:00:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/17 16:08:27 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_while_else(char *str, t_struc_ls *struc, STAT stat)
{
	int		ret;
	char	*chemin;
	size_t	taille;

	taille = 32764;
	chemin = ft_memalloc(32764);
	struc->buf.files_or_dir[struc->len.cont_arg_2] = 1;
	if (!(struc->buf.xattr[struc->len.cont_arg_2] = ft_memalloc(
					sizeof(size_t) * 1)))
		return ;
	if (!(struc->buf.buf[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char *) * struc->len.argv + 1)))
		return ;
	if (!(struc->buf.save_name[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char) * struc->len.argv + 1)))
		return ;
	if (!(struc->buf.stat[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(STAT) * struc->len.argv)))
		return ;
	if (!(struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
				[struc->len.cont_arg_2]] = ft_memalloc(sizeof(char *))))
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
	struc->len.total = stat.st_size;
	struc->buf.cont_files[struc->len.cont_arg_2]++;
	struc->len.cont_arg_2++;
	free(chemin);
}

void	ft_while_ls(char *str, int test, t_struc_ls *struc)
{
	struct stat	stat_dir;

	if (lstat(str, &stat_dir) == -1)
	{
		if (ft_strcmp(strerror(errno), "Not a directory") == 0)
			return ;
		ft_printf("ls: ");
		perror(str);
		return ;
	}
	struc->len.argv = ft_strlen(str);
	if (S_ISDIR(stat_dir.st_mode) == 1)
	{
		if (test == 0)
			write(1, "\n", 1);
		if ((struc->len.dir = ft_len_dir(str, test, struc)) == (size_t)-1)
			return ;
		if (!(struc->buf.buf[struc->len.cont_arg_2] =
					ft_memalloc(sizeof(char *) * struc->len.dir)))
			return ;
		if (!(struc->buf.stat[struc->len.cont_arg_2] =
					ft_memalloc(sizeof(STAT) * struc->len.dir)))
			return ;
		files_is_dir(str, struc);
	}
	else if (test == 1)
		ft_while_else(str, struc, stat_dir);
}
