/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_r_maj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 10:59:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/11 15:49:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	ft_len_dir(char *str, t_struc_ls *struc)
{
	DIR		*dir;
	size_t	x;
	DIRENT	*result;

	x = 0;
	dir = opendir(str);
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

void	write_buf_ls(int cont_arg, int *cont_files, char **save_name,
		char ***buf, int test, t_struc_ls *struc, long long total)
{
	int				z;
	int				x;
	int				y;
	struct group	*g;
	struct passwd	*p;

	y = 0;
	while (y < cont_arg)
	{
		x = 0;
		z = 0;
		if (test == 0 || struc->flag.multi == 1)
			ft_printf("%s:\n", save_name[y]);
		if (struc->flag.l_min == 1)
			ft_printf("total %lld\n", total);
		while (x < cont_files[y])
		{
			if (struc->flag.l_min == 1)
			{
				verif_len(struc->buf.stat[y], struc, cont_files[y]);
				p = getpwuid(struc->buf.stat[y][x].st_uid);
				g = getgrgid(struc->buf.stat[y][x].st_gid);
				ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %.*s\n",
						permision_l(&struc->buf.stat[y][x]) , struc->len.nlink,
						struc->buf.stat[y][x].st_nlink, struc->len.pwname,
						p->pw_name, struc->len.grname, g->gr_name,
						struc->len.size, struc->buf.stat[y][x].st_size,
						ctime(&struc->buf.stat[y][x].st_mtime) + 4,
						ft_strlen(buf[y][x]), buf[y][x]);
			}
			else
			{
				ft_printf("%s\n", buf[y][x]);
			}
			x++;
		}
		write(1, "\n", 1);
		while (z < cont_files[y] && struc->flag.r_maj == 1)
		{
			if (z >= 2 && struc->flag.a_min == 1)
				recursive_r_maj_files_ls(1, save_name[y], buf[y][z], 0, struc);
			else if (struc->flag.a_min == 0)
				recursive_r_maj_files_ls(1, save_name[y], buf[y][z], 0, struc);
			z++;
		}
		y++;
	}
}

