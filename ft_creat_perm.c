/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creat_perm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:44:36 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/27 12:14:34 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_creat_perm(char *str, char *name, t_struc_ls *struc)
{
	char			*str_errno;
	char			*tmp_name;
	char			*tm;
	struct stat		buf;
	struct group	*g;
	struct passwd	*p;

	tmp_name = ft_strjoin(str, "/");
	if (stat(ft_strjoin(tmp_name, name), &buf))
	{
		str_errno = strerror(errno);
		ft_printf("%d\n", str_errno);
		return (0);
	}
	p = getpwuid(buf.st_uid);
	g = getgrgid(buf.st_gid);
	tm = ctime(&buf.st_mtime);
	tm[16] = '\0';
	
	return (0);
}
