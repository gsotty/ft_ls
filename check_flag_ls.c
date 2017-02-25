/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:20:58 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/25 12:46:29 by gsotty           ###   ########.fr       */
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
				struc->flag.r_maj = 1;
			else if (str[pos_str] == 'a')
				struc->flag.a_min = 1;
			else if (str[pos_str] == 'l')
				struc->flag.l_min = 1;
			else if (str[pos_str] == 'r')
				struc->flag.r_min = 1;
			else if (str[pos_str] == 't')
				struc->flag.t_min = 1;
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
	while (struc->len.cont_arg < struc->len.tmp_argc)
	{
		if (verif_flag_ls(argv[struc->len.cont_arg], struc, 1) == 0)
			break ;
		struc->len.cont_arg++;
	}
	if (struc->len.cont_arg == struc->len.tmp_argc)
	{
		argv[struc->len.tmp_argc] = ft_strdup(".");
		struc->len.tmp_argc++;
	}
	else if (struc->len.cont_arg < struc->len.tmp_argc)
		struc->flag.multi = 1;
	return (0);
}
