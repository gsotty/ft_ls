/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_r_maj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 10:59:51 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/09 15:00:10 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	ft_len_dir(char *str)
{
	DIR		*dir;
	size_t	x;

	x = 0;
	dir = opendir(str);
	while (readdir(dir) != NULL)
		x++;
	closedir(dir);
	return (x);
}

void	write_buf_ls(int cont_arg, int *cont_files, char **save_name,
		char ***buf, int test)
{
	int		x;
	int		y;
	int		ret;
	int		len_buf;
	char	*tmp;

	y = 0;
	while (y < cont_arg)
	{
		x = 0;
		if (test == 0)
			ft_printf("%s:\n", save_name[y]);
		while (x < cont_files[y])
		{
			ft_printf("%s\n", buf[y][x]);
			len_buf = ft_strlen(save_name[y]) + ft_strlen(buf[y][x]) + 2;
			if ((tmp = ft_memalloc(sizeof(char) * len_buf)) == NULL)
				return ;
			ret = ft_sprintf(tmp, "%s/%s", save_name[y], buf[y][x]);
			tmp[ret] = '\0';
			if ((buf[y][x] = ft_memalloc(sizeof(char) * (ret + 1))) == NULL)
				return ;
			ft_memcpy(buf[y][x], tmp, ret);
			buf[y][x][ret] = '\0';
			free(tmp);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

void	test_r_maj(int nbr_arg, char **argv, int test)
{
	struct stat		stat;
	struct dirent	*result;
	int				cont_arg;
	int				cont_arg_1;
	int				*cont_files;
	int				len_argv;
	char			*str_error;
	char			**save_name;
	char			***buf;
	DIR				*dir;

	cont_arg = 0;
	cont_arg_1 = 0;
	if ((buf = ft_memalloc(sizeof(char **) * nbr_arg)) == NULL)
		return ;
	if ((save_name = ft_memalloc(sizeof(char *) * nbr_arg)) == NULL)
		return ;
	if ((cont_files = ft_memalloc(sizeof(int) * nbr_arg)) == NULL)
		return ;
	while (cont_arg_1 < nbr_arg)
	{
		if (lstat(argv[cont_arg_1], &stat) == -1)
		{
			str_error = strerror(errno);
			ft_printf("argv = %s\n", argv[cont_arg_1]);
			ft_printf("%s, %s\n", argv[cont_arg_1] + 1, str_error);
		}
		if (S_ISDIR(stat.st_mode) == 1)
		{
			len_argv = ft_strlen(argv[cont_arg_1]);
			if ((save_name[cont_arg] = ft_memalloc(sizeof(char) *
							(len_argv + 1))) == NULL)
				return ;
			ft_memcpy(save_name[cont_arg], argv[cont_arg_1], len_argv);
			save_name[cont_arg][len_argv] = '\0';
			if ((buf[cont_arg] = ft_memalloc(sizeof(char *) *
							((int)ft_len_dir(argv[cont_arg_1]) + 1))) == NULL)
				return ;
			if ((dir = opendir(argv[cont_arg_1])) == NULL)
				return ;
			while ((result = readdir(dir)) != NULL)
			{
				if (result->d_name[0] != '.')
				{
					if ((buf[cont_arg][cont_files[cont_arg]] =
								ft_memalloc(sizeof(char) *
									(result->d_namlen + 1))) == NULL)
						return ;
					ft_memcpy(buf[cont_arg][cont_files[cont_arg]], result->d_name,
							result->d_namlen);
					buf[cont_arg][cont_files[cont_arg]][result->d_namlen] = '\0';
					cont_files[cont_arg]++;
				}
			}
			closedir(dir);
			cont_arg++;
		}
		else if (test == 1)
		{
			len_argv = ft_strlen(argv[cont_arg_1]);
			argv[cont_arg_1][len_argv] = '\0';
			if ((save_name[cont_arg] = ft_memalloc(sizeof(char) *
							(len_argv + 1))) == NULL)
				return ;
			ft_memcpy(save_name[cont_arg], argv[cont_arg_1], len_argv);
			save_name[cont_arg][len_argv] = '\0';
			if ((buf[cont_arg] = ft_memalloc(sizeof(char *) + 1)) == NULL)
				return ;
			if ((buf[cont_arg][cont_files[cont_arg]] =
						ft_memalloc(sizeof(char) * (len_argv + 1))) == NULL)
				return ;
			ft_memcpy(buf[cont_arg][cont_files[cont_arg]], argv[cont_arg_1],
					len_argv);
			buf[cont_arg][cont_files[cont_arg]][len_argv] = '\0';
			cont_files[cont_arg]++;
			cont_arg++;
		}
		cont_arg_1++;
	}
	write_buf_ls(cont_arg, cont_files, save_name, buf, test);
	recursive_r_maj_ls(cont_arg, cont_files, buf);
	free(buf);
	free(cont_files);
	free(save_name);
}

void	recursive_r_maj_ls(int cont_arg, int *cont_files, char ***buf)
{
	int		j;

	j = 0;
	while (j < cont_arg)
	{
		test_r_maj(cont_files[j] - 2, buf[j] + 2, 0);
		j++;
	}
}

int		main(int argc, char **argv)
{
	test_r_maj(argc - 1, argv + 1, 1);
	return (0);
}
