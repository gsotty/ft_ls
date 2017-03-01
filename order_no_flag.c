/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_no_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:27:40 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/01 15:40:44 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	**order(size_t data_nbr, char **data, size_t *data_size,
		t_struc_ls *struc)
{
	int		x;
	int		verif;
	char	*tmp;

	if (struc->arg_p.r_min == 1)
	{
		verif = 1;
		while (verif == 1)
		{
			x = 0;
			verif = 0;
			while (x < data_nbr - 1)
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
			while (x < data_nbr - 1)
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
	char		**mtime;
	char		**dossier;
	size_t		*size;
	t_list_ls	*tmp;

	x = 0;
	tmp = begin_list;
	mtime = ft_memalloc(1);
	dossier = ft_memalloc(1);
	size = ft_memalloc(1);
	while (tmp != NULL)
	{
		mtime = ft_remalloc_data(dossier, x + 2, x);
		dossier = ft_remalloc_data(dossier, x + 2, x);
		size = ft_remalloc_size(size, x + 2, x);
		dossier[x] = ft_strdup(tmp->dossier);
		dossier[x + 1] = NULL;
		size[x] = (size_t)ft_strlen(dossier[x]);
		tmp = tmp->next;
		x++;
	}
	dossier = order(x, dossier, size, struc);
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

char		**order_no_flag(size_t data_nbr, char **data, size_t *data_size,
		t_struc_ls *struc)
{
	int		x;
	int		verif;
	char	*tmp;

	verif = 1;
	while (verif == 1)
	{
		x = 0;
		verif = 0;
		while (x < data_nbr - 1)
		{
			if (struc->arg_p.t_min == 1)
			{
				//	ft_printf("%s, %s\n", mtime[x], mtime[x + 1]);
			}
			else
			{
				if (ft_memcmp(data[x], data[x + 1], (data_size[x] < data_size[x + 1])
							? data_size[x] : data_size[x + 1]) > 0)
				{
					tmp = ft_strdup(data[x]);
					data[x] = ft_strdup(data[x + 1]);
					data[x + 1] = ft_strdup(tmp);
					verif = 1;
				}
			}
			x++;
		}
	}
	return (data);
}
