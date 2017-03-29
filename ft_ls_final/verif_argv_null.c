/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_argv_null.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:43:20 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 17:44:33 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		verif_argv_null(int argc, char **argv, int y)
{
	int		x;

	x = y;
	while (x < argc)
	{
		if (argv[x][0] == '\0')
		{
			ft_printf("ls: fts_open: No such file or directory\n");
			exit(1);
		}
		x++;
	}
}
