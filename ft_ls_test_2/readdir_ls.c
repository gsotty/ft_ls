/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 10:51:31 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/08 15:33:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

DIR				*opendir_ls(char *str)
{
	int		err;
	DIR		*dir;

	if ((dir = opendir(str)) == NULL)
		return (NULL);
	return (dir);
}

size_t			len_dir_ls(char *str, t_struc_ls *struc)
{
	DIR				*dir;
	size_t			x;
	DIRENT			*result;

	x = 0;
	dir = opendir_ls(str);
	while ((result = readdir(dir)) != NULL)
	{
		if (result->d_name[0] != '.' && struc->a_min == 0)
			x++;
		if (result->d_name[0] == '.' && struc->a_min == 1)
			x++;
		else if (struc->a_min == 1)
			x++;
	}
	closedir(dir);
	return (x);
}
STAT			stat_ls(char *str, STAT stat)
{
	char	*str_errno;

	if (lstat(str, &stat) == -1)
	{
		str_errno = strerror(errno);
		ft_printf("%s\n", str_errno);
		exit(0);
	}
	return (stat);
}

STAT			*creat_stat(char *str, t_struc_ls *struc, size_t len_dir, int x)
{
	size_t			y;
	size_t			len_str;
	DIR				*dir;
	DIRENT			*result;
	STAT			*stat;
	char			*tmp;
	size_t			cont_total;

	y = 0;
	cont_total = 0;
	len_str = ft_strlen(str);
	dir = opendir_ls(str);
	stat = ft_memalloc(sizeof(STAT) * len_dir + 1);
	ft_memset(stat, 0, sizeof(STAT) * len_dir + 1);
	struc->name[x] = ft_memalloc(sizeof(char *) * len_dir + 1);
	ft_memset(struc->name[x], 0, sizeof(char *) * len_dir + 1);
	struc->len.namlen = ft_memalloc(sizeof(size_t) * len_dir + 1);
	ft_memset(struc->name[x], 0, sizeof(size_t) * len_dir + 1);
	while ((result = readdir(dir)) != NULL)
	{
		if (result->d_name[0] != '.' && struc->a_min == 0)
		{
			tmp = ft_memalloc(sizeof(char) * (len_str + result->d_namlen + 2));
			ft_memset(tmp, 0, sizeof(char) * (len_str + result->d_namlen + 2));
			ft_memcpy(tmp, str, len_str);
			ft_memcpy(tmp + len_str, "/", 1);
			ft_memcpy(tmp + len_str + 1, result->d_name, result->d_namlen);
			stat[y] = stat_ls(tmp, stat[y]);
			struc->name[x][y] = ft_memalloc(result->d_namlen * sizeof(char));
			ft_memcpy(struc->name[x][y], result->d_name, result->d_namlen);
			struc->name[x][y][result->d_namlen] = '\0';
			struc->len.namlen[y] = result->d_namlen;
			y++;
		}
		else if (result->d_name[0] == '.' && struc->a_min == 1)
		{
			tmp = ft_memalloc(sizeof(char) * (len_str + result->d_namlen + 2));
			ft_memset(tmp, 0, sizeof(char) * (len_str + result->d_namlen + 2));
			ft_memcpy(tmp, str, len_str);
			ft_memcpy(tmp + len_str, "/", 1);
			ft_memcpy(tmp + len_str + 1, result->d_name, result->d_namlen);
			stat[y] = stat_ls(tmp, stat[y]);
			struc->name[x][y] = ft_memalloc(result->d_namlen * sizeof(char));
			ft_memcpy(struc->name[x][y], result->d_name, result->d_namlen);
			struc->name[x][y][result->d_namlen] = '\0';
			struc->len.namlen[y] = result->d_namlen;
			y++;
		}
		else if (struc->a_min == 1)
		{
			tmp = ft_memalloc(sizeof(char) * (len_str + result->d_namlen + 2));
			ft_memset(tmp, 0, sizeof(char) * (len_str + result->d_namlen + 2));
			ft_memcpy(tmp, str, len_str);
			ft_memcpy(tmp + len_str, "/", 1);
			ft_memcpy(tmp + len_str + 1, result->d_name, result->d_namlen);
			stat[y] = stat_ls(tmp, stat[y]);
			struc->name[x][y] = ft_memalloc(result->d_namlen * sizeof(char));
			ft_memcpy(struc->name[x][y], result->d_name, result->d_namlen);
			struc->name[x][y][result->d_namlen] = '\0';
			struc->len.namlen[y] = result->d_namlen;
			y++;
		}
	}
	struc->nbr_files = y;
	closedir(dir);
	return (stat);
}

