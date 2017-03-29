/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_while_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:00:18 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 10:00:09 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		files_is_lnk(char *str, int test, STAT stat_dir,
		t_struc_ls *struc)
{
	struct stat	stat_lnk;

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
		files_is_dir(str, struc, test);
	else if (test == 1)
		files_is_files(str, struc, stat_dir);
}

static void		ft_while_2_ls(char *str, t_struc_ls *struc, int test,
		STAT stat_dir)
{
	if (S_ISLNK(stat_dir.st_mode) == 1)
		files_is_lnk(str, test, stat_dir, struc);
	else
	{
		if (S_ISDIR(stat_dir.st_mode) == 1)
			files_is_dir(str, struc, test);
		else if (test == 1)
			files_is_files(str, struc, stat_dir);
	}
}

void			ft_while_ls(char *str, int test, t_struc_ls *struc)
{
	struct stat	stat_dir;

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
	ft_while_2_ls(str, struc, test, stat_dir);
}
