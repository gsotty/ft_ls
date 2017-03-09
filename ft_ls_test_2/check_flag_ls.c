/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:20:58 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/02 10:45:55 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	verif_flag_ls(char *str, t_struc_ls *struc, size_t pos_str)
{
	if (str[0] == '-')
	{
		while (str[pos_str] != '\0')
		{
			if (str[pos_str] == 'R')
				struc->r_maj = 1;
			else if (str[pos_str] == 'a')
				struc->a_min = 1;
			else if (str[pos_str] == 'l')
				struc->l_min = 1;
			else if (str[pos_str] == 'r')
				struc->r_min = 1;
			else if (str[pos_str] == 't')
				struc->t_min = 1;
			else
			{
				ft_printf("./ft_ls: illegal option -- %c\n", str[pos_str]);
				ft_printf("usage: ./ft_ls [-Ralrt] [file ...]\n");
				exit(0);
			}
			pos_str++;
		}
		return (1);
	}
	return (0);
}

int			check_flag_ls(char **argv, t_struc_ls *struc)
{
	int		x;

	x = 1;
	while (x < struc->argc)
	{
		if ((verif_flag_ls(argv[x], struc, 1)) == 0)
			break ;
		x++;
	}
	if (x == struc->argc)
	{
		argv[struc->argc] = ft_strdup(".");
		struc->argc++;
	}
	else if (x + 1 < struc->argc)
		struc->multi = 1;
	return (x);
}
