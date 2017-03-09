/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 10:01:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/09 11:55:06 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define STAT	struct stat
# define DIRENT	struct dirent

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <fcntl.h>
# include <sys/xattr.h>

typedef struct		s_len_ls
{
	size_t			nlink;
	size_t			size;
	size_t			grname;
	size_t			pwname;
	size_t			*namlen;
}					t_len_ls;

typedef struct		s_struc_ls
{
	unsigned int	r_maj : 1;
	unsigned int	a_min : 1;
	unsigned int	l_min : 1;
	unsigned int	r_min : 1;
	unsigned int	t_min : 1;
	unsigned int	multi : 1;
	unsigned int	argc;
	size_t			*len_dir;
	size_t			nbr_files;
	size_t			add_nlink;
	t_len_ls		len;
	char			***name;
	int				not_r;
}					t_struc_ls;

void				verif_len(STAT *buf, t_struc_ls *struc);
int					check_flag_ls(char **argv, t_struc_ls *struc);
char				*permision_l(struct stat *buf);
char				**stat_ls_dir(char *str, t_struc_ls *struc, size_t x);
char				*creat_l_min(STAT buf, t_struc_ls *struc, char *name,
		int len_name);
char				***readdir_ls(t_struc_ls *struc, char **argv,
		size_t cont_argc);
void				recursive_r_maj_ls(int cont_arg, int *cont_files,
		char ***buf);

#endif
