/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permision_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:18:34 by gsotty            #+#    #+#             */
/*   Updated: 2017/04/02 16:45:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*permision_l_3(struct stat *buf, char *tmp, int xattr)
{
	if ((buf->st_mode & S_IROTH) == S_IROTH)
		tmp[7] = 'r';
	else
		tmp[7] = '-';
	if ((buf->st_mode & S_IWOTH) == S_IWOTH)
		tmp[8] = 'w';
	else
		tmp[8] = '-';
	if (((buf->st_mode & S_IXOTH) != S_IXOTH) &&
			((buf->st_mode & S_ISVTX) == S_ISVTX))
		tmp[9] = 'T';
	else if ((buf->st_mode & S_ISVTX) == S_ISVTX)
		tmp[9] = 't';
	else if ((buf->st_mode & S_IXOTH) == S_IXOTH)
		tmp[9] = 'x';
	else
		tmp[9] = '-';
	if (xattr == 1)
		tmp[10] = '@';
	else
		tmp[10] = ' ';
	tmp[11] = '\0';
	return (tmp);
}

static char	*permision_l_2(struct stat *buf, char *tmp, int xattr)
{
	if ((buf->st_mode & S_IRGRP) == S_IRGRP)
		tmp[4] = 'r';
	else
		tmp[4] = '-';
	if ((buf->st_mode & S_IWGRP) == S_IWGRP)
		tmp[5] = 'w';
	else
		tmp[5] = '-';
	if (((buf->st_mode & S_IXGRP) != S_IXGRP) &&
			((buf->st_mode & S_ISGID) == S_ISGID))
		tmp[6] = 'S';
	else if ((buf->st_mode & S_ISGID) == S_ISGID)
		tmp[6] = 's';
	else if ((buf->st_mode & S_IXGRP) == S_IXGRP)
		tmp[6] = 'x';
	else
		tmp[6] = '-';
	tmp = permision_l_3(buf, tmp, xattr);
	return (tmp);
}

static char	*permision_l_1(struct stat *buf, char *tmp, int xattr)
{
	if ((buf->st_mode & S_IRUSR) == S_IRUSR)
		tmp[1] = 'r';
	else
		tmp[1] = '-';
	if ((buf->st_mode & S_IWUSR) == S_IWUSR)
		tmp[2] = 'w';
	else
		tmp[2] = '-';
	if (((buf->st_mode & S_IXUSR) != S_IXUSR) &&
			((buf->st_mode & S_ISUID) == S_ISUID))
		tmp[3] = 'S';
	else if ((buf->st_mode & S_ISUID) == S_ISUID)
		tmp[3] = 's';
	else if ((buf->st_mode & S_IXUSR) == S_IXUSR)
		tmp[3] = 'x';
	else
		tmp[3] = '-';
	tmp = permision_l_2(buf, tmp, xattr);
	return (tmp);
}

char		*permision_l(struct stat *buf, int y, int x, t_struc_ls *struc)
{
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * 12);
	if (S_ISREG(buf->st_mode) == 1)
		tmp[0] = '-';
	else if (S_ISDIR(buf->st_mode) == 1)
		tmp[0] = 'd';
	else if (S_ISCHR(buf->st_mode) == 1)
		tmp[0] = 'c';
	else if (S_ISBLK(buf->st_mode) == 1)
		tmp[0] = 'b';
	else if (S_ISFIFO(buf->st_mode) == 1)
		tmp[0] = 'p';
	else if (S_ISLNK(buf->st_mode) == 1)
		tmp[0] = 'l';
	else if (S_ISSOCK(buf->st_mode) == 1)
		tmp[0] = 's';
	tmp = permision_l_1(buf, tmp, struc->buf.xattr[y][x]);
	return (tmp);
}
