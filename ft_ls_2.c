/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:16:42 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 17:28:50 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char	**read_files(char *str, t_struc_ls *struc, char **data)
{
	DIR				*dir;
	char			*tmp;
	char			*str_errno;
	size_t			x;

	x = 0;
	if ((dir = opendir(str)) == NULL)
	{
		str_errno = strerror(errno);
		if (ft_strcmp(str_errno, "Not a directory") != 0)
		{
			struc->arg_np.err = 1;
			struc->arg_np.data_size = ft_remalloc_size(struc->arg_np.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			tmp = ft_strjoin("ft_ls: ", str);
			tmp = ft_strjoin(tmp, ": ");
			data[x] = ft_strjoin(tmp, str_errno);
			struc->arg_np.data_size[x] = ft_strlen(data[x]) + 1;
			struc->arg_np.data_nbr = x;
			x++;
		}
		else
			data = readdir_ls_f(struc, data, str);
		return (data);
	}
	data = readdir_ls(dir, struc, data, str);
	closedir(dir);
	return (data);
}

int			main(int argc, char **argv)
{
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
		while (tmp_data->nbr_dir < struc.arg_np.nbr_dir)
		{
			tmp_data->directory = ft_remalloc_size(tmp_data->directory,
					tmp_data->nbr_dir + 1, tmp_data->nbr_dir);
			tmp_data->directory[tmp_data->nbr_dir] =
				struc.arg_np.directory[tmp_data->nbr_dir];
			tmp_data->nbr_dir++;
		}
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
	write_list(begin_list, &struc);
	return (0);
}
