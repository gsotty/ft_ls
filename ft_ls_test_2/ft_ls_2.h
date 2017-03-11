/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 10:01:03 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/11 15:51:00 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_2_H
# define FT_LS_2_H

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
	int				cont_arg;
	int				cont_arg_2;
	size_t			dir;
	size_t			argv;
	size_t			total;
	size_t			namlen;
	size_t			nlink;
	size_t			pwname;
	size_t			grname;
	size_t			size;
}					t_len_ls;

typedef struct		s_flag_ls
{
	unsigned int	r_maj : 1;
	unsigned int	a_min : 1;
	unsigned int	l_min : 1;
	unsigned int	r_min : 1;
	unsigned int	t_min : 1;
	unsigned int	multi : 1;
}					t_flag_ls;

typedef struct		s_buf_ls
{
	int				argc;
	int				*cont_files;
	char			**save_name;
	char			***buf;
	STAT			**stat;
}					t_buf_ls;

typedef struct		s_struc_ls
{
	t_len_ls		len;
	t_flag_ls		flag;
	t_buf_ls		buf;
}					t_struc_ls;

void				ft_ls(int argc, char **argv, int test, t_struc_ls *struc);
int					check_flag_ls(int argc, char **argv, t_struc_ls *struc);
void				verif_len_2(STAT *buf, t_struc_ls *struc, int nbr_files);
char				*permision_l(struct stat *buf);
void				recursive_r_maj_files_ls(char *save_name, char *buf,
		t_struc_ls *struc);

#endif
