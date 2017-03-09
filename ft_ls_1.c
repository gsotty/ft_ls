/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:16:42 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/02 09:42:22 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char	**read_files(char *str, t_struc_ls *struc, char **data)
{
	struct group	*g;
	struct passwd	*p;
	struct stat		buf;
	struct dirent	*result;
	char			*tm;
	DIR				*dir;
	char			*tmp;
	char			*str_errno;
	int				errno;
	char			*tmp_char;

	size_t			x;

	x = 0;
	if ((dir = opendir(str)) == NULL)
	{
		str_errno = strerror(errno);
		struc->arg_np.err = 1;
		if (ft_strcmp(str_errno, "Not a directory") != 0)
		{
			struc->arg_np.data_size = ft_remalloc_size(struc->arg_np.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			tmp = ft_strjoin("ft_ls: ", str);
			tmp = ft_strjoin(tmp, ": ");
			data[x] = ft_strjoin(tmp, str_errno);
			struc->arg_np.data_size[x] = ft_strlen(data[x]) + 1;
			x++;
		}
		else
		{
			struc->arg_np.data_size = ft_remalloc_size(struc->arg_np.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			data[x] = ft_strdup(str);
			struc->arg_np.data_size[x] = ft_strlen(data[x]) + 1;
			x++;
		}
		struc->arg_np.data_nbr = x;
		return (data);
	}
	int		fd;
	char	*tmp_stat;
	while ((result = readdir(dir)) != NULL)
	{
		if (struc->arg_p.l_min == 1)
		{
			tmp_stat = ft_strjoin(str, "/");
			tmp_stat = ft_strjoin(tmp_stat, result->d_name);
			if (stat(tmp_stat, &buf) == -1)
			{
				str_errno = strerror(errno);
				ft_printf("%d\n", errno);
				ft_printf("%s\n", result->d_name);
				ft_printf("%s\n", str_errno);
				return (0);
			}
			p = getpwuid(buf.st_uid);
			g = getgrgid(buf.st_gid);
			tm = ctime(&buf.st_mtime);
			tm[16] = '\0';
			if (struc->arg_np.per == NULL)
				struc->arg_np.per = ft_memalloc(sizeof(char) * x);
			else
				struc->arg_np.per = ft_remalloc_data(struc->arg_np.per,
						x + 1, x);
			if (struc->arg_np.nlink == NULL)
				struc->arg_np.nlink = ft_memalloc(sizeof(char) * x);
			else
				struc->arg_np.nlink = ft_remalloc_data(struc->arg_np.nlink,
						x + 1, x);
			if (struc->arg_np.pw_name == NULL)
				struc->arg_np.pw_name = ft_memalloc(sizeof(char) * x);
			else
				struc->arg_np.pw_name = ft_remalloc_data(struc->arg_np.pw_name,
						x + 1, x);
			if (struc->arg_np.gr_name == NULL)
				struc->arg_np.gr_name = ft_memalloc(sizeof(char) * x);
			else
				struc->arg_np.gr_name = ft_remalloc_data(struc->arg_np.gr_name,
						x + 1, x);
			if (struc->arg_np.size == NULL)
				struc->arg_np.size = ft_memalloc(sizeof(char) * x);
			else
				struc->arg_np.size = ft_remalloc_data(struc->arg_np.size,
						x + 1, x);
			if (struc->arg_np.mtime == NULL)
				struc->arg_np.mtime = ft_memalloc(sizeof(char) * x);
			else
				struc->arg_np.mtime = ft_remalloc_data(struc->arg_np.mtime,
						x + 1, x);
			if (struc->arg_np.time == NULL)
				struc->arg_np.time = ft_memalloc(sizeof(size_t) * x);
			else
				struc->arg_np.time = ft_remalloc_size(struc->arg_np.time,
						x + 1, x);
			struc->arg_np.per[x] = permision_l(&buf);
			if (struc->arg_np.len_m_nl < ft_strlen(ft_itoa(buf.st_nlink)))
				struc->arg_np.len_m_nl = ft_strlen(ft_itoa(buf.st_nlink));
			struc->arg_np.nlink[x] = ft_itoa(buf.st_nlink);
			if (struc->arg_np.len_m_si < ft_strlen(ft_itoa(buf.st_size)))
				struc->arg_np.len_m_si = ft_strlen(ft_itoa(buf.st_size));
			struc->arg_np.size[x] = ft_itoa(buf.st_size);
			struc->arg_np.gr_name[x] = ft_strdup(g->gr_name);
			if (struc->arg_np.len_m_ng < ft_strlen(g->gr_name))
				struc->arg_np.len_m_ng = ft_strlen(g->gr_name);
			struc->arg_np.mtime[x] = ft_strdup(tm + 4);
			struc->arg_np.pw_name[x] = ft_strdup(p->pw_name);
			if (struc->arg_np.len_m_np < ft_strlen(p->pw_name))
				struc->arg_np.len_m_np = ft_strlen(p->pw_name);
			struc->arg_np.per[x] = ft_strdup(struc->arg_np.per[x]);
			struc->arg_np.time[x] = buf.st_mtime;
		}
		if ((struc->arg_p.a_min == 1) && (result->d_name[0] == '.'))
		{
			if (S_ISDIR(buf.st_mode) == 1)
			{
				struc->arg_np.directory = ft_remalloc_size(
						struc->arg_np.directory, struc->arg_np.nbr_dir + 1,
						struc->arg_np.nbr_dir);
				struc->arg_np.directory[struc->arg_np.nbr_dir] = x;
				struc->arg_np.nbr_dir++;
			}
			struc->arg_np.data_size = ft_remalloc_size(struc->arg_np.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			data[x] = ft_strdup(result->d_name);
			struc->arg_np.data_size[x] = result->d_namlen;
			data[x][result->d_namlen] = '\0';
			x++;
		}
		else if ((result->d_name[0] != '.'))
		{
			if (S_ISDIR(buf.st_mode) == 1)
			{
				struc->arg_np.directory = ft_remalloc_size(
						struc->arg_np.directory, struc->arg_np.nbr_dir + 1,
						struc->arg_np.nbr_dir);
				struc->arg_np.directory[struc->arg_np.nbr_dir] = x;
				struc->arg_np.nbr_dir++;
			}
			struc->arg_np.data_size = ft_remalloc_size(struc->arg_np.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			data[x] = ft_strdup(result->d_name);
			struc->arg_np.data_size[x] = result->d_namlen;
			data[x][result->d_namlen] = '\0';
			x++;
		}
	}
	struc->arg_np.data_nbr = x;
	closedir(dir);
	return (data);
}

int			main(int argc, char **argv)
{
	struct stat		buf;
	char			*str_errno;
	char			**data;
	t_list_ls		*tmp_data;
	t_list_ls		*list;
	t_list_ls		*begin_list;
	t_struc_ls		struc;

	list = NULL;
	list = begin_list;
	ft_memset(&struc, 0, sizeof(t_struc_ls));
	struc.arg_p.cont_arg = 1;
	struc.arg_p.tmp_argc = argc;
	check_flag_ls(argv, &struc);
	data = ft_memalloc(sizeof(data) * argc);
	while (struc.arg_p.cont_arg < struc.arg_p.tmp_argc)
	{
		ft_memset(&struc.arg_np, 0, sizeof(struc.arg_np));
		tmp_data = ft_lstnew_ls(read_files(argv[struc.arg_p.cont_arg],
					&struc, data), struc.arg_np.data_size,
				struc.arg_np.data_nbr, &struc);
		tmp_data->dossier = ft_strdup(argv[struc.arg_p.cont_arg]);
		tmp_data->directory = ft_memalloc(struc.arg_np.nbr_dir + 1);
		if (stat(argv[struc.arg_p.cont_arg], &buf) == -1)
		{
			str_errno = strerror(errno);
			ft_printf("%d\n", errno);
			ft_printf("%s\n", argv[struc.arg_p.cont_arg]);
			ft_printf("%s\n", str_errno);
			return (0);
		}
		tmp_data->time_dir = buf.st_mtime;
		while (tmp_data->nbr_dir < struc.arg_np.nbr_dir)
		{
			tmp_data->directory = ft_remalloc_size(tmp_data->directory,
					tmp_data->nbr_dir + 1, tmp_data->nbr_dir);
			tmp_data->directory[tmp_data->nbr_dir] =
				struc.arg_np.directory[tmp_data->nbr_dir];
			tmp_data->nbr_dir++;
		}
		tmp_data = order_no_flag(tmp_data, &struc);
		if (begin_list == NULL)
		{
			list = tmp_data;
			begin_list = list;
		}
		else
		{
			list->next = tmp_data;
			list = list->next;
		}
		struc.arg_p.cont_arg++;
	}
	begin_list = order_list(begin_list, &struc);
	write_list(begin_list, &struc);
	return (0);
}
