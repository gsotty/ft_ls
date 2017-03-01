/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 09:19:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/01 16:54:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list_ls	*struc_to_lst(t_list_ls *new, t_struc_ls *struc, int x)
{
	if (new->per == NULL)
		new->per = ft_memalloc(sizeof(char *) * struc->arg_np.data_nbr + 1);
	if (new->nlink == NULL)
		new->nlink = ft_memalloc(sizeof(char *) * struc->arg_np.data_nbr + 1);
	if (new->pw_name == NULL)
		new->pw_name = ft_memalloc(sizeof(char *) * struc->arg_np.data_nbr + 1);
	if (new->gr_name == NULL)
		new->gr_name = ft_memalloc(sizeof(char *) * struc->arg_np.data_nbr + 1);
	if (new->size == NULL)
		new->size = ft_memalloc(sizeof(char *) * struc->arg_np.data_nbr + 1);
	if (new->mtime == NULL)
		new->mtime = ft_memalloc(sizeof(char *) * struc->arg_np.data_nbr + 1);
	if (new->time == NULL)
		new->time = ft_memalloc(sizeof(size_t) * struc->arg_np.data_nbr + 1);
	new->per[x] = ft_strdup(struc->arg_np.per[x]);
	new->nlink[x] = ft_strdup(struc->arg_np.nlink[x]);
	new->pw_name[x] = ft_strdup(struc->arg_np.pw_name[x]);
	new->gr_name[x] = ft_strdup(struc->arg_np.gr_name[x]);
	new->size[x] = ft_strdup(struc->arg_np.size[x]);
	new->mtime[x] = ft_strdup(struc->arg_np.mtime[x]);
	new->time[x] = struc->arg_np.time[x];
	if (new->len_m_nl == 0)
		new->len_m_nl = struc->arg_np.len_m_nl;
	if (new->len_m_si == 0)
		new->len_m_si = struc->arg_np.len_m_si;
	if (new->len_m_np == 0)
		new->len_m_np = struc->arg_np.len_m_np;
	if (new->len_m_ng == 0)
		new->len_m_ng = struc->arg_np.len_m_ng;
	return (new);
}

t_list_ls			*ft_lstnew_ls(char **data, size_t *data_size,
		size_t data_nbr, t_struc_ls *struc)
{
	size_t		x;
	t_list_ls	*new;

	x = 0;
	if ((new = (t_list_ls *)malloc(sizeof(t_list_ls))) == NULL)
		return (NULL);
	if (data != NULL)
	{
		ft_memset(new, 0, sizeof(t_list_ls));
		if (struc->arg_np.err == 1)
			new->err = 1;
		if (!(new->data = (char **)malloc(sizeof(char *) * data_nbr)))
			return (NULL);
		if (!(new->data_size = (size_t *)malloc(sizeof(size_t) * data_nbr)))
			return (NULL);
		while (x < data_nbr)
		{
			if (struc->arg_p.l_min && new->err != 1)
				new = struc_to_lst(new, struc, x);
			if (!(new->data[x] = (char *)malloc(sizeof(char) * data_size[x] + 1)))
				return (NULL);
			ft_memcpy(new->data[x], data[x], data_size[x]);
			new->data_size[x] = data_size[x];
			new->data[x][data_size[x]] = '\0';
			x++;
		}
		new->data_nbr = data_nbr;
	}
	else
		ft_memset(new, 0, sizeof(t_list_ls));
	return (new);
}
