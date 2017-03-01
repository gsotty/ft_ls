/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:20:58 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/28 10:03:53 by gsotty           ###   ########.fr       */
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
				struc->arg_p.r_maj = 1;
			else if (str[pos_str] == 'a')
				struc->arg_p.a_min = 1;
			else if (str[pos_str] == 'l')
				struc->arg_p.l_min = 1;
			else if (str[pos_str] == 'r')
				struc->arg_p.r_min = 1;
			else if (str[pos_str] == 't')
				struc->arg_p.t_min = 1;
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
	while (struc->arg_p.cont_arg < struc->arg_p.tmp_argc)
	{
		if (verif_flag_ls(argv[struc->arg_p.cont_arg], struc, 1) == 0)
			break ;
		struc->arg_p.cont_arg++;
	}
	if (struc->arg_p.cont_arg == struc->arg_p.tmp_argc)
	{
		argv[struc->arg_p.tmp_argc] = ft_strdup(".");
		struc->arg_p.tmp_argc++;
	}
	else if (struc->arg_p.cont_arg + 1 < struc->arg_p.tmp_argc)
		struc->arg_p.multi = 1;
	return (0);
}