char			**stat_ls_dir(char *str, t_struc_ls *struc, size_t x)
{
	size_t			len_dir;
	DIR				*dir;
	STAT			stat;
	STAT			*buf;
	char			*str_errno;
	char			**name;
	int				y;

	y = 0;
	len_dir = 0;
	name = NULL;
	ft_memset(&struc->len, 0, sizeof(t_len_ls));
	//ft_printf("%s\n", str);
	if (lstat(str, &stat) == -1)
	{
		str_errno = strerror(errno);
		ft_printf("%s\n", str_errno);
		exit(0);
	}
	if (S_ISDIR(stat.st_mode) == 1)
	{
	//	ft_printf("is a directory:\n");
		struc->len_dir[x] = len_dir_ls(str, struc);
		len_dir = struc->len_dir[x];
		name = ft_memalloc(sizeof(char *) * len_dir + 1);
		ft_memset(name, 0, sizeof(char *) * len_dir + 1);
		buf = creat_stat(str, struc, len_dir, x);
		if (struc->l_min == 1)
		{
			verif_len(buf, struc);
			while ((y < struc->nbr_files) && (struc->l_min == 1))
			{
				name[y] = creat_l_min(buf[y], struc, struc->name[x][y],
						struc->len.namlen[y]);
				y++;
			}
		}
		else
		{
			while ((y < struc->nbr_files))
			{
				name[y] = ft_strdup(struc->name[x][y]);
				name[y][struc->len.namlen[y]] = '\0';
				y++;
			}
		}
	}
	else if (struc->not_r == 0)
	{
		ft_printf("is not a directory:\n");
		struc->len_dir[x] = 1;
		name = ft_memalloc(sizeof(char *) * 1);
		ft_memset(name, 0, sizeof(char *) * 1);
		name[0] = ft_strdup(str);
		verif_len(&stat, struc);
		if (struc->l_min == 1)
			name[0] = creat_l_min(stat, struc, name[0], ft_strlen(str));
	}
	return (name);
}

char			***readdir_ls(t_struc_ls *struc, char **argv, size_t cont_argc)
{
	size_t	x;
	char	***data;

	x = 0;
	struc->name = ft_memalloc(sizeof(char **) * struc->argc - cont_argc);
	ft_memset(struc->name, 0, sizeof(char **) * struc->argc - cont_argc);
	struc->len_dir = ft_memalloc(sizeof(unsigned int) *
			struc->argc - cont_argc);
	ft_memset(struc->len_dir, 0, sizeof(unsigned int) *
			struc->argc - cont_argc);
	data = ft_memalloc(sizeof(char **) * struc->argc);
	ft_memset(data, 0, sizeof(char **) * struc->argc);
/*	while (cont_argc < struc->argc)
	{
		data[x] = stat_ls_dir(argv[cont_argc], struc, x);
		cont_argc++;
		x++;
	}
	*/
	int	y=0;
	int	j=0;
	while (y < 1)
	{
		j = 0;
		while (j < struc->len_dir[y])
		{
			ft_printf("%-20s", data[y][j]);
			ft_printf("%s\n", struc->name[y][j]);
			j++;
		}
		y++;
	}
	return (data);
}
