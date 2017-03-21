/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:47:47 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/21 13:49:12 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		ft_len_dir(char *str, int test, t_struc_ls *struc)
{
	char			*test_1;
	DIR				*dir;
	size_t			x;
	struct dirent	*result;

	x = 0;
	if ((dir = opendir(str)) == NULL)
	{
		if (test == 0 || struc->flag.multi == 1)
			ft_printf("%s:\n", str);
		ft_printf("ls: ");
		if (str == NULL)
			perror("fts_open");
		else if ((test_1 = ft_strrchr(str, '/')) == NULL)
			perror(str);
		else
			perror(ft_strrchr(str, '/') + 1);
		return (-1);
	}
	while ((result = readdir(dir)) != NULL)
	{
		if (result->d_name[0] != '.' && struc->flag.a_min == 0)
			x++;
		else if (result->d_name[0] == '.' && struc->flag.a_min == 1)
			x++;
		else if (struc->flag.a_min == 1)
			x++;
	}
	closedir(dir);
	return (x);
}
