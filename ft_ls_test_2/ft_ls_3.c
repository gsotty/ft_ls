/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 11:42:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/13 17:25:47 by gsotty           ###   ########.fr       */
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
	{
		ft_printf("%s:\nls: ", str);
		perror(ft_strrchr(str, '/') + 1);
		write(1, "\n", 1);
		return (-1);
	}
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

void	order(char **save_name, t_struc_ls *struc)
{
	int			x;
	int			y;
	int			verif;
	int			verif_2;
	int			tmp_cont;
	char		*tmp_buf;
	char		**tmp_buf_x;
	char		*tmp_name;
	struct stat	*tmp_stat_x;
	struct stat	tmp_stat;

	verif = 1;
	while (verif == 1)
	{
		x = 0;
		verif = 0;
		verif_2 = 1;
		while (verif_2 == 1)
		{
			y = 0;
			verif_2 = 0;
			while (y < struc->buf.cont_files[x] - 1)
			{
				if ((ft_strcmp(struc->buf.buf[x][y],
								struc->buf.buf[x][y + 1])) > 0)
				{
					tmp_buf = ft_strdup(struc->buf.buf[x][y]);
					struc->buf.buf[x][y] =
						ft_strdup(struc->buf.buf[x][y + 1]);
					struc->buf.buf[x][y + 1] = ft_strdup(tmp_buf);
					tmp_stat = struc->buf.stat[x][y];
					struc->buf.stat[x][y] = struc->buf.stat[x][y + 1];
					struc->buf.stat[x][y + 1] = tmp_stat;
					verif_2 = 1;
				}
				y++;
			}
		}
		while (x < struc->len.cont_arg_2 - 1)
		{
			if ((ft_strcmp(save_name[x], save_name[x + 1])) > 0)
			{
				tmp_cont = struc->buf.cont_files[x];
				struc->buf.cont_files[x] = struc->buf.cont_files[x + 1];
				struc->buf.cont_files[x + 1] = tmp_cont;
				tmp_buf_x = struc->buf.buf[x];
				struc->buf.buf[x] = struc->buf.buf[x + 1];
				struc->buf.buf[x + 1] = tmp_buf_x;
				tmp_stat_x = struc->buf.stat[x];
				struc->buf.stat[x] = struc->buf.stat[x + 1];
				struc->buf.stat[x + 1] = tmp_stat_x;
				tmp_name = ft_strdup(save_name[x]);
				free(save_name[x]);
				save_name[x] = ft_strdup(save_name[x + 1]);
				free(save_name[x + 1]);
				save_name[x + 1] = ft_strdup(tmp_name);
				free(tmp_name);
				verif = 1;
			}
			x++;
		}
	}
}

