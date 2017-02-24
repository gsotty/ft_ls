/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsotty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 06:27:27 by gsotty            #+#    #+#             */
/*   Updated: 2017/02/24 10:30:51 by gsotty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "stdlib.h"

typedef struct		s_flag_ls
{
	unsigned int	r_maj : 1;
	unsigned int	a_min : 1;
	unsigned int	l_min : 1;
	unsigned int	r_min : 1;
	unsigned int	t_min : 1;
}					t_flag_ls;

typedef struct		s_len_ls
{
	int				nbr_files;
	size_t			*tab_size;
	size_t			cont_arg;
	int				tmp_argc;
}					t_len_ls;

typedef struct		s_data_ls
{
	char			*buf;
}					t_data_ls;

char	*ft_remalloc(char *dest, int len_d, int len_s);

#endif
