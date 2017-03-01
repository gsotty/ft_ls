/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 11:01:59 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 12:27:08 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**readdir_ls_f(t_struc_ls *struc, char **data, char *str)
{
	size_t			x;
	char			*str_errno;
	char			*tmp_stat;
	char			*tm;
	struct group	*g;
	struct passwd	*p;
	struct stat		buf;

	x = 0;
	if (struc->arg_p.l_min == 1)
	{
		//	tmp_stat = ft_strjoin(str, "/");
		//	tmp_stat = ft_strjoin(tmp_stat, str);
		if (stat(str, &buf) == -1)
		{
			str_errno = strerror(errno);
			ft_printf("%d\n", errno);
			ft_printf("%s\n", str);
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
		struc->arg_np.per[x] = permision_l(&buf);
		if (struc->arg_np.len_m_nl < ft_strlen(ft_itoa(buf.st_nlink)))
			struc->arg_np.len_m_nl = ft_strlen(ft_itoa(buf.st_nlink));
		struc->arg_np.nlink[x] = ft_itoa(buf.st_nlink);
		if (struc->arg_np.len_m_si < ft_strlen(ft_itoa(buf.st_size)))
			struc->arg_np.len_m_si = ft_strlen(ft_itoa(buf.st_size));
		struc->arg_np.size[x] = ft_itoa(buf.st_size);
		struc->arg_np.gr_name[x] = ft_strdup(g->gr_name);
		struc->arg_np.mtime[x] = ft_strdup(tm + 4);
		struc->arg_np.pw_name[x] = ft_strdup(p->pw_name);
	}
	if ((struc->arg_p.a_min == 1) && (str[0] == '.'))
	{
	/*	if (S_ISDIR(buf.st_mode) == 1)
		{
			struc->arg_np.directory = ft_remalloc_size(
					struc->arg_np.directory, struc->arg_np.nbr_dir + 1,
					struc->arg_np.nbr_dir);
			struc->arg_np.directory[struc->arg_np.nbr_dir] = x;
			struc->arg_np.nbr_dir++;
		}
	*/	struc->arg_np.data_size = ft_remalloc_size(struc->arg_np.data_size,
				x + 1, x);
		data = ft_remalloc_data(data, x + 1, x);
		data[x] = ft_strdup(str);
		struc->arg_np.data_size[x] = ft_strlen(str);
		data[x][struc->arg_np.data_size[x]] = '\0';
		x++;
	}
	else if ((str[0] != '.'))
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
		data[x] = ft_strdup(str);
		struc->arg_np.data_size[x] = ft_strlen(str);
		data[x][struc->arg_np.data_size[x]] = '\0';
		x++;
	}
	struc->arg_np.data_nbr = x;
	return (data);
}
