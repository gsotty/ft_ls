/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 10:02:15 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/07 15:03:50 by gsotty           ###   ########.fr       */
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
	struc.argc = argc;
	cont_argc = check_flag_ls(argv, &struc);
	data = readdir_ls(&struc, argv, cont_argc);
	int		y = 0;
	int		x = 0;
	while (x < struc.argc - cont_argc)
	{
		y = 0;
		while (y < (int)struc.len_dir)
		{
			ft_printf("%s\n", data[x][y]);
			ft_printf("%d\n", struc.nbr_files);
			main(1, struc.name[y]);
			y++;
		}
		x++;
	}
	return (0);
}
