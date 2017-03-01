/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 10:22:22 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/01 15:35:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

void	print_l(t_list_ls *tmp_list, int y)
{
	ft_printf("%s", tmp_list->per[y]);
	ft_printf(" %*s", (int)tmp_list->len_m_nl, tmp_list->nlink[y]);
	ft_printf(" %-*s ", (int)tmp_list->len_m_np, tmp_list->pw_name[y]);
	ft_printf(" %-*s ", (int)tmp_list->len_m_ng, tmp_list->gr_name[y]);
	ft_printf(" %*s ", (int)tmp_list->len_m_si, tmp_list->size[y]);
	ft_printf("%s ", tmp_list->mtime[y]);
}

int		write_list(t_list_ls *begin_list, t_struc_ls *struc)
{
	int			y;
	char		**data;
	t_list_ls	*tmp_list;

	tmp_list = begin_list;
	while (tmp_list != NULL)
	{
		if (struc->arg_p.multi == 1 && tmp_list->err != 1)
			ft_printf("%s:\n", tmp_list->dossier);
		y = 0;
		if (struc->arg_p.r_min == 1)
		{
			y = tmp_list->data_nbr - 1;
			while (y >= 0)
			{
				if (struc->arg_p.l_min == 1 && tmp_list->err != 1)
					print_l(tmp_list, y);
				ft_printf("%s\n", tmp_list->data[y]);
				y--;
			}
		}
		else
		{
			while (y < tmp_list->data_nbr)
			{
				if (struc->arg_p.l_min == 1 && tmp_list->err != 1)
					print_l(tmp_list, y);
				ft_printf("%s\n", tmp_list->data[y]);
				y++;
			}
		}
		if (struc->arg_p.multi == 1 && !(tmp_list->next == NULL))
			write(1, "\n", 1);
		tmp_list = tmp_list->next;
	}
	return (0);
}