void	write_buf_ls(char **save_name, int test, t_struc_ls *struc,
		long long total)
{
	int				z;
	int				x;
	int				y;
	long			time_day;
	long			time_files;
	char			*time_f;
	char			*tmp;
	char			*tmp_perm;
	char			*tmp_join;
	char			*test_1;
	struct stat		stat_nlink;
	struct group	*g;
	struct passwd	*p;

	y = 0;
	order(save_name, struc);
	while (y < struc->len.cont_arg_2)
	{
		x = 0;
		if (test == 0 || struc->flag.multi == 1)
			ft_printf("%s:\n", save_name[y]);
		if (struc->flag.l_min == 1 && test == 0)
			ft_printf("total %lld\n", total / 512);
		if (struc->flag.l_min == 1)
			verif_len_2(struc->buf.stat[y], struc, struc->buf.cont_files[y]);
		while (x < struc->buf.cont_files[y])
		{
			if (struc->flag.l_min == 1)
			{
				time_day = time(&time_day);
				time_files = struc->buf.stat[y][x].st_mtime;
				p = getpwuid(struc->buf.stat[y][x].st_uid);
				g = getgrgid(struc->buf.stat[y][x].st_gid);
				if (!(time_files > time_day - 15778800 &&
							time_files < time_day + 60))
				{
					time_f = ctime(&time_files);
					if (S_ISLNK(struc->buf.stat[y][x].st_mode) == 1)
					{
						tmp = ft_memalloc(32767);
						sprintf(tmp, "%s/%s", save_name[y],
								struc->buf.buf[y][x]);
						if (stat(tmp, &stat_nlink))
						{
							ft_printf("ls :");
							perror(tmp);
						}
						else
						{
							test_1 = ft_memalloc(256);
							if ((readlink(tmp, test_1, 256)) == -1)
							{
								ft_printf("ls: ");
								perror(tmp);
							}
							else
							{
								ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s -> %s\n"
										, tmp_perm =
										permision_l(&struc->buf.stat[y][x]),
										struc->len.nlink,
										struc->buf.stat[y][x].st_nlink,
										struc->len.pwname, p->pw_name,
										struc->len.grname,
										g->gr_name, struc->len.size,
										struc->buf.stat[y][x].st_size,
										tmp_join = ft_strjoin("Jun  1  ",
											time_f + 20),
										struc->buf.buf[y][x], test_1);
								free(tmp_perm);
								free(tmp_join);
							}
							free(test_1);
						}
						free(tmp);
					}
					else
					{
						ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s\n",
								tmp_perm = permision_l(&struc->buf.stat[y][x]),
								struc->len.nlink,
								struc->buf.stat[y][x].st_nlink,
								struc->len.pwname, p->pw_name,
								struc->len.grname,
								g->gr_name, struc->len.size,
								struc->buf.stat[y][x].st_size,
								tmp_join = ft_strjoin("Jun  1  ", time_f + 20),
								struc->buf.buf[y][x]);
						free(tmp_perm);
						free(tmp_join);
					}
				}
				else
				{
					if (S_ISLNK(struc->buf.stat[y][x].st_mode) == 1)
					{
						tmp = ft_memalloc(32767);
						sprintf(tmp, "%s/%s", save_name[y],
								struc->buf.buf[y][x]);
						if (stat(tmp, &stat_nlink))
						{
							ft_printf("ls :");
							perror(tmp);
						}
						else
						{
							test_1 = ft_memalloc(256);
							if ((readlink(tmp, test_1, 256)) == -1)
							{
								ft_printf("ls: ");
								perror(tmp);
							}
							else
							{
								ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s -> %s\n"
										, tmp_perm =
										permision_l(&struc->buf.stat[y][x]),
										struc->len.nlink,
										struc->buf.stat[y][x].st_nlink,
										struc->len.pwname, p->pw_name,
										struc->len.grname,
										g->gr_name, struc->len.size,
										struc->buf.stat[y][x].st_size,
										ctime(&time_files)
										+ 4, struc->buf.buf[y][x], test_1);
								free(tmp_perm);
							}
							free(test_1);
						}
						free(tmp);
					}
					else
					{
						ft_printf("%s %*d %-*s  %-*s  %*lld %.12s %s\n",
								tmp_perm = permision_l(&struc->buf.stat[y][x]),
								struc->len.nlink,
								struc->buf.stat[y][x].st_nlink,
								struc->len.pwname, p->pw_name,
								struc->len.grname,
								g->gr_name, struc->len.size,
								struc->buf.stat[y][x].st_size,
								ctime(&time_files)
								+ 4, struc->buf.buf[y][x]);
						free(tmp_perm);
					}
				}
			}
			else
			{
				ft_printf("%s\n", struc->buf.buf[y][x]);
			}
			if (struc->flag.r_maj == 0)
				free(struc->buf.buf[y][x]);
			x++;
		}
		write(1, "\n", 1);
		z = 0;
		while (z < struc->buf.cont_files[y] && struc->flag.r_maj == 1)
		{
			if (struc->flag.a_min == 1 && ft_strcmp(struc->buf.buf[y][z], ".")
					!= 0 && ft_strcmp(struc->buf.buf[y][z], "..") != 0)
				recursive_r_maj_files_ls(save_name[y], struc->buf.buf[y][z],
						struc);
			else if (struc->flag.a_min == 0)
				recursive_r_maj_files_ls(save_name[y], struc->buf.buf[y][z],
						struc);
			free(struc->buf.buf[y][z]);
			z++;
		}
		free(struc->buf.save_name[y]);
		free(struc->buf.stat[y]);
		free(struc->buf.buf[y]);
		y++;
	}
	free(struc->buf.buf);
	free(struc->buf.save_name);
	free(struc->buf.cont_files);
	free(struc->buf.stat);
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
	if (ft_memcmp(str, "/", ft_strlen(str)) == 0)
		ft_sprintf(tmp, "%s/%s", str, name);
	else
		ft_sprintf(tmp, "%s/%s", str, name);
	if ((lstat(tmp, &struc->buf.stat[struc->len.cont_arg_2][cont_files]))
			== -1)
	{
		ft_printf("lstat de write_struc_ls\n");
		perror(tmp);
	}
	free(tmp);
}

void	files_is_dir(char *str, t_struc_ls *struc)
{
	DIR				*dir;
	size_t			x;
	struct dirent	*result;
	struct stat		stat_files;
	char			*tmp;

	if ((dir = opendir(str)) == NULL)
	{
		ft_printf("opendir de files_is_dir\n");
		perror(str);
		return ;
	}
	while ((result = readdir(dir)) != NULL)
	{
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
		free(tmp);
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
	{
		ft_printf("lstat de ft_while_ls\n");
		perror(str);
		return ;
	}
	if (S_ISDIR(stat_dir.st_mode) == 1)
	{
		if ((struc->len.dir = ft_len_dir(str, struc)) == -1)
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
	if ((tmp[0] = ft_memalloc(sizeof(char) * len_buf)) == NULL)
		return ;
	if (ft_memcmp(save_name, "/", ft_strlen(save_name)) == 0)
		ret = ft_sprintf(tmp[0], "%s%s", save_name, buf);
	else
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
	free(tmp[0]);
	free(tmp);
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
