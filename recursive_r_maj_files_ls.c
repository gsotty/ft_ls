/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_r_maj_files_ls.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:50:10 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 17:47:57 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	cp_struc(t_struc_ls *struc, t_struc_ls *new_struc)
{
	new_struc->flag.r_maj = struc->flag.r_maj;
	new_struc->flag.t_maj = struc->flag.t_maj;
	new_struc->flag.s_maj = struc->flag.s_maj;
	new_struc->flag.a_min = struc->flag.a_min;
	new_struc->flag.f_min = struc->flag.f_min;
	new_struc->flag.l_min = struc->flag.l_min;
	new_struc->flag.u_min = struc->flag.u_min;
	new_struc->flag.r_min = struc->flag.r_min;
	new_struc->flag.s_min = struc->flag.s_min;
	new_struc->flag.t_min = struc->flag.t_min;
	new_struc->flag.one = struc->flag.one;
	new_struc->flag.multi = struc->flag.multi;
}

void		recursive_r_maj_files_ls(char *save_name, char *buf,
		t_struc_ls *struc)
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
	ft_memset(&new_struc, 0, sizeof(t_struc_ls));
	cp_struc(struc, &new_struc);
	ft_ls(1, tmp, 0, &new_struc);
	free(tmp[0]);
	free(tmp);
}
