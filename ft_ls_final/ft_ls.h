/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 11:27:57 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/29 10:34:28 by gsotty           ###   ########.fr       */
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

typedef struct		s_len_s
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
	unsigned int	one : 1;
	unsigned int	tiret : 1;
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
	size_t			*files_or_dir;
	int				*cont_files;
	char			**save_name;
	size_t			**xattr;
	char			***buf;
	STAT			**stat;
}					t_buf_ls;

typedef struct		s_struc_ls
{
	t_len_ls		len;
	t_flag_ls		flag;
	t_buf_ls		buf;
}					t_struc_ls;

void				printf_l_nlik(t_struc_ls *struc, int x, int y);
void				printf_l_lik(t_struc_ls *struc, int x, int y,
		char **save_name);
void				printf_l_nlik_tsix(t_struc_ls *struc, int x, int y);
void				printf_l_lik_tsix(t_struc_ls *struc, int x, int y,
		char **save_name);
void				write_buf_ls(char **save_name, int test, t_struc_ls *struc,
		long long total);
void				orber_dir_t_no_r(int x, char **save_name,
		t_struc_ls *struc);
void				orber_dir_t_r(int x, char **save_name,
		t_struc_ls *struc);
void				order_t_r(char **save_name, t_struc_ls *struc);
void				order_t_no_r(char **save_name, t_struc_ls *struc);
void				order_no_t_r(char **save_name, t_struc_ls *struc);
void				order_no_t_no_r(char **save_name, t_struc_ls *struc);
void				order_r(char **save_name, t_struc_ls *struc);
void				order_no_r(char **save_name, t_struc_ls *struc);
void				ft_while_ls(char *str, int test, t_struc_ls *struc);
void				write_struc_ls(size_t cont_files, char *str, char *name,
		t_struc_ls *struc);
void				files_is_dir(char *str, t_struc_ls *struc, int test);
void				files_is_files(char *str, t_struc_ls *struc, STAT stat);
size_t				ft_len_dir(char *str, int test, t_struc_ls *struc);
void				ft_ls(int argc, char **argv, int test, t_struc_ls *struc);
int					check_flag_ls(int argc, char **argv, t_struc_ls *struc);
void				verif_len(STAT *buf, t_struc_ls *struc, int nbr_files);
char				*permision_l(struct stat *buf, int y, int x,
		t_struc_ls *struc);
void				recursive_r_maj_files_ls(char *save_name, char *buf,
		t_struc_ls *struc);

#endif
