/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 06:27:24 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/24 11:43:03 by gsotty           ###   ########.fr       */
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
	return (0);
}

#include <unistd.h>
#include <sys/stat.h>

#include <dirent.h>

#include <errno.h>

#include <pwd.h>

t_data_ls	*ft_remalloc_data(t_data_ls *data, size_t len_d, size_t len_s)
{
	int			x;
	t_data_ls	*tmp_data;
	char		*tmp_buf;

	if (len_d <= len_s)
		return (data);
	x = 0;
	if (!(tmp_data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	while (x < len_s)
	{
		tmp_data[x].buf = ft_strdup(data[x].buf);
		x++;
	}
	free(data);
	if (!(data = ft_memalloc((sizeof(char *) * len_d))))
		return (NULL);
	ft_memset(data, 0, sizeof(t_data_ls) * len_d);
	x = 0;
	while (x < len_s)
	{
		data[x].buf = ft_strdup(tmp_data[x].buf);
		x++;
	}
	free(tmp_data);
	return (data);
}

t_data_ls	*read_files(char **argv, t_flag_ls *flag, t_len_ls *len,
		t_data_ls *data)
{
	DIR				*dir;
	char			*str_errno;
	int				errno;
	char			*tmp;
	struct dirent	*result;
	struct passwd	*p;
	struct stat		buf;

	if ((dir = opendir(argv[len->cont_arg])) == NULL)
	{
		str_errno = strerror(errno);
		if (ft_strcmp(str_errno, "Not a directory") != 0)
		{
			tmp = ft_strjoin("ls: ", argv[len->cont_arg]);
			tmp = ft_strjoin(tmp, ": ");
			data[len->nbr_files].buf = ft_strjoin(tmp, str_errno);
			len->nbr_files++;
		}
		else
		{
			data[len->nbr_files].buf = ft_strdup(argv[len->cont_arg]);
			len->nbr_files++;
		}
		return (data);
	}
	while ((result = readdir(dir)) != NULL)
	{
		if ((flag->a_min == 1) && (result->d_name[0] == '.'))
		{
			data[len->nbr_files].buf = ft_strdup(result->d_name);
			len->nbr_files++;
			data = ft_remalloc_data(data, len->nbr_files + 1, len->nbr_files);
		}
		else if ((result->d_name[0] != '.'))
		{
			data[len->nbr_files].buf = ft_strdup(result->d_name);
			len->nbr_files++;
			data = ft_remalloc_data(data, len->nbr_files + 1, len->nbr_files);
		}
	//	stat(result->d_name, &buf);
	//	p = getpwuid(buf.st_uid);
	//	ft_printf("%s\n", p->pw_name);
	}
	return (data);
}

int			main(int argc, char **argv)
{
	size_t		cont_arg;
	t_flag_ls	flag;
	t_len_ls	len;
	t_data_ls	*data;
	char		**tmp;
	int			x;

	x = 0;
	len.cont_arg = 1;
	len.nbr_files = 0;
	len.tmp_argc = argc;
	if (!(data = ft_memalloc((sizeof(char *) * 1))))
		return (-1);
	ft_memset(&flag, 0, sizeof(t_flag_ls));
	check_flag_ls(argv, &flag, &len);
	data = read_files(argv, &flag, &len, data);
	/*
	ft_printf("cont_arg = %d ", len.cont_arg);
	ft_printf("argv[cont_arg] = %s\n", argv[len.cont_arg]);
	ft_printf("r_maj = %d ", flag.r_maj);
	ft_printf("a_min = %d ", flag.a_min);
	ft_printf("l_min = %d\n", flag.l_min);
	ft_printf("r_min = %d ", flag.r_min);
	ft_printf("t_min = %d\n", flag.t_min);
	*/
	while (x < len.nbr_files)
	{
			printf("%s\n", data[x].buf);
			x++;
	}
	return (0);
}
