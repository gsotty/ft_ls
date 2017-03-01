/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_no_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:27:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/01 17:28:24 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	**order(size_t *time, char **data, size_t *data_size,
		t_struc_ls *struc)
{
	int			x;
	int			verif;
	char		*tmp;

	if (struc->arg_p.r_min == 1)
	{
		verif = 1;
		while (verif == 1)
		{
			x = 0;
			verif = 0;
			while (x < struc->arg_p.nbr_dir)
			{
				if (ft_memcmp(data[x], data[x + 1], (data_size[x] <
								data_size[x + 1]) ? data_size[x] :
							data_size[x + 1]) < 0)
				{
					tmp = ft_strdup(data[x]);
					data[x] = ft_strdup(data[x + 1]);
					data[x + 1] = ft_strdup(tmp);
					verif = 1;
				}
				x++;
			}
		}
	}
	else
	{
		verif = 1;
		while (verif == 1)
		{
			x = 0;
			verif = 0;
			while (x < struc->arg_p.nbr_dir)
			{
				if (ft_memcmp(data[x], data[x + 1], (data_size[x] <
								data_size[x + 1]) ? data_size[x] :
							data_size[x + 1]) > 0)
				{
					tmp = ft_strdup(data[x]);
					data[x] = ft_strdup(data[x + 1]);
					data[x + 1] = ft_strdup(tmp);
					verif = 1;
				}
				x++;
			}
		}
	}
	return (data);
}

char		**check_min_dos(t_list_ls *begin_list, t_struc_ls *struc)
{
	int			x;
	char		**dossier;
	size_t		*size;
	size_t		*time;
	t_list_ls	*tmp;

	x = 0;
	tmp = begin_list;
	dossier = ft_memalloc(1);
	size = ft_memalloc(1);
	time = ft_memalloc(1);
	while (tmp != NULL)
	{
		dossier = ft_remalloc_data(dossier, x + 2, x);
		size = ft_remalloc_size(size, x + 2, x);
		time = ft_remalloc_size(time, x + 2, x);
		dossier[x] = ft_strdup(tmp->dossier);
		dossier[x + 1] = NULL;
		size[x] = (size_t)ft_strlen(dossier[x]);
		time[x] = tmp->time_dir;
		tmp = tmp->next;
		x++;
	}
	struc->arg_p.nbr_dir = x;
	dossier = order(time, dossier, size, struc);
	return (dossier);
}

t_list_ls	*order_list(t_list_ls *begin_list, t_struc_ls *struc)
{
	int			x;
	char		**dossier;
	t_list_ls	*tmp;
	t_list_ls	*tmp_2;
	t_list_ls	*tmp_begin;

	x = 0;
	tmp_2 = NULL;
	tmp = tmp_2;
	dossier = check_min_dos(begin_list, struc);
	while (dossier[x] != NULL)
	{
		tmp_begin = begin_list;
		while (tmp_begin != NULL)
		{
			if (ft_memcmp(tmp_begin->dossier, dossier[x],
						ft_strlen(dossier[x])) == 0)
			{
				if (tmp_2 == NULL)
				{
					tmp = tmp_begin;
					tmp_2 = tmp;
				}
				else
				{
					tmp->next = tmp_begin;
					tmp = tmp->next;
				}
				break ;
			}
			tmp_begin = tmp_begin->next;
		}
		x++;
	}
	tmp->next = NULL;
	return (tmp_2);
}

t_list_ls	*order_no_flag(t_list_ls *begin, t_struc_ls *struc)
{
	int			x;
	int			verif;
	char		*tmp;
	size_t		tmp_2;
	char		*tmp_per;
	char		*tmp_nlink;
	char		*tmp_pw_name;
	char		*tmp_gr_name;
	char		*tmp_size;
	char		*tmp_mtime;
	t_list_ls	*lst;

	verif = 1;
	lst = begin;
	while (verif == 1)
	{
		x = 0;
		verif = 0;
		while (x < lst->data_nbr - 1)
		{
			if (struc->arg_p.t_min == 1)
			{
				if (lst->time[x] < lst->time[x + 1])
				{
					tmp_2 = lst->time[x];
					lst->time[x] = lst->time[x + 1];
					lst->time[x + 1] = tmp_2;
					tmp_per = ft_strdup(lst->per[x]);
					lst->per[x] = ft_strdup(lst->per[x + 1]);
					lst->per[x + 1] = ft_strdup(tmp_per);
					tmp_nlink = ft_strdup(lst->nlink[x]);
					lst->nlink[x] = ft_strdup(lst->nlink[x + 1]);
					lst->nlink[x + 1] = ft_strdup(tmp_nlink);
					tmp_pw_name = ft_strdup(lst->pw_name[x]);
					lst->pw_name[x] = ft_strdup(lst->pw_name[x + 1]);
					lst->pw_name[x + 1] = ft_strdup(tmp_pw_name);
					tmp_gr_name = ft_strdup(lst->gr_name[x]);
					lst->gr_name[x] = ft_strdup(lst->gr_name[x + 1]);
					lst->gr_name[x + 1] = ft_strdup(tmp_gr_name);
					tmp_size = ft_strdup(lst->size[x]);
					lst->size[x] = ft_strdup(lst->size[x + 1]);
					lst->size[x + 1] = ft_strdup(tmp_size);
					tmp_mtime = ft_strdup(lst->mtime[x]);
					lst->mtime[x] = ft_strdup(lst->mtime[x + 1]);
					lst->mtime[x + 1] = ft_strdup(tmp_mtime);
					tmp = ft_strdup(lst->data[x]);
					lst->data[x] = ft_strdup(lst->data[x + 1]);
					lst->data[x + 1] = ft_strdup(tmp);
					verif = 1;
				}
			}
			else
			{
				if (ft_memcmp(lst->data[x], lst->data[x + 1],
							(lst->data_size[x] < lst->data_size[x + 1])
							? lst->data_size[x] : lst->data_size[x + 1]) > 0)
				{
					tmp_per = ft_strdup(lst->per[x]);
					lst->per[x] = ft_strdup(lst->per[x + 1]);
					lst->per[x + 1] = ft_strdup(tmp_per);
					tmp_nlink = ft_strdup(lst->nlink[x]);
					lst->nlink[x] = ft_strdup(lst->nlink[x + 1]);
					lst->nlink[x + 1] = ft_strdup(tmp_nlink);
					tmp_pw_name = ft_strdup(lst->pw_name[x]);
					lst->pw_name[x] = ft_strdup(lst->pw_name[x + 1]);
					lst->pw_name[x + 1] = ft_strdup(tmp_pw_name);
					tmp_gr_name = ft_strdup(lst->gr_name[x]);
					lst->gr_name[x] = ft_strdup(lst->gr_name[x + 1]);
					lst->gr_name[x + 1] = ft_strdup(tmp_gr_name);
					tmp_size = ft_strdup(lst->size[x]);
					lst->size[x] = ft_strdup(lst->size[x + 1]);
					lst->size[x + 1] = ft_strdup(tmp_size);
					tmp_mtime = ft_strdup(lst->mtime[x]);
					lst->mtime[x] = ft_strdup(lst->mtime[x + 1]);
					lst->mtime[x + 1] = ft_strdup(tmp_mtime);
					tmp = ft_strdup(lst->data[x]);
					lst->data[x] = ft_strdup(lst->data[x + 1]);
					lst->data[x + 1] = ft_strdup(tmp);
					verif = 1;
				}
			}
			x++;
		}
	}
	return (lst);
}
