/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_while_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:00:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/22 16:10:18 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_while_ls(char *str, int test, t_struc_ls *struc)
{
	struct stat	stat_dir;
	struct stat	stat_lnk;

	if (lstat(str, &stat_dir) == -1)
	{
		if (str[0] == '\0')
		{
			ft_printf("ls: ");
			perror("fts_open");
		}
		else
		{
			if (ft_strcmp(strerror(errno), "Not a directory") == 0)
				return ;
			ft_printf("ls: ");
			perror(str);
		}
		return ;
	}
	struc->len.argv = ft_strlen(str);
	if (S_ISLNK(stat_dir.st_mode) == 1)
	{
		if (struc->flag.l_min == 1)
		{
			if (lstat(str, &stat_lnk) == -1)
				ft_memset(&stat_lnk, 0, sizeof(struct stat));
		}
		else
		{
			if (stat(str, &stat_lnk) == -1)
				ft_memset(&stat_lnk, 0, sizeof(struct stat));
		}
		if (S_ISDIR(stat_lnk.st_mode) == 1)
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
		{
			files_is_files(str, struc, stat_dir);
		}
	}
	else
	{
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
		{
			files_is_files(str, struc, stat_dir);
		}
	}
}
