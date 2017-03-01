/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 06:27:27 by gsotty            #+#    #+#             */
/*   Updated: 2017/03/01 17:18:49 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
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

typedef struct			s_arg_p
{
	unsigned int		r_maj : 1;
	unsigned int		a_min : 1;
	unsigned int		l_min : 1;
	unsigned int		r_min : 1;
	unsigned int		t_min : 1;
	unsigned int		multi : 1;
	size_t				cont_arg;
	int					tmp_argc;
	size_t				nbr_dir;
}						t_arg_p;

typedef struct			s_arg_np
{
	size_t				*time;
	char				**per;
	char				**nlink;
	char				**pw_name;
	char				**gr_name;
	char				**size;
	char				**mtime;
	size_t				len_m_nl;
	size_t				len_m_si;
	size_t				len_m_ng;
	size_t				len_m_np;
	size_t				data_nbr;
	size_t				*data_size;
	unsigned int		err : 1;
	size_t				nbr_dir;
	size_t				*directory;
}						t_arg_np;

typedef struct			s_struc_ls
{
	t_arg_p				arg_p;
	t_arg_np			arg_np;
}						t_struc_ls;

typedef struct			s_list_ls
{
	size_t				*time;
	size_t				time_dir;
	char				**per;
	char				**nlink;
	char				**pw_name;
	char				**gr_name;
	char				**size;
	char				**mtime;
	size_t				len_m_nl;
	size_t				len_m_si;
	size_t				len_m_ng;
	size_t				len_m_np;
	unsigned int		err : 1;
	size_t				nbr_dir;
	size_t				*directory;
	char				*dossier;
	size_t				data_nbr;
	size_t				*data_size;
	char				**data;
	struct s_list_ls	*next;
}						t_list_ls;

t_list_ls				*ft_lstnew_ls(char **data, size_t *data_size,
		size_t data_nbr, t_struc_ls *struc);
char					*permision_l(struct stat *buf);
int						check_flag_ls(char **argv, t_struc_ls *struc);
int						write_list(t_list_ls *begin_list, t_struc_ls *struc);
char					*ft_remalloc(char *dest, int len_d, int len_s);
t_list_ls				*order_list(t_list_ls *begin_list, t_struc_ls *struc);
t_list_ls				*order_no_flag(t_list_ls *begin, t_struc_ls *struc);
char					**readdir_ls_f(t_struc_ls *struc, char **data,
		char *str);
char					**readdir_ls(DIR *dir, t_struc_ls *struc, char **data,
		char *str);
size_t					*ft_remalloc_size(size_t *data, size_t len_d,
		size_t len_s);
char					**ft_remalloc_data(char **data, size_t len_d,
		size_t len_s);
char					**read_files(char *str, t_struc_ls *struc, char **data);

#endif
