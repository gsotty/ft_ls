/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 10:02:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/10 12:00:21 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include  <stdio.h>

int		main(int argc, char **argv)
{
	size_t		cont_argc;
	char		***data;
	t_struc_ls	struc;

	ft_memset(&struc, 0, sizeof(t_struc_ls));
	struc.buf.argc = argc;
	cont_argc = check_flag_ls(argc, argv, &struc);
	data = readdir_ls(&struc, argv, cont_argc);
	int		y = 0;
	int		x = 0;
	while (x < struc.buf.argc - cont_argc)
	{
		y = 0;
		while (y < (int)struc.buf.len_dir)
		{
			ft_printf("%s\n", data[x][y]);
			ft_printf("%d\n", struc.buf.nbr_files);
			y++;
		}
		x++;
	}
	return (0);
}
