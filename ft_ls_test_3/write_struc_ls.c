/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_struc_ls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:55:55 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/21 11:04:26 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	write_struc_ls(size_t cont_files, char *str, char *name,
		t_struc_ls *struc)
{
	char	*tmp;

	if (!(struc->buf.buf[struc->len.cont_arg_2][cont_files] =
				ft_memalloc(sizeof(char) * struc->len.namlen + 1)))
		return ;
	ft_memcpy(struc->buf.buf[struc->len.cont_arg_2][cont_files], name,
			struc->len.namlen);
	struc->buf.buf[struc->len.cont_arg_2][cont_files]
		[struc->len.namlen] = '\0';
	if (!(tmp = ft_memalloc(sizeof(char) * struc->len.namlen +
					struc->len.argv + 2)))
		return ;
	if (ft_memcmp(str, "/", ft_strlen(str)) == 0)
		ft_sprintf(tmp, "%s/%s", str, name);
	else
		ft_sprintf(tmp, "%s/%s", str, name);
	if ((lstat(tmp, &struc->buf.stat[struc->len.cont_arg_2][cont_files]))
			== -1)
	{
		ft_printf("lstat de write_struc_ls\n");
		perror(tmp);
	}
	free(tmp);
}
