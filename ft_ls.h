/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 06:27:27 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/25 18:05:56 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "stdlib.h"

typedef struct			s_flag_ls
{
	unsigned int		r_maj : 1;
	unsigned int		a_min : 1;
	unsigned int		l_min : 1;
	unsigned int		r_min : 1;
	unsigned int		t_min : 1;
	unsigned int		multi : 1;
	unsigned int		err : 1;
}						t_flag_ls;

typedef struct			s_len_ls
{
	size_t				*data_size;
	size_t				data_nbr;
	size_t				cont_arg;
	int					tmp_argc;
}						t_len_ls;

typedef struct			s_struc_ls
{
	t_flag_ls			flag;
	t_len_ls			len;
}						t_struc_ls;

typedef struct			s_list_ls
{
	unsigned int 		err : 1;
	char				*dossier;
	char				**data;
	size_t				data_nbr;
	size_t				*data_size;
	struct s_list_ls	*next;
}						t_list_ls;

char	*ft_remalloc(char *dest, int len_d, int len_s);
int		check_flag_ls(char **argv, t_struc_ls *struc);

#endif
