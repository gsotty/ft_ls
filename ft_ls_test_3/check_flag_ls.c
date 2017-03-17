/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_ls_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:20:58 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/16 13:46:13 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	verif_flag_ls(char *str, t_struc_ls *struc, size_t pos_str)
{
	if (str[0] == '-' && str[1] != '\0')
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
			else if (str[pos_str] == '1')
				struc->flag.one = 1;
			else if (str[pos_str] == '-')
				struc->flag.tiret = 1;
			else
			{
				ft_printf("./ft_ls: illegal option -- %c\n", str[pos_str]);
				ft_printf("usage: ./ft_ls [-Ralrt1] [file ...]\n");
				exit(1);
			}
			pos_str++;
		}
		return (1);
	}
	return (0);
}

int			check_flag_ls(int argc, char **argv, t_struc_ls *struc)
{
	int		x;

	x = 1;
	struc->buf.argc = argc;
	while (x < struc->buf.argc && struc->flag.tiret == 0)
	{
		if ((verif_flag_ls(argv[x], struc, 1)) == 0)
			break ;
		x++;
	}
	if (x == struc->buf.argc || (struc->flag.tiret == 1 && x ==
				struc->buf.argc))
	{
		if (struc->flag.tiret == 1)
			argv[x] = ft_strdup(".");
		else
			argv[struc->buf.argc] = ft_strdup(".");
		struc->buf.argc++;
	}
	else if (x + 1 < struc->buf.argc)
		struc->flag.multi = 1;
	return (x);
}
