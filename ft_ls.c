/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 06:27:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/25 12:50:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

int			verif_flag_ls(char *str, t_flag_ls *flag, size_t pos_str)
{
	if (str[0] == '-')
	{
		while (str[pos_str] != '\0')
		{
			if (str[pos_str] == 'l')
				flag->l_min = 1;
			else if (str[pos_str] == 'R')
				flag->r_maj = 1;
			else if (str[pos_str] == 'a')
				flag->a_min = 1;
			else if (str[pos_str] == 'r')
				flag->r_min = 1;
			else if (str[pos_str] == 't')
				flag->t_min = 1;
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

int			check_flag_ls(char **argv, t_flag_ls *flag, t_len_ls *len)
{
	while (len->cont_arg < len->tmp_argc)
	{
		if (verif_flag_ls(argv[len->cont_arg], flag, 1) == 0)
			break ;
		len->cont_arg++;
	}
	if (len->cont_arg == len->tmp_argc)
	{
		argv[len->tmp_argc] = ft_strdup(".");
		len->tmp_argc++;
	}
	else if (len->cont_arg < len->tmp_argc)
		flag->multi = 1;
	return (0);
}

#include <unistd.h>
#include <sys/stat.h>

#include <dirent.h>

#include <errno.h>

#include <pwd.h>

char		***read_files(char **argv, t_flag_ls *flag, t_len_ls *len,
		char ***data)
{
	DIR				*dir;
	char			*str_errno;
	int				errno;
	char			*tmp;
	struct dirent	*result;
	struct passwd	*p;
	//	struct stat		buf;


	if ((dir = opendir(argv[len->cont_arg])) == NULL)
	{
		str_errno = strerror(errno);
		if (ft_strcmp(str_errno, "Not a directory") != 0)
		{
			tmp = ft_strjoin("ls: ", argv[len->cont_arg]);
			tmp = ft_strjoin(tmp, ": ");
			data[len->nbr_dir][len->nbr_files[len->nbr_dir]] =
				ft_strjoin(tmp, str_errno);
			len->nbr_files[len->nbr_dir]++;
		}
		else
		{
			data[len->nbr_dir][len->nbr_files[len->nbr_dir]] =
				ft_strdup(argv[len->cont_arg]);
			len->nbr_files[len->nbr_dir]++;
		}
		return (data);
	}
	while ((result = readdir(dir)) != NULL)
	{
		if ((flag->a_min == 1) && (result->d_name[0] == '.'))
		{
			data = ft_remalloc_data(data, len, len->nbr_files[len->nbr_dir]
					+ 1);
			data[len->nbr_dir][len->nbr_files[len->nbr_dir]] =
				ft_strdup(result->d_name);
			len->nbr_files[len->nbr_dir]++;
		}
		else if ((result->d_name[0] != '.'))
		{
			data = ft_remalloc_data(data, len, len->nbr_files[len->nbr_dir]
					+ 1);
			data[len->nbr_dir][len->nbr_files[len->nbr_dir]] =
				ft_strdup(result->d_name);
			len->nbr_files[len->nbr_dir]++;
		}
		//	stat(result->d_name, &buf);
		//	p = getpwuid(buf.st_uid);
		//	ft_printf("%s\n", p->pw_name);
	}
	closedir(dir);
	return (data);
}

int			main(int argc, char **argv)
{
	size_t		cont_arg;
	t_flag_ls	flag;
	t_len_ls	len;
	char	***data;
	char		*tmp;

	len.cont_arg = 1;
	len.nbr_dir = 0;
	len.tmp_argc = argc;
	if (!(len.nbr_files = ft_memalloc((sizeof(int) * len.nbr_dir + 1))))
		return (-1);
	ft_memset(len.nbr_files, 0, sizeof(int) * len.nbr_dir + 1);
	if (!(data = ft_memalloc((sizeof(char **) * len.nbr_dir + 1))))
		return (-1);
	if (!(data[0] = ft_memalloc((sizeof(char *) * len.nbr_files[len.nbr_dir]
						+ 1))))
		return (-1);
	ft_memset(&flag, 0, sizeof(t_flag_ls));
	check_flag_ls(argv, &flag, &len);
	while (len.cont_arg < len.tmp_argc)
	{
		len.nbr_files[len.nbr_dir] = 0;
		if (flag.multi == 1)
		{
			ft_printf("%d %d\n", len.nbr_dir, len.nbr_files[len.nbr_dir]);
			tmp = ft_strjoin(argv[len.cont_arg], ":");
			data[len.nbr_dir][len.nbr_files[len.nbr_dir]] = ft_strdup(tmp);
			len.nbr_files[len.nbr_dir]++;
		}
		data = read_files(argv, &flag, &len, data);
		len.cont_arg++;
		if (flag.multi == 1 && !(len.cont_arg >= len.tmp_argc))
		{
			data[len.nbr_dir][len.nbr_files[len.nbr_dir]] = ft_strdup("");
			len.nbr_files[len.nbr_dir]++;
		}
		len.nbr_dir++;
	}
	/*
	   ft_printf("cont_arg = %d ", len.cont_arg);
	   ft_printf("argv[cont_arg] = %s\n", argv[len.cont_arg]);
	   ft_printf("r_maj = %d ", flag.r_maj);
	   ft_printf("a_min = %d ", flag.a_min);
	   ft_printf("l_min = %d\n", flag.l_min);
	   ft_printf("r_min = %d ", flag.r_min);
	   ft_printf("t_min = %d\n", flag.t_min);
	   */
	int			x;
	int			y;

	x = 0;
	while (x < len.nbr_dir)
	{
		y = 0;
		while (y < len.nbr_files[len.nbr_dir])
		{
			printf("%s\n", data[x][y]);
			y++;
		}
		x++;
	}
	return (0);
}
