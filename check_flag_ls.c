/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_ls_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 11:20:58 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 17:44:41 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	char_flag_is_2(char *str, t_struc_ls *struc, size_t pos_str)
{
	if (str[pos_str] == 'R')
		struc->flag.r_maj = 1;
	else if (str[pos_str] == 'T')
		struc->flag.t_maj = 1;
	else if (str[pos_str] == 'S')
		struc->flag.s_maj = 1;
	else if (str[pos_str] == 'a')
		struc->flag.a_min = 1;
	else if (str[pos_str] == 'f')
	{
		struc->flag.f_min = 1;
		struc->flag.a_min = 1;
	}
	else if (str[pos_str] == 'l')
		struc->flag.l_min = 1;
	else if (str[pos_str] == 'u')
		struc->flag.u_min = 1;
	else if (str[pos_str] == 'r')
		struc->flag.r_min = 1;
	else if (str[pos_str] == 's')
		struc->flag.s_min = 1;
	else
		return (0);
	return (1);
}

static void	char_flag_is(char *str, t_struc_ls *struc, size_t pos_str)
{
	if (str[pos_str] == 't')
		struc->flag.t_min = 1;
	else if (str[pos_str] == '1')
		struc->flag.one = 1;
	else if (str[1] == '-' && str[2] == '\0')
		struc->flag.tiret = 1;
	else if ((char_flag_is_2(str, struc, pos_str)) == 1)
		return ;
	else
	{
		ft_printf("ls: illegal option -- %c\n", str[pos_str]);
		ft_printf("usage: ./ft_ls [-RTSaflurt1] [file ...]\n");
		exit(1);
	}
}

static int	verif_flag_ls(char *str, t_struc_ls *struc, size_t pos_str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		while (str[pos_str] != '\0')
		{
			char_flag_is(str, struc, pos_str);
			pos_str++;
		}
		return (1);
	}
	return (0);
}

static int	filling_struc(char **argv, t_struc_ls *struc)
{
	int		x;

	x = 1;
	while (x < struc->buf.argc && struc->flag.tiret == 0)
	{
		if ((verif_flag_ls(argv[x], struc, 1)) == 0)
			break ;
		x++;
	}
	return (x);
}

int			check_flag_ls(int argc, char **argv, t_struc_ls *struc)
{
	int		y;

	struc->buf.argc = argc;
	y = filling_struc(argv, struc);
	if (y == struc->buf.argc || (struc->flag.tiret == 1 && y ==
				struc->buf.argc))
	{
		if (struc->flag.tiret == 1)
			argv[y] = ft_strdup(".");
		else
			argv[struc->buf.argc] = ft_strdup(".");
		struc->buf.argc++;
	}
	else if (y + 1 < struc->buf.argc)
		struc->flag.multi = 1;
	verif_argv_null(argc, argv, y);
	return (y);
}
