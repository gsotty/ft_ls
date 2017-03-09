/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_l_min.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:19:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/07 14:30:48 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

char	*creat_l_min(STAT buf, t_struc_ls *struc, char *name, int len_name)
{
	char			*res;
	struct group	*g;
	struct passwd	*p;
	char			*tmp;
	int				ret;

	ret = 0;
	p = getpwuid(buf.st_uid);
	g = getgrgid(buf.st_gid);
	tmp = ft_memalloc(sizeof(char) * (42 + struc->len.nlink + struc->len.size +
			struc->len.pwname + struc->len.grname + len_name));
	ft_memset(tmp, 0, sizeof(char) * (42 + struc->len.nlink + struc->len.size +
			struc->len.pwname + struc->len.grname + len_name));
	ret += ft_sprintf(tmp + ret, "%s ", permision_l(&buf));
	ret += ft_sprintf(tmp + ret, "%*d ", (int)struc->len.nlink, buf.st_nlink);
	ret += ft_sprintf(tmp + ret, "%*s ", (int)struc->len.pwname, p->pw_name);
	ret += ft_sprintf(tmp + ret, " %*s ", (int)struc->len.grname, g->gr_name);
	ret += ft_sprintf(tmp + ret, " %*lld ", (int)struc->len.size, buf.st_size);
	ret += ft_sprintf(tmp + ret, "%.12s ", ctime(&buf.st_mtime) + 4);
	ret += ft_sprintf(tmp + ret, "%.*s", len_name, name);
	tmp[ret] = '\0';
	return (tmp);
}
