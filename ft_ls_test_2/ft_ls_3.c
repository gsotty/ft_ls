/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 13:07:39 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/11 16:34:37 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls_2.h"

size_t	ft_len_dir(char *str, t_struc_ls *struc)
{
	DIR				*dir;
	size_t			x;
	struct dirent	*result;

	x = 0;
	if ((dir = opendir(str)) == NULL)
		perror("tmp");
	while ((result = readdir(dir)) != NULL)
	{
		if (result->d_name[0] != '.' && struc->flag.a_min == 0)
			x++;
		else if (result->d_name[0] == '.' && struc->flag.a_min == 1)
			x++;
		else if (struc->flag.a_min == 1)
			x++;
	}
	closedir(dir);
	return (x);
}

void	write_buf_ls(char **save_name, int test, t_struc_ls *struc,
		long long total)
{
	int				z;
	int				x;
	int				y;
	struct group	*g;
	struct passwd	*p;

	y = 0;
	while (y < struc->len.cont_arg_2)
	{
		x = 0;
		if (test == 0 || struc->flag.multi == 1)
			ft_printf("%s:\n", save_name[y]);
		if (struc->flag.l_min == 1)
			ft_printf("total %lld\n", total / 512);
		if (struc->flag.l_min == 1)
			verif_len_2(struc->buf.stat[y], struc, struc->buf.cont_files[y]);
		while (x < struc->buf.cont_files[y])
		{
			if (struc->flag.l_min == 1)
			{
				p = getpwuid(struc->buf.stat[y][x].st_uid);
				g = getgrgid(struc->buf.stat[y][x].st_gid);
				ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %.*s\n",
						permision_l(&struc->buf.stat[y][x]), struc->len.nlink,
						struc->buf.stat[y][x].st_nlink, struc->len.pwname,
						p->pw_name, struc->len.grname, g->gr_name,
						struc->len.size, struc->buf.stat[y][x].st_size,
						ctime(&struc->buf.stat[y][x].st_mtime) + 4,
						ft_strlen(struc->buf.buf[y][x]), struc->buf.buf[y][x]);
			}
			else
			{
				ft_printf("%s\n", struc->buf.buf[y][x]);
			}
			x++;
		}
		write(1, "\n", 1);
		z = 0;
		while (z < struc->buf.cont_files[y] && struc->flag.r_maj == 1)
		{
			if (z >= 2 && struc->flag.a_min == 1)
				recursive_r_maj_files_ls(save_name[y], struc->buf.buf[y][z],
						struc);
			else if (struc->flag.a_min == 0)
				recursive_r_maj_files_ls(save_name[y], struc->buf.buf[y][z],
						struc);
			z++;
		}
		y++;
	}
}

void	write_struc_ls(size_t cont_files, char *str, char *name,
		t_struc_ls *struc)
{
	char	*tmp;

	if (!(struc->buf.buf[struc->len.cont_arg_2][cont_files] =
				ft_memalloc(sizeof(char) * struc->len.namlen + 1)))
		return ;
	ft_memcpy(struc->buf.buf[struc->len.cont_arg_2][cont_files], name,
			struc->len.namlen);
	struc->buf.buf[struc->len.cont_arg_2][cont_files]
		[struc->len.namlen] = '\0';
	if (!(tmp = ft_memalloc(sizeof(char) * struc->len.namlen +
					struc->len.argv + 2)))
		return ;
	sprintf(tmp, "%s/%s", str, name);
	if ((lstat(tmp, &struc->buf.stat[struc->len.cont_arg_2][cont_files]))
			== -1)
		perror("tmp");
}

void	files_is_dir(char *str, t_struc_ls *struc)
{
	DIR				*dir;
	size_t			x;
	struct dirent	*result;
	struct stat		stat_files;
	char			*tmp;

	if ((dir = opendir(str)) == NULL)
		perror("dir");
	while ((result = readdir(dir)) != NULL)
	{
		if (!(tmp = ft_memalloc(sizeof(char) * result->d_namlen +
						struc->len.argv + 2)))
			return ;
		sprintf(tmp, "%s/%s", str, result->d_name);
		if (lstat(tmp, &stat_files) == -1)
			perror("tmp");
		struc->len.namlen = result->d_namlen;
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
		struc->len.total += stat_files.st_size;
	}
	closedir(dir);
}

void	ft_while_ls(char *str, int cont_arg_1, int test, t_struc_ls *struc)
{
	struct stat	stat_dir;

	if (lstat(str, &stat_dir) == -1)
		perror("tmp");
	if (S_ISDIR(stat_dir.st_mode) == 1)
	{
		struc->len.dir = ft_len_dir(str, struc);
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
	{
		struc->len.argv = ft_strlen(str);
		struc->len.dir = ft_len_dir(str, struc);
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
}

void	ft_ls(int argc, char **argv, int test, t_struc_ls *struc)
{
	int		cont_arg_1;

	cont_arg_1 = 0;
	if ((struc->buf.buf = ft_memalloc(sizeof(char **) * argc)) == NULL)
		return ;
	if ((struc->buf.save_name = ft_memalloc(sizeof(char *) * argc)) == NULL)
		return ;
	if ((struc->buf.cont_files = ft_memalloc(sizeof(int) * argc)) == NULL)
		return ;
	if ((struc->buf.stat = ft_memalloc(sizeof(STAT *) * argc)) == NULL)
		return ;
	while (cont_arg_1 < argc)
	{
		ft_while_ls(argv[struc->len.cont_arg_2], cont_arg_1, test, struc);
		cont_arg_1++;
	}
	write_buf_ls(struc->buf.save_name, test, struc, struc->len.total);
}

void	recursive_r_maj_files_ls(char *save_name, char *buf, t_struc_ls *struc)
{
	int			ret;
	int			len_buf;
	char		**tmp;
	t_struc_ls	new_struc;

	if ((tmp = ft_memalloc(sizeof(char *))) == NULL)
		return ;
	len_buf = ft_strlen(save_name) + ft_strlen(buf) + 2;
	if ((tmp[0] = ft_memalloc(sizeof(char) * len_buf + 1)) == NULL)
		return ;
	ret = ft_sprintf(tmp[0], "%s/%s", save_name, buf);
	tmp[0][ret] = '\0';
	ft_memset(&new_struc, 0, sizeof(t_struc_ls));
	new_struc.flag.r_maj = struc->flag.r_maj;
	new_struc.flag.a_min = struc->flag.a_min;
	new_struc.flag.l_min = struc->flag.l_min;
	new_struc.flag.r_min = struc->flag.r_min;
	new_struc.flag.t_min = struc->flag.t_min;
	new_struc.flag.multi = struc->flag.multi;
	ft_ls(1, tmp, 0, &new_struc);
}

int		main(int argc, char **argv)
{
	int			cont_arg;
	t_struc_ls	struc;

	ft_memset(&struc, 0, sizeof(t_struc_ls));
	cont_arg = check_flag_ls(argc, argv, &struc);
	ft_ls(struc.buf.argc - cont_arg, argv + cont_arg, 1, &struc);
	return (0);
}
