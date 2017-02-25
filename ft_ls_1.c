/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:16:42 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/25 18:15:39 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_lstadd_ls(t_list_ls **alst, t_list_ls *new)
{
	if (alst == NULL || new == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

t_list_ls	*ft_lstnew_ls(char **data, size_t *data_size, size_t data_nbr)
{
	size_t		x;
	t_list_ls	*new;

	if ((new = (t_list_ls *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	x = 0;
	if (data != NULL)
	{
		if (!(new->data = (char **)malloc(sizeof(char *) * data_nbr)))
			return (NULL);
		if (!(new->data_size = (size_t *)malloc(sizeof(size_t) * data_nbr)))
			return (NULL);
		while (x < data_nbr)
		{
			if (!(new->data[x] = (char *)malloc(sizeof(char) * data_size[x])))
				return (NULL);
			ft_memcpy(new->data[x], data[x], data_size[x]);
			new->data_size[x] = data_size[x];
			x++;
		}
		new->data_nbr = data_nbr;
		new->err = 0;
	}
	else
	{
		new->data = NULL;
		new->data_size = NULL;
		new->data_nbr = 0;
		new->err = 0;
	}
	new->next = NULL;
	return (new);
}

#include <dirent.h>

size_t	*ft_remalloc_size(size_t *data, size_t len_d, size_t len_s)
{
	int			x;
	size_t		*tmp_data;

	if (len_d <= len_s)
		return (data);
	x = 0;
	if (!(tmp_data = ft_memalloc((sizeof(size_t *) * len_d))))
		return (NULL);
	while (x < len_s)
	{
		tmp_data[x] = data[x];
		x++;
	}
	free(data);
	if (!(data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	ft_memset(data, 0, sizeof(char *) * len_d);
	x = 0;
	while (x < len_s)
	{
		data[x] = tmp_data[x];
		x++;
	}
	free(tmp_data);
	return (data);
}

char	**ft_remalloc_data(char **data, size_t len_d, size_t len_s)
{
	int			x;
	char		**tmp_data;

	if (len_d <= len_s)
		return (data);
	x = 0;
	if (!(tmp_data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	while (x < len_s)
	{
		tmp_data[x] = ft_strdup(data[x]);
//		free(data[x]);
		x++;
	}
//	free(data);
	if (!(data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	ft_memset(data, 0, sizeof(char *) * len_d);
	x = 0;
	while (x < len_s)
	{
		data[x] = ft_strdup(tmp_data[x]);
//		free(tmp_data[x]);
		x++;
	}
//	free(tmp_data);
	return (data);
}

#include <errno.h>

char	**read_files(char **argv, t_struc_ls *struc, char **data)
{
	struct dirent	*result;
	DIR				*dir;
	char			*tmp;
	char			*str_errno;
	int				errno;

	size_t			x;

	x = 0;
	if ((dir = opendir(argv[struc->len.cont_arg])) == NULL)
	{
		str_errno = strerror(errno);
		struc->flag.err = 1;
		if (ft_strcmp(str_errno, "Not a directory") != 0)
		{
			struc->len.data_size = ft_remalloc_size(struc->len.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			tmp = ft_strjoin("ft_ls: ", argv[struc->len.cont_arg]);
			tmp = ft_strjoin(tmp, ": ");
			data[x] = ft_strjoin(tmp, str_errno);
			struc->len.data_size[x] = ft_strlen(data[x] - 1);
			x++;
		}
		else
		{
			struc->len.data_size = ft_remalloc_size(struc->len.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			data[x] = ft_strdup(argv[struc->len.cont_arg]);
			struc->len.data_size[x] = ft_strlen(data[x] - 1);
			x++;
		}
		struc->len.data_nbr = x;
		return (data);
	}
	while ((result = readdir(dir)) != NULL)
	{
		if ((struc->flag.a_min == 1) && (result->d_name[0] == '.'))
		{
			struc->len.data_size = ft_remalloc_size(struc->len.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			data[x] = ft_strdup(result->d_name);
			struc->len.data_size[x] = ft_strlen(result->d_name - 1);
			x++;
		}
		else if ((result->d_name[0] != '.'))
		{
			struc->len.data_size = ft_remalloc_size(struc->len.data_size,
					x + 1, x);
			data = ft_remalloc_data(data, x + 1, x);
			data[x] = ft_strdup(result->d_name);
			struc->len.data_size[x] = ft_strlen(result->d_name - 1);
			x++;
		}
	}
	struc->len.data_nbr = x;
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
	struc.len.cont_arg = 1;
	struc.len.tmp_argc = argc;
	check_flag_ls(argv, &struc);
	data = ft_memalloc(sizeof(data) * argc);
	while (struc.len.cont_arg < struc.len.tmp_argc)
	{
		tmp_data = ft_lstnew_ls(read_files(argv, &struc, data),
				struc.len.data_size, struc.len.data_nbr);
		tmp_data->dossier = ft_strdup(argv[struc.len.cont_arg]);
		if (struc.flag.err == 1)
		{
			tmp_data->err = 1;
			struc.flag.err = 0;
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
		struc.len.cont_arg++;
	}
	int	y = 0;
	while (begin_list != NULL)
	{
		if (struc.flag.multi == 1 && begin_list->err != 1)
			ft_printf("%s:\n", begin_list->dossier);
		y = 0;
		while (y < begin_list->data_nbr)
		{
			ft_printf("%s\n", begin_list->data[y]);
			y++;
		}
		if (struc.flag.multi == 1 && !(begin_list->next == NULL))
			ft_printf("\n");
		begin_list = begin_list->next;
	}
	return (0);
}