void	test_r_maj(int nbr_arg, char **argv, int test, t_struc_ls *struc)
{
	int				cont_arg;
	int				cont_arg_1;

	struct stat		stat_2;
	struct stat		stat;
	struct dirent	*result;
	int				len_argv;
	char			*str_error;
	DIR				*dir;
	int				len_dir;
	char			*tmp;
	long long		total;

	int				*cont_files;
	char			**save_name;
	char			***buf;


	cont_arg = 0;
	cont_arg_1 = 0;
	total = 0;
	ft_memset(&struc->len, 0, sizeof(t_len_ls));
	ft_memset(&struc->buf, 0, sizeof(t_buf_ls));
	if ((buf = ft_memalloc(sizeof(char **) * nbr_arg)) == NULL)
		return ;
	if ((save_name = ft_memalloc(sizeof(char *) * nbr_arg)) == NULL)
		return ;
	if ((cont_files = ft_memalloc(sizeof(int) * nbr_arg)) == NULL)
		return ;
	if (!(struc->buf.stat = ft_memalloc(sizeof(STAT *) * nbr_arg)))
		return ;
	while (cont_arg_1 < nbr_arg)
	{
		if (lstat(argv[cont_arg_1], &stat) == -1)
		{
			str_error = strerror(errno);
			ft_printf("argv = %s\n", argv[cont_arg_1]);
			ft_printf("%s, %s\n", argv[cont_arg_1] + 1, str_error);
		}
		if (S_ISDIR(stat.st_mode) == 1)
		{
			len_dir = ((int)ft_len_dir(argv[cont_arg_1], struc));
			len_argv = ft_strlen(argv[cont_arg_1]);
			if (!(struc->buf.stat[cont_arg] = ft_memalloc(sizeof(STAT) *
							len_dir)))
				return ;
			if ((save_name[cont_arg] = ft_memalloc(sizeof(char) *
							(len_argv + 1))) == NULL)
				return ;
			ft_memcpy(save_name[cont_arg], argv[cont_arg_1], len_argv);
			save_name[cont_arg][len_argv] = '\0';
			if (!(buf[cont_arg] = ft_memalloc(sizeof(char *) * len_dir)))
				return ;
			if ((dir = opendir(argv[cont_arg_1])) == NULL)
				return ;
			while ((result = readdir(dir)) != NULL)
			{
				tmp = ft_memalloc(sizeof(char) * result->d_namlen +
						ft_strlen(argv[cont_arg_1]) + 2);
				sprintf(tmp, "%s/%s", argv[cont_arg_1], result->d_name);
				if (lstat(tmp, &stat_2) == -1)
				{
					str_error = strerror(errno);
					ft_printf("argv = %s\n", tmp);
					ft_printf("%s, %s\n", tmp, str_error);
				}
				total += stat_2.st_size / 512;
				if (result->d_name[0] != '.' && struc->flag.a_min == 0)
				{
					if ((buf[cont_arg][cont_files[cont_arg]] =
								ft_memalloc(sizeof(char) *
									(result->d_namlen + 1))) == NULL)
						return ;
					ft_memcpy(buf[cont_arg][cont_files[cont_arg]],
							result->d_name, result->d_namlen);
					buf[cont_arg][cont_files[cont_arg]][result->d_namlen]
						= '\0';
					tmp = ft_memalloc(sizeof(char) * result->d_namlen +
							ft_strlen(argv[cont_arg_1]) + 2);
					sprintf(tmp, "%s/%s", argv[cont_arg_1], result->d_name);
					if ((lstat(tmp, &struc->buf.stat[cont_arg][cont_files
									[cont_arg]])) == -1)
					{
						str_error = strerror(errno);
						ft_printf("argv = %s\n", result->d_name);
						ft_printf("%s, %s\n", result->d_name, str_error);
					}
					cont_files[cont_arg]++;
				}
				else if (result->d_name[0] == '.' && struc->flag.a_min == 1)
				{
					if ((buf[cont_arg][cont_files[cont_arg]] =
								ft_memalloc(sizeof(char) *
									(result->d_namlen + 1))) == NULL)
						return ;
					ft_memcpy(buf[cont_arg][cont_files[cont_arg]],
							result->d_name, result->d_namlen);
					buf[cont_arg][cont_files[cont_arg]][result->d_namlen]
						= '\0';
					tmp = ft_memalloc(sizeof(char) * result->d_namlen +
							ft_strlen(argv[cont_arg_1]) + 2);
					sprintf(tmp, "%s/%s", argv[cont_arg_1], result->d_name);
					if ((lstat(tmp, &struc->buf.stat[cont_arg][cont_files
									[cont_arg]])) == -1)
					{
						str_error = strerror(errno);
						ft_printf("argv = %s\n", result->d_name);
						ft_printf("%s, %s\n", result->d_name, str_error);
					}
					cont_files[cont_arg]++;
				}
				else if (struc->flag.a_min == 1)
				{
					if ((buf[cont_arg][cont_files[cont_arg]] =
								ft_memalloc(sizeof(char) *
									(result->d_namlen + 1))) == NULL)
						return ;
					ft_memcpy(buf[cont_arg][cont_files[cont_arg]],
							result->d_name, result->d_namlen);
					buf[cont_arg][cont_files[cont_arg]][result->d_namlen]
						= '\0';
					tmp = ft_memalloc(sizeof(char) * result->d_namlen +
							ft_strlen(argv[cont_arg_1]) + 2);
					sprintf(tmp, "%s/%s", argv[cont_arg_1], result->d_name);
					if ((lstat(tmp, &struc->buf.stat[cont_arg][cont_files
									[cont_arg]])) == -1)
					{
						str_error = strerror(errno);
						ft_printf("argv = %s\n", result->d_name);
						ft_printf("%s, %s\n", result->d_name, str_error);
					}
					cont_files[cont_arg]++;
				}
			}
			struc->buf.nbr_files = cont_arg;
			closedir(dir);
			cont_arg++;
		}
		else if (test == 1)
		{
			len_argv = ft_strlen(argv[cont_arg_1]);
			argv[cont_arg_1][len_argv] = '\0';
			if ((save_name[cont_arg] = ft_memalloc(sizeof(char) *
							(len_argv + 1))) == NULL)
				return ;
			ft_memcpy(save_name[cont_arg], argv[cont_arg_1], len_argv);
			save_name[cont_arg][len_argv] = '\0';
			if ((buf[cont_arg] = ft_memalloc(sizeof(char *) + 1)) == NULL)
				return ;
			if ((buf[cont_arg][cont_files[cont_arg]] =
						ft_memalloc(sizeof(char) * (len_argv + 1))) == NULL)
				return ;
			ft_memcpy(buf[cont_arg][cont_files[cont_arg]], argv[cont_arg_1],
					len_argv);
			buf[cont_arg][cont_files[cont_arg]][len_argv] = '\0';
			cont_files[cont_arg]++;
			cont_arg++;
		}
		cont_arg_1++;
	}
	write_buf_ls(cont_arg, cont_files, save_name, buf, test, struc, total);
}

void	recursive_r_maj_files_ls(int cont_arg, char *save_name, char *buf,
		int test, t_struc_ls *struc)
{
	int		ret;
	int		len_buf;
	char	**tmp;

	if ((tmp = ft_memalloc(sizeof(char *))) == NULL)
		return ;
	len_buf = ft_strlen(save_name) + ft_strlen(buf) + 2;
	if ((tmp[0] = ft_memalloc(sizeof(char) * len_buf)) == NULL)
		return ;
	ret = ft_sprintf(tmp[0], "%s/%s", save_name, buf);
	tmp[0][ret] = '\0';
	test_r_maj(cont_arg, tmp, test, struc);
}

int		main(int argc, char **argv)
{
	int			cont_arg;
	t_struc_ls	struc;

	ft_memset(&struc, 0, sizeof(t_struc_ls));
	cont_arg = check_flag_ls(argc, argv, &struc);
	test_r_maj(struc.buf.argc - cont_arg, argv + cont_arg, 1, &struc);
	return (0);
}
