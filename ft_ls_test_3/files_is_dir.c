/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_is_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:52:05 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/17 16:08:42 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		ft_while_files_2(struct dirent *result, char *str,
		t_struc_ls *struc)
{
	if (result->d_name[0] != '.' && struc->flag.a_min == 0)
	{
		write_struc_ls(struc->buf.cont_files[struc->len.cont_arg_2], str,
				result->d_name, struc);
		struc->buf.cont_files[struc->len.cont_arg_2]++;
	}
	else if (result->d_name[0] == '.' && struc->flag.a_min == 1)
	{
		write_struc_ls(struc->buf.cont_files[struc->len.cont_arg_2], str,
				result->d_name, struc);
		struc->buf.cont_files[struc->len.cont_arg_2]++;
	}
	else if (struc->flag.a_min == 1)
	{
		write_struc_ls(struc->buf.cont_files[struc->len.cont_arg_2], str,
				result->d_name, struc);
		struc->buf.cont_files[struc->len.cont_arg_2]++;
	}
}

static void		ft_while_files(struct dirent *result, char *str,
		t_struc_ls *struc)
{
	int				ret;
	char			*chemin;
	size_t			taille;
	char			*tmp;
	struct stat		stat_files;

	taille = 32764;
	chemin = ft_memalloc(32764);
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
	struc->len.total += stat_files.st_blocks;
	if ((ret = listxattr(tmp, chemin, taille, XATTR_NOFOLLOW)) > 0 &&
			ft_strstr(str, "/usr") == NULL)
	{
		struc->buf.xattr[struc->len.cont_arg_2][struc->buf.cont_files
			[struc->len.cont_arg_2]] = 1;
	}
	struc->len.namlen = result->d_namlen;
	ft_while_files_2(result, str, struc);
	free(tmp);
	free(chemin);
}

void			files_is_dir(char *str, t_struc_ls *struc)
{
	DIR				*dir;
	struct dirent	*result;

	if (!(struc->buf.xattr[struc->len.cont_arg_2] =
				ft_memalloc(sizeof(size_t) * struc->len.dir + 1)))
		return ;
	struc->buf.save_name[struc->len.cont_arg_2] = ft_strdup(str);
	if ((dir = opendir(str)) == NULL)
	{
		ft_printf("opendir de files_is_dir\n");
		perror(str);
		return ;
	}
	while ((result = readdir(dir)) != NULL)
		ft_while_files(result, str, struc);
	closedir(dir);
	struc->len.cont_arg_2++;
}
