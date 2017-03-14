/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_while_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:00:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/14 13:05:12 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_while_else(char *str, t_struc_ls *struc)
{
	struc->len.dir = ft_strlen(str);
	if (!(struc->buf.buf[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char *) * struc->len.dir + 1)))
		return ;
	if (!(struc->buf.save_name[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(char) * struc->len.dir + 1)))
		return ;
	if (!(struc->buf.stat[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(STAT) * struc->len.dir)))
		return ;
	ft_memcpy(struc->buf.save_name[struc->len.cont_arg_2], str,
			struc->len.argv);
	struc->buf.save_name[struc->len.cont_arg_2][struc->len.argv] = '\0';
	ft_memcpy(struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
			[struc->len.cont_arg_2]], str, struc->len.namlen);
	struc->buf.buf[struc->len.cont_arg_2][struc->buf.cont_files
		[struc->len.cont_arg_2]][struc->len.namlen] = '\0';
	struc->buf.cont_files[struc->len.cont_arg_2]++;
	struc->len.cont_arg_2++;
}

void	ft_while_ls(char *str, int test, t_struc_ls *struc)
{
	struct stat	stat_dir;

	if (lstat(str, &stat_dir) == -1)
	{
		ft_printf("lstat de ft_while_ls\n");
		perror(str);
		return ;
	}
	if (S_ISDIR(stat_dir.st_mode) == 1)
	{
		if ((struc->len.dir = ft_len_dir(str, struc)) == (size_t)-1)
			return ;
		struc->len.argv = ft_strlen(str);
		if (!(struc->buf.buf[struc->len.cont_arg_2] =
					ft_memalloc(sizeof(char *) * struc->len.dir)))
			return ;
		if (!(struc->buf.stat[struc->len.cont_arg_2] =
					ft_memalloc(sizeof(STAT) * struc->len.dir)))
			return ;
		struc->buf.save_name[struc->len.cont_arg_2] = ft_strdup(str);
		files_is_dir(str, struc);
		struc->len.cont_arg_2++;
	}
	else if (test == 1)
		ft_while_else(str, struc);
}
