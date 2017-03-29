/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_is_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:52:05 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 09:56:38 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		filling_struc_dir(char *str, STAT stat_files,
		struct dirent *result, t_struc_ls *struc)
{
	int				ret;
	char			*tmp;
	char			*chemin;
	size_t			taille;

	taille = 32764;
	chemin = ft_memalloc(32764);
	if (!(tmp = ft_memalloc(sizeof(char) * result->d_namlen +
					struc->len.argv + 2)))
		return ;
	if (ft_memcmp(str, "/", ft_strlen(str)) == 0)
		ft_sprintf(tmp, "%s/%s", str, result->d_name);
	else
		ft_sprintf(tmp, "%s/%s", str, result->d_name);
	if ((ret = listxattr(tmp, chemin, taille, XATTR_NOFOLLOW)) > 0)
	{
		struc->buf.xattr[struc->len.cont_arg_2][struc->buf.cont_files
			[struc->len.cont_arg_2]] = 1;
	}
	write_struc_ls(struc->buf.cont_files[struc->len.cont_arg_2], str,
			result->d_name, struc);
	struc->buf.cont_files[struc->len.cont_arg_2]++;
	struc->len.total += stat_files.st_blocks;
	free(chemin);
	free(tmp);
}

static void		ft_while_files_2(struct dirent *result, char *str,
		t_struc_ls *struc, STAT stat_files)
{
	if (result->d_name[0] != '.' && struc->flag.a_min == 0)
		filling_struc_dir(str, stat_files, result, struc);
	else if (result->d_name[0] == '.' && struc->flag.a_min == 1)
		filling_struc_dir(str, stat_files, result, struc);
	else if (struc->flag.a_min == 1)
		filling_struc_dir(str, stat_files, result, struc);
}

static void		ft_while_files(struct dirent *result, char *str,
		t_struc_ls *struc)
{
	char			*tmp;
	struct stat		stat_files;

	if (!(tmp = ft_memalloc(sizeof(char) * result->d_namlen +
					struc->len.argv + 2)))
		return ;
	if (ft_memcmp(str, "/", ft_strlen(str)) == 0)
		ft_sprintf(tmp, "%s/%s", str, result->d_name);
	else
		ft_sprintf(tmp, "%s/%s", str, result->d_name);
	if (lstat(tmp, &stat_files) == -1)
	{
		ft_printf("lstat de files_is_dir\n");
		perror(tmp);
		return ;
	}
	struc->len.namlen = result->d_namlen;
	ft_while_files_2(result, str, struc, stat_files);
	free(tmp);
}

static void		open_dir(char *str, t_struc_ls *struc)
{
	DIR				*dir;
	struct dirent	*result;

	if ((dir = opendir(str)) == NULL)
	{
		ft_printf("opendir de files_is_dir\n");
		perror(str);
		return ;
	}
	while ((result = readdir(dir)) != NULL)
		ft_while_files(result, str, struc);
	closedir(dir);
}

void			files_is_dir(char *str, t_struc_ls *struc, int test)
{
	if (test == 0)
		write(1, "\n", 1);
	if ((struc->len.dir = ft_len_dir(str, test, struc)) == (size_t)-1)
		return ;
	if (!(struc->buf.xattr[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(size_t) * struc->len.dir + 1)))
		return ;
	if (!(struc->buf.stat[struc->len.cont_arg_2] = ft_memalloc(sizeof(STAT) *
					struc->len.dir)))
		return ;
	if (!(struc->buf.buf[struc->len.cont_arg_2] = ft_memalloc(sizeof(char *) *
					struc->len.dir)))
		return ;
	struc->buf.save_name[struc->len.cont_arg_2] = ft_strdup(str);
	open_dir(str, struc);
	struc->len.cont_arg_2++;
}
